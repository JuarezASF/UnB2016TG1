//
// Created by rodrigo on 3/29/16.
//
#include <string>

#include <opencv2/opencv.hpp>
#include "MultipleViewPointTracker.h"

#ifndef TG1_ARM_DETECTION_COLOR_ARM_H
#define TG1_ARM_DETECTION_COLOR_ARM_H


/***
 * A HSV range that can be tracked on multiple views
 */
class RangeMultipleViewTracker : public MultipleViewPointTracker {

    //the range we track is given by
    cv::Scalar lowColor, highColor;

public:

    RangeMultipleViewTracker(cv::Scalar low, cv::Scalar high);
    void setHSV(cv::Scalar low, cv::Scalar high);

    virtual ~RangeMultipleViewTracker();

    //update objects detection based on each received image
    void update(const std::vector<cv::Mat> &hsv_imgs);

    //return center of object on each view
    std::vector<cv::Point3d> getCenters() const;
    cv::Point3d getEstimatedCenter() const;


    // access to member variables
    cv::Scalar getHSVLow();
    cv::Scalar getHSVHigh();



};


#endif //TG1_ARM_DETECTION_COLOR_ARM_H
