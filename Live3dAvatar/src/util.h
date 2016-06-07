//
// Created by jasf on 4/23/16.
//

#ifndef STEP00_UTIL_H
#define STEP00_UTIL_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <set>
#include <unordered_map>
#include "TrackableObjInfo.h"

class util {

public:
    static cv::Vec3b convert(cv::Scalar c, int code);

    static std::vector<cv::Vec3b> convert(std::vector<cv::Vec3b> cs, int code);

    static std::vector<cv::Vec3b> getSpacedHSVColors(int n, unsigned char s, unsigned char v);

    static std::unordered_map<std::string, TrackableObjInfo> parseConnectionYML(std::string filename);

    static cv::Vec3b readVec3b(cv::FileNode node);

};


#endif //STEP00_UTIL_H
