//
// Created by jasf on 5/17/16.
//

#ifndef STEP00_TEMPLATETRACLER_H
#define STEP00_TEMPLATETRACLER_H


#include "Markers.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <iostream>

/**
 * Multiple Object Template Tracker
 */
class MOTemplateTracker {

    Markers markers;

    std::vector<std::vector<cv::Point2d>> centers;

public:

    MOTemplateTracker();

    //update objects detection based on each received image
    void update(const std::vector <cv::Mat> &imgs);

    //return center of object on each view
    virtual std::vector <cv::Point3d> getCenters() const;


};


#endif //STEP00_TEMPLATETRACLER_H
