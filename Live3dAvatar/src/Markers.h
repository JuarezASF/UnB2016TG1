//
// Created by rodrigo on 4/30/16.
//

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

#ifndef TG1_MARKER_DETECTION_MARKERS_H
#define TG1_MARKER_DETECTION_MARKERS_H

using namespace cv;
using namespace std;

class Markers {

    vector<int> markerIds; // vetor de Ids dos marcadores
    vector<vector<Point2f> > markerCorners, rejectedCandidates; // aqui estarão os pontos dos cantos de cada marcador

    aruco::DetectorParameters parameters;
    aruco::Dictionary dictionary = aruco::getPredefinedDictionary(aruco::DICT_6X6_250);
    bool firstCalib = true;

public:


    vector<int> allIds;
    vector<int> leftArm;
    vector<int> rightArm;
    String markersDistribution;
    int markersAmount;
    map<int, bool> detectedId;
    map<int, double> xCenter, yCenter;
    void createMarkers(int);
    void findAllIds(Mat, Mat);
    map<int, cv::Point2d> detect(Mat, Mat);

    vector<int> getMarkersIds();
};


#endif //TG1_MARKER_DETECTION_MARKERS_H
