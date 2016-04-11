//
// Created by jasf on 4/7/16.
//

#include "Demo.h"
#include "ColorPointTracker.h"
#include "Logger.h"

std::unordered_map<std::string, OutputWindow> Demo::window;


OutputWindow &Demo::getOutput(std::string name) {
    if (window.find(name) == window.end())
        window[name] = OutputWindow(name);

    return window[name];
}

void Demo::run() {

    while (!quitRequested) {

        updateCameraStates();

        tracker.update(frameCollection);

        if (((char) waitKey(30)) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            Logger::log("esc key is pressed by user");
            quitRequested = true;
        }

    }


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
    frameCollection.insert(std::make_pair(idx, Mat()));

}

Demo::Demo(std::string filename) : quitRequested(false){
    setCamera(filename);

    tracker.addHSVRangeToTrack(Eigen::Vector3f(122, 77, 36), Eigen::Vector3f(179, 255, 255), "left hand");
    tracker.addHSVRangeToTrack(Eigen::Vector3f(95, 90, 0), Eigen::Vector3f(130, 255, 141), "left elbow");
    tracker.addHSVRangeToTrack(Eigen::Vector3f(41, 56, 34), Eigen::Vector3f(103, 255, 200), "left shoulder");


    if(false) {
        tracker.addHSVRangeToTrack(Eigen::Vector3f(103, 26, 40), Eigen::Vector3f(145, 206, 255), "right hand");
        tracker.addHSVRangeToTrack(Eigen::Vector3f(0, 80, 46), Eigen::Vector3f(37, 255, 155), "right elbow");
        tracker.addHSVRangeToTrack(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f(38, 255, 255), "right shoulder");
    }


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
