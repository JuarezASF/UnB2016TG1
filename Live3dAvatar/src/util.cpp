//
// Created by jasf on 4/23/16.
//

#include "util.h"

cv::Vec3b util::convert(cv::Scalar c, int code) {
    cv::Mat a(1, 1, CV_8UC3);
    a.at<cv::Vec3b>(0,0) = cv::Vec3b(c[0], c[1], c[2]);
    cv::cvtColor(a, a, code);
    return a.at<cv::Vec3b>(0,0);
}

std::vector<cv::Vec3b> util::convert(std::vector<cv::Vec3b> cs, int code) {
    std::vector<cv::Vec3b> out;
    cv::Mat a(1, cs.size(), CV_8UC3);
    for( int k = 0; k < cs.size(); k++)
        a.at<cv::Vec3b>(0,k) = cv::Vec3b(cs[k][0], cs[k][1], cs[k][2]);
    cv::cvtColor(a, a, code);
    for( int k = 0; k < cs.size(); k++)
        out.push_back(a.at<cv::Vec3b>(0,k));

    return out;
}

std::vector<cv::Vec3b> util::getSpacedHSVColors(int n, unsigned char s, unsigned char v) {
    std::vector<cv::Vec3b> out;
    float step = 255.0/n;

    for (int k = 0; k < n; k++)
        out.push_back(cv::Vec3b((int) (step*k + 0.5), s, v);

    return out;
}
