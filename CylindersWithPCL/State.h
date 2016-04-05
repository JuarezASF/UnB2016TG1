//
// Created by jasf on 4/3/16.
//

#ifndef STEP00_STATE_H
#define STEP00_STATE_H

#include <Eigen/Dense>
#include <pcl/visualization/pcl_visualizer.h>

#include <unordered_map>
#include <string>
#include <exception>

class State {
protected:
    std::unordered_map<std::string, boost::shared_ptr<pcl::ModelCoefficients>> cylinders;
    std::unordered_map<std::string, Eigen::Vector3f> centers;

    int qtd_of_points;
    float cylinder_radius, tube_radius, dz, current_time, frequency;

    void construct(int N, float cr, float tr, float dz, float f);

    void fitCylindersToCenters();

    std::string nameOfCenter(int d);
    std::string nameOfCylinder(int d);

    bool checkCenterExists(std::string name);
    bool checkCylinderExists(std::string name);


public:
    State();
    State(int qtd_of_points, float cylinder_radius, float rube_radius, float dz, float frequency);

    virtual ~State();

    void update(float dt);

    inline std::unordered_map<std::string, boost::shared_ptr<pcl::ModelCoefficients>> getCylinders(){return cylinders;}
    inline std::unordered_map<std::string, Eigen::Vector3f> getCenters(){return centers;}

};


#endif //STEP00_STATE_H
