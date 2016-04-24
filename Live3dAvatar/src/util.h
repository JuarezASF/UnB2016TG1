//
// Created by jasf on 4/23/16.
//

#ifndef STEP00_UTIL_H
#define STEP00_UTIL_H

#include <opencv2/opencv.hpp>
#include <vector>

class util {

public:
    static cv::Vec3b convert(cv::Scalar c, int code);

    static std::vector<cv::Vec3b> convert(std::vector<cv::Vec3b> cs, int code);

    static std::vector<cv::Vec3b> getSpacedHSVColors(int n, unsigned char s, unsigned char v);

};


#endif //STEP00_UTIL_H
