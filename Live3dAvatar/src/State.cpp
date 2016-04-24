//
// Created by jasf on 4/3/16.
//

#include "State.h"
#include "Demo.h"

void State::construct(float cr) {
    cylinder_radius = cr;


}

State::State() {
    construct(1);

}

State::State(float d) {
    construct(d);

}

State::~State() {
    centers.clear();
    cylinders.clear();
}

void State::update(float dt) {
    current_time += dt;
    std::vector<cv::Point3d> points = Demo::getPointsToConnect();
    int c = 0;
    std::string c_name;
    for (int k = 0 ; k < points.size(); k++) {
        c_name = nameOfCenter(c++);
        centers[c_name] = points[k];
    }

    fitCylindersToCenters();

}


void State::fitCylindersToCenters() {
    for (int i = 0; i < centers.size(); i++) {
        auto current_center_name = nameOfCenter(i);
        auto next_center_name = nameOfCenter((i + 1) % centers.size());

        //the last point is the start point of no cilinder
        if (i == centers.size() - 1)
            break;

        if (!checkCenterExists(current_center_name))
            throw std::runtime_error("Cannot find point " + current_center_name);
        if (!checkCenterExists(next_center_name))
            throw std::runtime_error("Cannot find point " + next_center_name);


        auto current_cylinder_name = nameOfCylinder(i);
        if (cylinders.find(current_cylinder_name) == cylinders.end()) {
            cylinders[current_cylinder_name] = new pcl::ModelCoefficients();
            cylinders[current_cylinder_name]->values.resize(7);
        }

        pcl::ModelCoefficients* coefficients = cylinders[current_cylinder_name];

        auto center = centers[current_center_name];
        auto axis_direction = centers[next_center_name] - center;

        coefficients->values.clear();

        coefficients->values.push_back(center.x);
        coefficients->values.push_back(center.y);
        coefficients->values.push_back(center.z);

        coefficients->values.push_back(axis_direction.x);
        coefficients->values.push_back(axis_direction.y);
        coefficients->values.push_back(axis_direction.z);
        coefficients->values.push_back(cylinder_radius);

    }

}

std::string State::nameOfCenter(int d) {
    return "center#" + std::to_string(d);
}

std::string State::nameOfCylinder(int d) {
    return "cylinder#" + std::to_string(d);
}

bool State::checkCenterExists(std::string name) {
    return centers.find(name) != centers.end();
}

bool State::checkCylinderExists(std::string name) {
    return cylinders.find(name) != cylinders.end();
}
