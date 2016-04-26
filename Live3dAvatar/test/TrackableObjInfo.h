//
// Created by jasf on 4/25/16.
//

#ifndef STEP00_TRACKABLEOBJINFO_H
#define STEP00_TRACKABLEOBJINFO_H

#include <opencv2/opencv.hpp>
#include <set>
#include <string>

class TrackableObjInfo {

public:
    cv::Vec3b low_hsv, high_hsv;
    std::set<std::string> connections;

    TrackableObjInfo();
    void set_low(cv::Vec3b low);
    void set_high(cv::Vec3b low);
    void add_connection(std::string o);


};


#endif //STEP00_TRACKABLEOBJINFO_H
