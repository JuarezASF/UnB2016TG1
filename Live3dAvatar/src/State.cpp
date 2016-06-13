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
    std::map<int, cv::Point3d> markerIdPointMap = Demo::getPointsToConnect();
    std::vector<cv::Point3d> points;

    for (int k = 0; k < Demo::getInstance()->getQtdObjectsBeingTracked(); k++) {
        std::string c_name = nameOfCenter(k);
        points.push_back(markerIdPointMap[pointHyerarchyMap.find(c_name)->second.markerId]);

    }

    if (!points.empty()) {
        std::string c_name;
        for (int k = 0; k < points.size(); k++) {
            c_name = nameOfCenter(k);

            cv::Point3_<double> &o = points[k];
            centers[c_name] = cv::Point3d(-1 * o.x, -1.0 * o.y, -1.0 * o.z);
        }

        fitCylindersToCenters();

    }

}


void State::fitCylindersToCenters() {
    int cylinder_count = 0;

    for (int i = 0; i < centers.size(); i++) {
        auto current_center_name = nameOfCenter(i);

        if (pointHyerarchyMap.find(current_center_name) == pointHyerarchyMap.end()) {
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

    ((TrackableObjInfo) pointHyerarchyMap[A]).add_connection(B);

    if (pointHyerarchyMap.find(B) == pointHyerarchyMap.end()) {
        pointHyerarchyMap[B] = TrackableObjInfo();
    }

    ((TrackableObjInfo) pointHyerarchyMap[B]).add_connection(A);

}

void State::printHyerarchyMap() {

    for (const auto &it : pointHyerarchyMap) {
        cout << it.first << "\tmarkerId:" << ((TrackableObjInfo) it.second).markerId << "\tcolor" <<
        ((TrackableObjInfo) it.second).colorToPaintObject << std::endl;
        ((TrackableObjInfo) it.second).printConnections();
    }

}

void State::setHyerarhcyMap(std::unordered_map<std::string, TrackableObjInfo> map) {

    pointHyerarchyMap.clear();

    for (auto it : map) {
        pointHyerarchyMap[it.first] = it.second;
    }

}
