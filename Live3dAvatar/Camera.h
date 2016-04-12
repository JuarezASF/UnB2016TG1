//
// Created by rodrigo on 3/29/16.
//

#include <opencv2/opencv.hpp>
#include "HSVRangeTrackableObject.h"

#ifndef TG1_ARM_DETECTION_COLOR_CAMERA_H
#define TG1_ARM_DETECTION_COLOR_CAMERA_H


class Camera {
protected:

    static char previousCameraId;

    int cameraAngle;
    int cameraNumber;

public:

    Camera();

    virtual ~Camera();

    cv::VideoCapture cap;

    void setCamera(int);

    void setCamera(String);

    void setAngle(int);

    static char getNextCameraId();


};


#endif //TG1_ARM_DETECTION_COLOR_CAMERA_H
