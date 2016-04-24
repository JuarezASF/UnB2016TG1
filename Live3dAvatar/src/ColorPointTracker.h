//
// Created by jasf on 4/7/16.
//

#ifndef TG1_ARM_DETECTION_COLOR_COLORPOINTTRACKER_H
#define TG1_ARM_DETECTION_COLOR_COLORPOINTTRACKER_H

#include "MultipleViewPointTracker.h"
#include "Camera.h"

#include <vector>
#include <unordered_map>

#include <eigen3/Eigen/Dense>

/***
 * Detects multiple objects on multiple cameras
 */
class ColorPointTracker{

    //objects to track
    std::vector<RangeMultipleViewTracker *> targets;
    std::map<int, std::string> idx_name_map;
    std::map<std::string, int> name_idx_map;

public:
    ColorPointTracker();

    virtual ~ColorPointTracker();

    void update(std::vector<cv::Mat> &imgs);

    void addHSVRangeToTrack(const cv::Scalar &low_hsv, const cv::Scalar &high_hsv, std::string obj_name = "");

    std::vector<cv::Point3d> getCenters() const;

};


#endif //TG1_ARM_DETECTION_COLOR_COLORPOINTTRACKER_H
