//
// Created by rodrigo on 3/29/16.
//

#include "Camera.h"




char Camera::previousCameraId = 0;

char Camera::getNextCameraId() {
    return previousCameraId++;
}

Camera::Camera(std::string file) {
    cameraNumber = getNextCameraId();
    cap.open(file);

}

Camera::~Camera() {
    cap.release();

}

