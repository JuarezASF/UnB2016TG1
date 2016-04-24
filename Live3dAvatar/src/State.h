//
// Created by jasf on 4/3/16.
//

#ifndef STEP00_STATE_H
#define STEP00_STATE_H

#include <pcl/visualization/pcl_visualizer.h>

#include <opencv2/core.hpp>

#include <unordered_map>
#include <string>
#include <exception>

class State {
protected:
    std::unordered_map<std::string, pcl::ModelCoefficients*> cylinders;
    std::unordered_map<std::string, cv::Point3d> centers;

    float cylinder_radius, current_time;

    void construct(float cr);

    void fitCylindersToCenters();

    std::string nameOfCenter(int d);

    std::string nameOfCylinder(int d);

    bool checkCenterExists(std::string name);

    bool checkCylinderExists(std::string name);


public:
    State();

    State(float cylinder_radius);

    virtual ~State();

    void update(float dt);

    inline std::unordered_map<std::string, pcl::ModelCoefficients*> getCylinders() { return cylinders; }

    inline std::unordered_map<std::string, cv::Point3d> getCenters() { return centers; }

};


#endif //STEP00_STATE_H
