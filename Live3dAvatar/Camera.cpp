//
// Created by rodrigo on 3/29/16.
//

#include "Camera.h"

using namespace std;

void Camera::setCamera(int i) {

    cameraNumber = i;
    cap.open(i);

}

void Camera::setCamera(std::string file) {

    cameraNumber = 0;
    cap.open(file);

}

void Camera::setAngle(int theta) {
    cameraAngle = theta;
}


char Camera::previousCameraId = 0;

char Camera::getNextCameraId() {
    return ++previousCameraId;
}

Camera::Camera() {

}

Camera::~Camera() {

}
