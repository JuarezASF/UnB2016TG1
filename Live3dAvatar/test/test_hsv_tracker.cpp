//
// Created by jasf on 4/23/16.
//

#include "../src/MultipleViewPointTracker.h"
#include "RangeMultipleViewTracker.h"

void test00() {

    RangeMultipleViewTracker tracker(cv::Scalar(0, 0, 80), cv::Scalar(0, 0, 120));

    std::vector<cv::Mat *> imgs;

    cv::Mat in(100, 100, CV_8UC3, cv::Scalar(0, 0, 100));

    imgs.push_back(&in);

    tracker.update(imgs);

    cv::Point3d c = tracker.getEstimatedCenter();


    cv::Point3d expected(50, 50, 0);
    cv::Point3d err = c - expected;

    double err_mag = sqrt(err.dot(err));

    assert(err_mag < 1);

    in = cv::Mat::zeros(100, 100, CV_8UC3);

    imgs.push_back(&in);

    tracker.update(imgs);

    cv::Point3d c = tracker.getEstimatedCenter();


    cv::Point3d expected(50, 50, 0);
    cv::Point3d err = c - expected;

    double err_mag = sqrt(err.dot(err));

    assert(err_mag < 1);

};

int main() {

    test00();

}

