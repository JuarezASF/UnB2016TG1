//
// Created by rodrigo on 4/30/16.
//

#include <opencv2/opencv.hpp>
#include "Markers.h"

#ifndef TG1_MARKER_DETECTION_CAMERA_H
#define TG1_MARKER_DETECTION_CAMERA_H

using namespace cv;

class Camera {


    int timerCalib = 2;
    int numFramesCalib = 120;

    bool inputIsFile = false;
    int numberOfCameras;
    double baseline = 18;
    Markers markersCalib;
    vector<double > focal {0, (838.202721973366010 + 841.388786651687380)/2, (854.792781659906610 + 857.614193372593600)/2,
            (834.378121568220080 + 835.838850269775660) / 2, (840.061263941844910 + 841.195974132470720)/2};
    vector<Markers> markersArray;
    vector<int> cameraLabels;
    vector<VideoCapture> cap;

    unsigned capPos;
    String windowTitle;


public:

    map<int, double> markerZ, markerX, markerY;
    bool endProgram = false;

    void setTheCameras(int);
    void setTheCameras(int, int);
    void setTheCameras(int, int, int);
    void setTheCameras(int, int, int, int);
    void setTheCameras(String, String, int, int);
    void calibrateMarkers();
    void detectMarkers();



};


#endif //TG1_MARKER_DETECTION_CAMERA_H
