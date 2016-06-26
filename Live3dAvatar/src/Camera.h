//
// Created by rodrigo on 3/29/16.
//

#include <opencv2/opencv.hpp>
#include "RangeMultipleViewTracker.h"

#ifndef TG1_ARM_DETECTION_COLOR_CAMERA_H
#define TG1_ARM_DETECTION_COLOR_CAMERA_H


class Camera {
protected:

    static char previousCameraId;

    int cameraAngle;
    int cameraNumber;

    static char getNextCameraId();

public:

    Camera(std::string filename);

    virtual ~Camera();

    cv::VideoCapture cap;

};


#endif //TG1_ARM_DETECTION_COLOR_CAMERA_H
