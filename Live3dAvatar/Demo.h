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
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
    State state;

    void cleanVisualizer();

    void updateVisualizer();

    //opencv stuff
    static ColorPointTracker tracker;
    bool quitRequested;
    static std::unordered_map<std::string, OutputWindow> window;
    std::unordered_map<char, boost::shared_ptr<Camera> > videoInputArray;
    std::unordered_map<char, cv::Mat> frameCollection;

    void updateCameraStates();

    void setCamera(std::string file);

    void setCamera(unsigned int index, unsigned int camera_index);


public:

    Demo(std::string filename);

    virtual ~Demo();

    void run();

    static OutputWindow &getOutput(std::string name);

    static std::vector<cv::Point3d> getPointsToConnect();

};


#endif //STEP00_DEMO_H
