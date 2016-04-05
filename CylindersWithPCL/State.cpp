//
// Created by jasf on 4/3/16.
//

#include "State.h"

void State::construct(int N, float cr, float tr, float dz, float f) {
    current_time = 0;
    this->frequency = f;
    qtd_of_points = N;
    cylinder_radius = cr;
    tube_radius = tr;
    this->dz = dz;

    float theta = 0;

    for (int i = 0; i < N; i++) {
        std::string name = nameOfCenter(i);
        centers.insert(std::make_pair(name, Eigen::Vector3f(tube_radius * cos(i * 2 * M_PI / N) - tube_radius,
                                                            tube_radius * sin(i * 2 * M_PI / N), i * dz)));
    }

    fitCylindersToCenters();

}

State::State() {
    construct(16, 1, 1, 1, 1);

}

State::State(int i, float d, float d1, float d2, float frequency) {
    construct(i, d, d1, d2, frequency);

}

State::~State() {
    centers.clear();
    cylinders.clear();
}

void State::update(float dt) {
    current_time += dt;
    for (int i = 0; i < qtd_of_points; i++) {
        std::string name = nameOfCenter(i);
        centers[name](0) = tube_radius * (cos(i * 2 * M_PI / qtd_of_points + current_time * 2 * M_PI * frequency) - 1.0);
        centers[name](1) = tube_radius * sin(i * 2 * M_PI / qtd_of_points + current_time * 2 * M_PI * frequency);
        //TODO update z
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
            throw std::runtime_error("Cannor find point " + current_center_name);
        if (!checkCenterExists(next_center_name))
            throw std::runtime_error("Cannor find point " + next_center_name);


        auto current_cylinder_name = nameOfCylinder(i);
        if (cylinders.find(current_cylinder_name) == cylinders.end()) {
            cylinders[current_cylinder_name] = boost::shared_ptr<pcl::ModelCoefficients>(new pcl::ModelCoefficients());
            cylinders[current_cylinder_name]->values.resize(7);
        }

        boost::shared_ptr<pcl::ModelCoefficients> coefficients = cylinders[current_cylinder_name];

        auto center = centers[current_center_name];
        auto axis_direction = centers[next_center_name] - center;

        coefficients->values.clear();

        coefficients->values.push_back(center.x());
        coefficients->values.push_back(center.y());
        coefficients->values.push_back(center.z());

        coefficients->values.push_back(axis_direction.x());
        coefficients->values.push_back(axis_direction.y());
        coefficients->values.push_back(axis_direction.z());
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
