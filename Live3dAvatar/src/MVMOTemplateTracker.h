//
// Created by jasf on 5/10/16.
//

#ifndef STEP00_MVMOTEMPLATETRACKER_H
#define STEP00_MVMOTEMPLATETRACKER_H

#include <opencv2/opencv.hpp>
#include <vector>
#include "Markers.h"
#include "MVMOTracker.h"

class MVMOTemplateTracker : public MVMOTracker{

    bool quitRequested;

    vector<Markers> markerArray;
    Markers markersCalib;
    std::vector<std::string> markers_labels;

public:
    //update objects detection based on each received image
    virtual void update(const std::vector<cv::Mat> &imgs);

    //return center of object on each view
    virtual std::vector<cv::Point3d> getCenters() const;

    void calibrateMarkers(std::vector<cv::VideoCapture> cap, int framesToSkip,
                              int qtdFrames2CalibreFrom, int qtdMarkersToTrack);


};


#endif //STEP00_MVMOTEMPLATETRACKER_H
