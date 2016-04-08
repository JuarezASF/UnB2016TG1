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
        cv::Mat img = img_it->second;

        Demo::getOutput("originalWindow#" + std::to_string(img_it->first)).display(img);
        Mat imgDetection;
        img.copyTo(imgDetection);

        for (auto it = targets.begin(); it != targets.end(); it++) {
            detect(it->second, img, imgDetection);
        }

        Demo::getOutput("detectionWindow#" + std::to_string(img_it->first)).display(imgDetection);
    }


}


void ColorPointTracker::addHSVRangeToTrack(const Eigen::Vector3f &low_hsv, const Eigen::Vector3f &high_hsv,
                                           std::string obj_name) {

    char idx = HSVRangeTrackableObject::getNextAvailableId();
    targets.emplace(
            std::make_pair(idx, new HSVRangeTrackableObject(low_hsv.x(), high_hsv.x(),
                                                            low_hsv.y(), high_hsv.y(),
                                                            low_hsv.z(), high_hsv.z())));

    targets[idx]->setName(obj_name);

}

void ColorPointTracker::detect(boost::shared_ptr<HSVRangeTrackableObject> objToTrack, Mat imgOriginal,
                               Mat imgDetection) {
    Mat imgHSV;
    Mat imgThresholded;

    cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);

    inRange(imgHSV, objToTrack->getHSVLow(), objToTrack->getHSVHigh(), imgThresholded);

    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)));
    dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)));

    String windowTitle;

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    Moments moment;
    int firstAngle = 0;

    findContours(imgThresholded, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    if (contours.size() > 0) {
        bool zDetection = false;
        double area = 0;
        int index = 0;

        for (int i = 0; i < contours.size(); i++) {
            moment = moments(contours[i]);
            if (moment.m00 > area) {
                area = moment.m00;
                index = i;
            }
        }

        drawContours(imgDetection, contours, index, Scalar(0, 0, 255), 2, 8, hierarchy, 0, Point());

        moment = moments(contours[index]);

        objToTrack->setArea(moment.m00);
        objToTrack->setXCenter(moment.m10 / moment.m00);
        objToTrack->setYCenter(moment.m01 / moment.m00);
    }


}

std::vector<Eigen::Vector3f> ColorPointTracker::getCenters() const {
}
