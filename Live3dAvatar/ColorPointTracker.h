//
// Created by jasf on 4/7/16.
//

#ifndef TG1_ARM_DETECTION_COLOR_COLORPOINTTRACKER_H
#define TG1_ARM_DETECTION_COLOR_COLORPOINTTRACKER_H

#include "PointTracker.h"
#include "Camera.h"

#include <vector>
#include <unordered_map>
#include <boost/shared_ptr.hpp>

#include <eigen3/Eigen/Dense>

class ColorPointTracker : public PointTracker {

    std::unordered_map<char, boost::shared_ptr<HSVRangeTrackableObject>> targets;

public:
    ColorPointTracker();

    virtual ~ColorPointTracker();

    std::vector<Eigen::Vector3f> getCenters() const;

    void update(std::unordered_map<char, cv::Mat> &imgs);

    void addHSVRangeToTrack(const Eigen::Vector3f &low_hsv, const Eigen::Vector3f &high_hsv, std::string obj_name = "");

    void detect(boost::shared_ptr<HSVRangeTrackableObject> objToTrack, const Mat &img);

};


#endif //TG1_ARM_DETECTION_COLOR_COLORPOINTTRACKER_H
