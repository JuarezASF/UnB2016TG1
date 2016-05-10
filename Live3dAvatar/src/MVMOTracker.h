//
// Created by jasf on 5/10/16.
//

#ifndef STEP00_MVMOTRACKER_H
#define STEP00_MVMOTRACKER_H

#include <opencv2/opencv.hpp>
#include <vector>

/***
 * Multiple View Multiple Object Tracker
 */
class MVMOTracker {

public:
    //update objects detection based on each received image
    virtual void update(const std::vector<cv::Mat> &imgs) = 0;

    //return center of object on each view
    virtual std::vector<cv::Point3d> getCenters() const = 0;

};


#endif //STEP00_MVMOTRACKER_H
