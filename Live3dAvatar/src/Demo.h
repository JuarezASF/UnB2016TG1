//
// Created by jasf on 4/4/16.
//

#ifndef STEP00_DEMO_H
#define STEP00_DEMO_H

#include <string>
#include <unordered_map>
#include <Eigen/Dense>

#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/common/common_headers.h>
#include "State.h"

#include "OutputWindow.h"
#include "ColorPointTracker.h"

class Demo {

protected:
    //pcl stuff
    pcl::visualization::PCLVisualizer *viewer;
    State state;

    void cleanVisualizer();

    void updateVisualizer();

    //opencv stuff
    static ColorPointTracker tracker;
    bool quitRequested;
    static std::unordered_map<std::string, OutputWindow> window;
    std::vector<Camera*> videoInputArray;
    std::vector<cv::Mat> frameCollection;

    void updateCameraStates();

    void setCamera(std::string file);

    Demo(std::string filename, std::string yml_file);

    static Demo *instance;

public:


    static Demo *getInstance();

    static void init(std::string filename, std::string yml_file);

    virtual ~Demo();

    void run();

    static OutputWindow &getOutput(std::string name);

    static std::vector<cv::Point3d> getPointsToConnect();

};


#endif //STEP00_DEMO_H
