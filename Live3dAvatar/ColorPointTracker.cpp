//
// Created by jasf on 4/7/16.
//

#include "ColorPointTracker.h"
#include "Logger.h"
#include "Demo.h"

ColorPointTracker::ColorPointTracker() {

}


void ColorPointTracker::update(std::unordered_map<char, cv::Mat> &imgs) {

    for (auto img_it = imgs.begin(); img_it != imgs.end(); img_it++) {
        cv::Mat &img = img_it->second;
        cvtColor(img, img, COLOR_BGR2HSV);

        Mat out(img);

        for (auto it = targets.begin(); it != targets.end(); it++) {
            detect(it->second, img);
            cv::polylines(out, it->second->getContourn(), true, it->second->getHSVHigh(), 4, 8);
        }

        cvtColor(out, out, COLOR_HSV2BGR);

        Demo::getOutput("detectionWindow#" + std::to_string(img_it->first)).display(out);
    }


}


void ColorPointTracker::addHSVRangeToTrack(const Eigen::Vector3f &low_hsv, const Eigen::Vector3f &high_hsv,
                                           std::string obj_name) {

    char idx = HSVRangeTrackableObject::getNextAvailableId();
    targets[idx] = boost::shared_ptr<HSVRangeTrackableObject>(new HSVRangeTrackableObject(low_hsv.x(), high_hsv.x(),
                                                                                          low_hsv.y(), high_hsv.y(),
                                                                                          low_hsv.z(), high_hsv.z()));

    targets[idx]->setName(obj_name);

}

void ColorPointTracker::detect(boost::shared_ptr<HSVRangeTrackableObject> objToTrack, const Mat &img) {
    static const Size2i &erose_kernel_size = Size(5, 5);
    static const Size2i &dilate_kernel_size = Size(10, 10);

    Mat filteredImg;

    inRange(img, objToTrack->getHSVLow(), objToTrack->getHSVHigh(), filteredImg);

    erode(filteredImg, filteredImg, getStructuringElement(MORPH_ELLIPSE, erose_kernel_size));
    erode(filteredImg, filteredImg, getStructuringElement(MORPH_ELLIPSE, erose_kernel_size));

    dilate(filteredImg, filteredImg, getStructuringElement(MORPH_ELLIPSE, dilate_kernel_size));
    dilate(filteredImg, filteredImg, getStructuringElement(MORPH_ELLIPSE, dilate_kernel_size));

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    Moments moment;
    int firstAngle = 0;

    findContours(filteredImg, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    if (contours.size() > 0) {
        double max_seen_area = 0;
        int index = 0;

        //find contour of max max_seen_area
        for (int i = 0; i < contours.size(); i++) {
            moment = moments(contours[i]);
            if (moment.m00 > max_seen_area) {
                max_seen_area = moment.m00;
                index = i;
            }
        }

        moment = moments(contours[index]);

        objToTrack->setArea(moment.m00);
        objToTrack->setXCenter(moment.m10 / moment.m00);
        objToTrack->setYCenter(moment.m01 / moment.m00);
        objToTrack->setContourn(contours[index]);
    }


}


ColorPointTracker::~ColorPointTracker() {
    targets.clear();

}

std::vector<Eigen::Vector3f> ColorPointTracker::getCenters() const {
    std::vector<Eigen::Vector3f> out;

    for (auto obj = targets.begin(); obj != targets.end(); obj++) {
        out.emplace_back(obj->second->getXCenter(), obj->second->getYCenter(), obj->second->getZCenter());
    }

    return out;
}
