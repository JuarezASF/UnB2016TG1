//
// Created by jasf on 4/7/16.
//

#ifndef TG1_ARM_DETECTION_COLOR_POINTTRACKER_H
#define TG1_ARM_DETECTION_COLOR_POINTTRACKER_H

#include <eigen3/Eigen/Dense>
#include <vector>
#include <opencv2/core/mat.hpp>
#include <unordered_map>

class PointTracker {

protected:
    bool quitRequested;

public:
    virtual std::vector<Eigen::Vector3f> getCenters() const = 0;

    virtual void update(std::unordered_map<char, cv::Mat> &imgs) = 0;

    inline bool getQuitRequested(){return quitRequested;}


};


#endif //TG1_ARM_DETECTION_COLOR_POINTTRACKER_H
