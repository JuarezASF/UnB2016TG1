//
// Created by rodrigo on 3/29/16.
//

#include "RangeMultipleViewTracker.h"

void RangeMultipleViewTracker::setHSV(cv::Scalar low, cv::Scalar high) {
    lowColor = low;
    highColor = high;
}

cv::Scalar RangeMultipleViewTracker::getHSVLow() {
    return lowColor;
}

cv::Scalar RangeMultipleViewTracker::getHSVHigh() {
    return highColor;
}


RangeMultipleViewTracker::RangeMultipleViewTracker(cv::Scalar low, cv::Scalar high) : lowColor(
        low), highColor(high) {

}

RangeMultipleViewTracker::~RangeMultipleViewTracker() {

}

void RangeMultipleViewTracker::update(const std::vector<cv::Mat> &hsv_imgs) {
    static const cv::Size2i &erose_kernel_size = cv::Size(5, 5);
    static const cv::Size2i &dilate_kernel_size = cv::Size(10, 10);


    measuredCenters.clear();

    //detect colort on each image of the array
    for (int k = 0; k < hsv_imgs.size(); k++) {
        cv::Mat input = hsv_imgs[k];
        cv::Mat filteredImg;

        inRange(input, lowColor, highColor, filteredImg);

        erode(filteredImg, filteredImg, getStructuringElement(cv::MORPH_ELLIPSE, erose_kernel_size));
        erode(filteredImg, filteredImg, getStructuringElement(cv::MORPH_ELLIPSE, erose_kernel_size));

        dilate(filteredImg, filteredImg, getStructuringElement(cv::MORPH_ELLIPSE, dilate_kernel_size));
        dilate(filteredImg, filteredImg, getStructuringElement(cv::MORPH_ELLIPSE, dilate_kernel_size));


        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::Moments moment;

        int firstAngle = 0;

        cv::findContours(filteredImg, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

        if (contours.size() > 0) {
            double max_seen_area = 0;
            unsigned int index = 0;

            //find contour of max max_seen_area
            for (unsigned int i = 0; i < contours.size(); i++) {
                moment = moments(contours[i]);
                if (moment.m00 > max_seen_area) {
                    max_seen_area = moment.m00;
                    index = i;
                }
            }

            moment = moments(contours[index]);

            measuredCenters.push_back(cv::Point3d(moment.m10 / moment.m00, moment.m01 / moment.m00, 0));
        } else {
            std::cerr << "Could not find center for hsv hange [(" << lowColor << "),(" << highColor << ")]" <<
            std::endl;
        }

    }

    //update estimated center
    cv::Point3d out(0, 0, 0);
    double w = 1.0 / measuredCenters.size();

    for (unsigned int i = 0; i < measuredCenters.size(); i++)
        out += w * measuredCenters[i];

    estimatedCenter = out;
}

std::vector<cv::Point3d> RangeMultipleViewTracker::getCenters() const {
    return measuredCenters;
}

cv::Point3d RangeMultipleViewTracker::getEstimatedCenter() const {
    return estimatedCenter;
}
