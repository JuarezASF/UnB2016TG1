//
// Created by jasf on 4/4/16.
//

#include "Demo.h"

Demo::Demo() : viewer(new pcl::visualization::PCLVisualizer("3D Viewer")),  state() {
    viewer->setBackgroundColor(0, 0, 0);
    viewer->addCoordinateSystem(10.0);
    viewer->initCameraParameters();
}

Demo::~Demo() {

}

void Demo::run() {
    while (!viewer->wasStopped()) {
        viewer->spinOnce(100);
        boost::this_thread::sleep(boost::posix_time::microseconds(100000));
        state.update(0.1);
        cleanVisualizer();
        updateVisualizer();
    }
}

void Demo::cleanVisualizer() {
    viewer->removeAllShapes();
}

void Demo::updateVisualizer() {
    int i = 0;

    std::unordered_map<std::string, boost::shared_ptr<pcl::ModelCoefficients>> cylinders = state.getCylinders();
    for (auto it = cylinders.begin(); it != cylinders.end(); it++) {
        viewer->addCylinder(*(it->second), it->first);
    }

    std::unordered_map<std::string, Eigen::Vector3f> centers = state.getCenters();
    for (auto it = centers.begin(); it != centers.end(); it++) {
        auto c = it->second;
        viewer->addSphere(pcl::PointXYZ(c(0), c(1), c(2)), 0.2, 0.5, 0.5, 0.0, it->first);
    }

}
