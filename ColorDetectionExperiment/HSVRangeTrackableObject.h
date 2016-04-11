//
// Created by rodrigo on 3/29/16.
//

#include <opencv2/opencv.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>

#ifndef TG1_ARM_DETECTION_COLOR_ARM_H
#define TG1_ARM_DETECTION_COLOR_ARM_H

using namespace std;
using namespace cv;

class HSVRangeTrackableObject {

    static char previous_id;

    double xCenter, yCenter, zCenter, area;

    int iLowH;
    int iHighH;

    int iLowS;
    int iHighS;

    int iLowV;
    int iHighV;

    vector<double> projectedTrajectories;

    vector<Point> contourn;

    String name;

    void construct();

public:

    static char getNextAvailableId();

    HSVRangeTrackableObject();

    HSVRangeTrackableObject(int low_h, int high_h, int low_s, int high_s, int low_v, int high_v);

    void setXCenter(double);

    void setYCenter(double);

    void setZCenter(double);

    void setArea(double);

    void setHSV(int, int, int, int, int, int);

    Scalar getHSVLow();

    Scalar getHSVHigh();

    void setName(String);

    String getName();

    double getXCenter();

    double getYCenter();

    double getZCenter();

    void initializeProjectedTrajectories();

    void findProjectedTrajectory(double, double, int);

    void calculateRealX(int, int);

    void calculateRealZ(int, int);

    void setContourn(vector<Point> &c);

    vector<Point> & getContourn();

};


#endif //TG1_ARM_DETECTION_COLOR_ARM_H
