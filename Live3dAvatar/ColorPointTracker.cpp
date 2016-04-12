//
// Created by jasf on 4/7/16.
//

#include "ColorPointTracker.h"
#include "Demo.h"

ColorPointTracker::ColorPointTracker(unsigned int qtdOfCameras) : qtdOfCameras(qtdOfCameras) {


}


void ColorPointTracker::update(std::unordered_map<char, cv::Mat> &imgs) {

    unsigned int image_index = 0;
    for (auto img_it = imgs.begin(); img_it != imgs.end(); img_it++) {
        cv::Mat &img = img_it->second;
        cvtColor(img, img, cv::COLOR_BGR2HSV);

        cv::Mat out(img);

        for (auto it = targets.begin(); it != targets.end(); it++) {
            detect(it->second, img, image_index);
            cv::polylines(out, it->second->getContourn(image_index++), true, it->second->getHSVHigh(), 4, 8);
        }

        cvtColor(out, out, cv::COLOR_HSV2BGR);

        Demo::getOutput("detectionWindow#" + std::to_string(img_it->first)).display(out);
    }


}


void ColorPointTracker::addHSVRangeToTrack(const cv::Scalar &low_hsv, const cv::Scalar &high_hsv,
                                           std::string obj_name) {

    char idx = HSVRangeMultipleViewTrackableObject::getNextAvailableId();
    targets[idx] = boost::shared_ptr<HSVRangeMultipleViewTrackableObject>(
            new HSVRangeMultipleViewTrackableObject(low_hsv, high_hsv, qtdOfCameras));

    targets[idx]->setName(obj_name);

}

void ColorPointTracker::detect(boost::shared_ptr<HSVRangeMultipleViewTrackableObject> objToTrack, const cv::Mat &img,
                               unsigned int k) {
    static const cv::Size2i &erose_kernel_size = cv::Size(5, 5);
    static const cv::Size2i &dilate_kernel_size = cv::Size(10, 10);

    cv::Mat filteredImg;

    inRange(img, objToTrack->getHSVLow(), objToTrack->getHSVHigh(), filteredImg);

    erode(filteredImg, filteredImg, getStructuringElement(cv::MORPH_ELLIPSE, erose_kernel_size));
    erode(filteredImg, filteredImg, getStructuringElement(cv::MORPH_ELLIPSE, erose_kernel_size));

    dilate(filteredImg, filteredImg, getStructuringElement(cv::MORPH_ELLIPSE, dilate_kernel_size));
    dilate(filteredImg, filteredImg, getStructuringElement(cv::MORPH_ELLIPSE, dilate_kernel_size));

    std::vector<std::vector<cv::Point> > contornos;
    std::vector<cv::Vec4i> hierarchy;
    cv::Moments moment;
    int firstAngle = 0;

    cv::findContours(filteredImg, contornos, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

    if (contornos.size() > 0) {
        double max_seen_area = 0;
        unsigned int index = 0;

        //find contour of max max_seen_area
        for (unsigned int i = 0; i < contornos.size(); i++) {
            moment = moments(contornos[i]);
            if (moment.m00 > max_seen_area) {
                max_seen_area = moment.m00;
                index = i;
            }
        }

        moment = moments(contornos[index]);

        objToTrack->setArea(moment.m00, k);
        objToTrack->setCenter(cv::Point3d(moment.m10 / moment.m00, moment.m01 / moment.m00, 0), k);


        objToTrack->setContourn(contornos[index], k);
    }


}


ColorPointTracker::~ColorPointTracker() {
    targets.clear();

}

std::vector<cv::Point3d> ColorPointTracker::getCenters() const {
    std::vector<cv::Point3d> out;

    std::unordered_map<char, boost::shared_ptr<HSVRangeMultipleViewTrackableObject>>::const_iterator obj;
    for (obj = targets.begin(); obj != targets.end(); obj++) {
        out.emplace_back(obj->second->getEstimatedCenter());
    }

    return out;
}
