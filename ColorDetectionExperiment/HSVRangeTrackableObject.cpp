//
// Created by rodrigo on 3/29/16.
//

#include "HSVRangeTrackableObject.h"

void HSVRangeTrackableObject::construct()
{
    xCenter = 0;
    yCenter = 0;
    zCenter = 0;
}

HSVRangeTrackableObject::HSVRangeTrackableObject()
{
    construct();
}

HSVRangeTrackableObject::HSVRangeTrackableObject(int low_h, int high_h, int low_s, int high_s, int low_v, int high_v) {
    construct();
    setHSV(low_h, high_h, low_s, high_s, low_v, high_v);

}

void HSVRangeTrackableObject::setXCenter(double x)
{
    xCenter = x;
}

void HSVRangeTrackableObject::setYCenter(double y)
{
    yCenter = y;
}

void HSVRangeTrackableObject::setZCenter(double z)
{
    zCenter = z;
}

void HSVRangeTrackableObject::setArea(double a)
{
    area = a;
}

double HSVRangeTrackableObject::getXCenter()
{
    return xCenter;
}

double HSVRangeTrackableObject::getYCenter()
{
    return yCenter;
}

double HSVRangeTrackableObject::getZCenter()
{
    return zCenter;
}

void HSVRangeTrackableObject::setHSV(int lh, int hh, int ls, int hs, int lv, int hv)
{
    iLowH = lh;
    iHighH = hh;

    iLowS = ls;
    iHighS = hs;

    iLowV = lv;
    iHighV = hv;

}

Scalar HSVRangeTrackableObject::getHSVLow()
{
    return Scalar(iLowH, iLowS, iLowV);
}

Scalar HSVRangeTrackableObject::getHSVHigh()
{
    return Scalar(iHighH, iHighS, iHighV);
}

void HSVRangeTrackableObject::setName(String s)
{
    name = s;
}

String HSVRangeTrackableObject::getName()
{
    return name;
}

void HSVRangeTrackableObject::initializeProjectedTrajectories()
{
    projectedTrajectories.reserve(3);
}

void HSVRangeTrackableObject::findProjectedTrajectory(double xOld, double xNew, int i)
{
    projectedTrajectories[i] = xNew - xOld;
}

void HSVRangeTrackableObject::calculateRealX(int thetaCamOne, int thetaCamTwo)
{
    double thetaObject;
    double angleInRadians = CV_PI/180*(90 - thetaCamOne - thetaCamTwo);
    double trueTrajectory;


    thetaObject = atan((projectedTrajectories[2]/projectedTrajectories[1])*(1/cos(angleInRadians)) - tan(angleInRadians));
    trueTrajectory = projectedTrajectories[1]/cos(thetaObject);

    xCenter = xCenter - (sin(CV_PI/180*(90 - thetaCamOne) + thetaObject)*trueTrajectory);

}

void HSVRangeTrackableObject::calculateRealZ(int thetaCamOne, int thetaCamTwo)
{
    double thetaObject;
    double angleInRadians = CV_PI/180*(90 - thetaCamOne - thetaCamTwo);
    double trueTrajectory;


    thetaObject = atan((projectedTrajectories[2]/projectedTrajectories[1])*(1/cos(angleInRadians)) - tan(angleInRadians));
    trueTrajectory = projectedTrajectories[1]/cos(thetaObject);

    zCenter = zCenter - (cos(CV_PI/180*(90 - thetaCamOne) + thetaObject)*trueTrajectory);
}

char HSVRangeTrackableObject::previous_id = 0;

char HSVRangeTrackableObject::getNextAvailableId() {
    return ++previous_id;
}

void HSVRangeTrackableObject::setContourn(vector<Point> &c){
    contourn.clear();
    for (auto cc : c)
        contourn.push_back(cc);
}

vector<Point> &HSVRangeTrackableObject::getContourn() {
    return contourn;
}
