//
// Created by jasf on 4/4/16.
//

#include "Demo.h"
#include "Logger.h"

ColorPointTracker Demo::tracker(1);
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

        tracker.addHSVRangeToTrack(cv::Scalar(122, 77, 36), cv::Scalar(179, 255, 255), "left hand");
//        tracker.addHSVRangeToTrack(cv::Scalar(95, 90, 0), cv::Scalar(130, 255, 141), "left elbow");
//        tracker.addHSVRangeToTrack(cv::Scalar(41, 56, 34), cv::Scalar(103, 255, 200), "left shoulder");
    }


}

Demo::~Demo() {
    if (viewer)
        delete viewer;
}

void Demo::run() {
    while (!quitRequested) {
        if (using3dVisualizer) {
            viewer->spinOnce(100);
            if(viewer->wasStopped())
                break;
        }
//        boost::this_thread::sleep(boost::posix_time::microseconds(100000));

        //update input
        if (usingTrueTracker) {
            updateCameraStates();
            tracker.update(frameCollection);
        }


        if (using3dVisualizer) {
            state.update(0.1);
            cleanVisualizer();
            updateVisualizer();
        }



        //check for opencv input
        if (((char) cv::waitKey(30)) == 27) {
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

    std::unordered_map<std::string, Eigen::Vector3f> centers = state.getCenters();
    for (auto it = centers.begin(); it != centers.end(); it++) {
        auto c = it->second;
        viewer->addSphere(pcl::PointXYZ(c(0), c(1), c(2)), 10, 0.5, 0.5, 0.0, it->first);
    }

}


OutputWindow &Demo::getOutput(std::string name) {
    if (window.find(name) == window.end())
        window[name] = OutputWindow(name);

    return window[name];
}


void Demo::setCamera(std::string file) {
    char idx = Camera::getNextCameraId();

    if (videoInputArray.find(idx) == videoInputArray.end())
        videoInputArray[idx] = new Camera();

    videoInputArray[idx]->setCamera(file);

    if (!videoInputArray[idx]->cap.isOpened()) {
        Logger::err("Error on opening camera " + std::to_string(idx) + " on file " + file + " !");

        quitRequested = true;
    }

    //set frame for this camera
    frameCollection.insert(std::make_pair(idx, cv::Mat()));

}


void Demo::updateCameraStates() {
    for (auto it = videoInputArray.begin(); it != videoInputArray.end(); it++) {
        it->second->cap.read(frameCollection[it->first]);
        cv::imshow("debug", frameCollection[it->first]);
    }
}

void Demo::setCamera(unsigned int index, unsigned int camera_index) {

    if (videoInputArray.find(index) == videoInputArray.end())
        videoInputArray[index] = new Camera();

    videoInputArray[index]->setCamera(camera_index);

    if (!videoInputArray[index]->cap.isOpened()) {
        Logger::err("Error on opening camera " + std::to_string(index) + " on camera " + std::to_string(camera_index) +
                    " !");
        quitRequested = true;
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
