//
// Created by jasf on 4/4/16.
//

#include "Demo.h"
#include "Logger.h"
#include "util.h"

ColorPointTracker Demo::tracker;
std::unordered_map<std::string, OutputWindow> Demo::window;

Demo::Demo(std::string filename, std::string yml_file)
        : state(), quitRequested(false) {

    viewer = new pcl::visualization::PCLVisualizer("Live 3d Avatar Visualizer");
    viewer->setBackgroundColor(0, 0, 0);
    viewer->addCoordinateSystem(10.0);
    viewer->initCameraParameters();

    setCamera(filename);

    auto connection_map = util::parseConnectionYML(yml_file);

    for (auto it = connection_map.begin(); it != connection_map.end(); it++) {
        tracker.addHSVRangeToTrack(it->second.low_hsv, it->second.high_hsv, it->first);
    }


    for (auto it = connection_map.begin(); it != connection_map.end(); it++) {
        tracker.addHSVRangeToTrack(it->second.low_hsv, it->second.high_hsv, it->first);
        for (auto iit : it->second.connections)
            state.connect(it->first, iit);
        state.setPointRange(it->second.low_hsv, it->second.high_hsv, it->first);
    }


}

Demo::~Demo() {
    if (viewer)
        delete viewer;
}

void Demo::run() {
    char c;
    while (!quitRequested) {
        viewer->spinOnce(100);
        if (viewer->wasStopped())
            break;

        updateCameraStates();
        tracker.update(frameCollection);
        if (true) {
            for (int k = 0; k < frameCollection.size(); k++) {
                cv::imshow("input " + std::to_string(k), frameCollection[k]);
            }

        }


        state.update(0.1);
        cleanVisualizer();
        updateVisualizer();



        //check for opencv input
        c = cv::waitKey(30);
        if (c == 'q' || c == 27) {
            Logger::log("esc key is pressed by user");
            quitRequested = true;
        }
    }
}

void Demo::cleanVisualizer() {
    viewer->removeAllShapes();
}

void Demo::updateVisualizer() {
    int i = 0;

    std::unordered_map<std::string, pcl::ModelCoefficients *> cylinders = state.getCylinders();
    for (auto it = cylinders.begin(); it != cylinders.end(); it++) {
        viewer->addCylinder(*(it->second), it->first);
    }

    std::unordered_map<std::string, cv::Point3d> centers = state.getCenters();
    for (auto it = centers.begin(); it != centers.end(); it++) {
        auto c = it->second;
        cv::Vec3b color = util::convert(state.pointHyerarchyMap[it->first].high_hsv, cv::COLOR_HSV2BGR);

        viewer->addSphere(pcl::PointXYZ(c.x, c.y, c.z), 10, color[2], color[1], color[0], it->first);
    }

}


OutputWindow &Demo::getOutput(std::string name) {
    if (window.find(name) == window.end())
        window[name] = OutputWindow(name);

    return window[name];
}


void Demo::setCamera(std::string file) {


    videoInputArray.push_back(new Camera(file));

    if (!videoInputArray[videoInputArray.size() - 1]->cap.isOpened()) {
        Logger::err("Error on opening camera on file " + file + " !");

        quitRequested = true;
    }

    //set frame for this camera
    frameCollection.push_back(cv::Mat());

}


void Demo::updateCameraStates() {
    for (int k = 0; k < videoInputArray.size(); k++) {
        videoInputArray[k]->cap.read(frameCollection[k]);
    }
}


std::vector<cv::Point3d> Demo::getPointsToConnect() {
    return tracker.getCenters();
}

Demo *Demo::instance = nullptr;

Demo *Demo::getInstance() {

    return instance;
}

void Demo::init(std::string filename, std::string yml_file) {
    instance = new Demo(filename, yml_file);

}
