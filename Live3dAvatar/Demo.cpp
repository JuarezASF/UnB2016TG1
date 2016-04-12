//
// Created by jasf on 4/4/16.
//

#include "Demo.h"
#include "Logger.h"

ColorPointTracker Demo::tracker(1);
std::unordered_map<std::string, OutputWindow> Demo::window;

Demo::Demo(std::string filename) : viewer(new pcl::visualization::PCLVisualizer("3D Viewer")), state(),
                                   quitRequested(false){
    viewer->setBackgroundColor(0, 0, 0);
    viewer->addCoordinateSystem(10.0);
    viewer->initCameraParameters();

    setCamera(filename);

    tracker.addHSVRangeToTrack(cv::Scalar(122, 77, 36), cv::Scalar(179, 255, 255), "left hand");
    tracker.addHSVRangeToTrack(cv::Scalar(95, 90, 0), cv::Scalar(130, 255, 141), "left elbow");
    tracker.addHSVRangeToTrack(cv::Scalar(41, 56, 34), cv::Scalar(103, 255, 200), "left shoulder");


}

Demo::~Demo() {

}

void Demo::run() {
    while (!viewer->wasStopped() && !quitRequested) {
        viewer->spinOnce(100);
//        boost::this_thread::sleep(boost::posix_time::microseconds(100000));

        //update input
        updateCameraStates();
        tracker.update(frameCollection);

        state.update(0.1);


        cleanVisualizer();
        updateVisualizer();



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

    std::unordered_map<std::string, boost::shared_ptr<pcl::ModelCoefficients>> cylinders = state.getCylinders();
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
        videoInputArray[idx] = boost::shared_ptr<Camera>(new Camera());

    videoInputArray[idx]->setCamera(file);

    if (!videoInputArray[idx]->cap.isOpened()) {
        Logger::err("Error on opening camera " + std::to_string(idx) + " on file " + file + " !");

        quitRequested = true;
    }

    //set frame for this camera
    frameCollection.insert(std::make_pair(idx, cv::Mat()));

}


void Demo::updateCameraStates() {
    for (auto it = videoInputArray.begin(); it != videoInputArray.end(); it++)
        it->second->cap.read(frameCollection[it->first]);
}

void Demo::setCamera(unsigned int index, unsigned int camera_index) {

    if (videoInputArray.find(index) == videoInputArray.end())
        videoInputArray[index] = boost::shared_ptr<Camera>(new Camera());

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
