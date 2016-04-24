//
// Created by jasf on 4/4/16.
//

#include "Demo.h"
#include "Logger.h"

ColorPointTracker Demo::tracker;
std::unordered_map<std::string, OutputWindow> Demo::window;

Demo::Demo(std::string filename, bool use3dVisualizer, bool useTrueTracking)
        : state(), using3dVisualizer(use3dVisualizer), usingTrueTracker(useTrueTracking),
          quitRequested(false) {

    if (use3dVisualizer) {
        viewer = new pcl::visualization::PCLVisualizer("Live 3d Avatar Visualizer");
        viewer->setBackgroundColor(0, 0, 0);
        viewer->addCoordinateSystem(10.0);
        viewer->initCameraParameters();
    }

    if (useTrueTracking) {
        setCamera(filename);
        displayImgProcessing = useTrueTracking;

        tracker.addHSVRangeToTrack(cv::Scalar(122, 77, 36), cv::Scalar(179, 255, 255), "left hand");
        tracker.addHSVRangeToTrack(cv::Scalar(95, 90, 0), cv::Scalar(130, 255, 141), "left elbow");
        tracker.addHSVRangeToTrack(cv::Scalar(41, 56, 34), cv::Scalar(103, 255, 200), "left shoulder");
    }


}

Demo::~Demo() {
    if (viewer)
        delete viewer;
}

void Demo::run() {
    char c;
    while (!quitRequested) {
        if (using3dVisualizer) {
            viewer->spinOnce(100);
            if(viewer->wasStopped())
                break;
        }

        //update input
        if (usingTrueTracker) {
            updateCameraStates();
            tracker.update(frameCollection);
            if (displayImgProcessing){
                for(int k = 0; k < frameCollection.size(); k++){
                    cv::imshow("input " + std::to_string(k), frameCollection[k]);
                }

            }
        }


        if (using3dVisualizer) {
            state.update(0.1);
            cleanVisualizer();
            updateVisualizer();
        }



        //check for opencv input
        c = cv::waitKey(30);
        if (c  == 'q' || c == 27){
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
        viewer->addSphere(pcl::PointXYZ(c.x, c.y, c.z), 10, 0.5, 0.5, 0.0, it->first);
    }

}


OutputWindow &Demo::getOutput(std::string name) {
    if (window.find(name) == window.end())
        window[name] = OutputWindow(name);

    return window[name];
}


void Demo::setCamera(std::string file) {


    videoInputArray.push_back( new Camera(file));

    if (!videoInputArray[videoInputArray.size()-1]->cap.isOpened()) {
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

void Demo::init(std::string filename, bool use3dVisualizer, bool useTrueTracking) {
    instance = new Demo(filename, use3dVisualizer, useTrueTracking);

}
