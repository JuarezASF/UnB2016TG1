//
// Created by jasf on 4/7/16.
//

#ifndef TG1_ARM_DETECTION_COLOR_COLORPOINTTRACKER_H
#define TG1_ARM_DETECTION_COLOR_COLORPOINTTRACKER_H

#include "PointTracker.h"
#include "Camera.h"

#include <vector>
#include <unordered_map>

#include <eigen3/Eigen/Dense>

class ColorPointTracker : public PointTracker {

    std::unordered_map<char, HSVRangeMultipleViewTrackableObject *> targets;

    unsigned int qtdOfCameras;

    std::vector<cv::Vec4i> hierarchy;
    std::vector<std::vector<cv::Point> > current_contourns;

public:
    ColorPointTracker(unsigned int qtdOfCameras);

    virtual ~ColorPointTracker();

    std::vector<cv::Point3d> getCenters() const;

    void update(std::unordered_map<char, cv::Mat> &imgs);

    void addHSVRangeToTrack(const cv::Scalar &low_hsv, const cv::Scalar &high_hsv, std::string obj_name = "");

    void detect(HSVRangeMultipleViewTrackableObject *objToTrack, const cv::Mat &img, unsigned int k);

};


#endif //TG1_ARM_DETECTION_COLOR_COLORPOINTTRACKER_H
