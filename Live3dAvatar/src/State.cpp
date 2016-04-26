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
    for (int k = 0; k < points.size(); k++) {
        c_name = nameOfCenter(c++);
        centers[c_name] = points[k];
    }

    fitCylindersToCenters();

}


void State::fitCylindersToCenters() {
    int cylinder_count = 0;

    for (int i = 0; i < centers.size(); i++) {
        auto current_center_name = nameOfCenter(i);

        if(pointHyerarchyMap.find(current_center_name) == pointHyerarchyMap.end()){
            pointHyerarchyMap[current_center_name] = TrackableObjInfo();
        }

        for (auto toConnect : pointHyerarchyMap[current_center_name].connections) {
            auto current_cylinder_name = nameOfCylinder(cylinder_count++);
            if (cylinders.find(current_cylinder_name) == cylinders.end()) {
                cylinders[current_cylinder_name] = new pcl::ModelCoefficients();
                cylinders[current_cylinder_name]->values.resize(7);
            }
            pcl::ModelCoefficients *coefficients = cylinders[current_cylinder_name];
            auto center = centers[current_center_name];
            auto axis_direction = centers[toConnect] - center;

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

void State::connect(std::string A, std::string B) {

    if (pointHyerarchyMap.find(A) == pointHyerarchyMap.end()) {
        pointHyerarchyMap[A] = TrackableObjInfo();
    }

    pointHyerarchyMap[A].add_connection(B);

    if (pointHyerarchyMap.find(B) == pointHyerarchyMap.end()) {
        pointHyerarchyMap[B] = TrackableObjInfo();
    }

    pointHyerarchyMap[B].add_connection(A);

}

void State::setPointRange(cv::Vec3b low, cv::Vec3b high, std::string name) {
    if (pointHyerarchyMap.find(name) == pointHyerarchyMap.end()) {
        pointHyerarchyMap[name] = TrackableObjInfo();
    }

    pointHyerarchyMap[name].set_low(low);
    pointHyerarchyMap[name].set_high(high);



}
