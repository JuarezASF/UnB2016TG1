//
// Created by jasf on 4/7/16.
//

#ifndef TG1_ARM_DETECTION_COLOR_POINTTRACKER_H
#define TG1_ARM_DETECTION_COLOR_POINTTRACKER_H

#include <eigen3/Eigen/Dense>
#include <vector>
#include <opencv2/core/mat.hpp>
#include <unordered_map>

class MultipleViewPointTracker {

protected:
    bool quitRequested;
    std::vector<cv::Point3d> measuredCenters;
    cv::Point3d estimatedCenter;

public:

    //update objects detection based on each received image
    virtual void update(const std::vector<cv::Mat> &imgs) = 0;

    //return center of object on each view
    virtual std::vector<cv::Point3d> getCenters() const = 0;
    virtual cv::Point3d getEstimatedCenter() const = 0;



    inline bool getQuitRequested() { return quitRequested; }


};


#endif //TG1_ARM_DETECTION_COLOR_POINTTRACKER_H
