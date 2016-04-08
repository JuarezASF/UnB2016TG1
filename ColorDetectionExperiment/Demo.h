//
// Created by jasf on 4/7/16.
//

#ifndef TG1_ARM_DETECTION_COLOR_DEMO_H
#define TG1_ARM_DETECTION_COLOR_DEMO_H

#include <string>
#include <unordered_map>

#include "OutputWindow.h"
#include "ColorPointTracker.h"

class Demo {
protected:

    bool quitRequested;
    static std::unordered_map<std::string, OutputWindow> window;
    std::unordered_map<char , boost::shared_ptr<Camera> > videoInputArray;
    std::unordered_map<char, Mat> frameCollection;

    ColorPointTracker tracker;

    void updateCameraStates();

    void setCamera(std::string file);

    void setCamera(unsigned int index, unsigned int camera_index);


public:

    Demo(std::string filename);

    static OutputWindow &getOutput(std::string name);

    void run();

};


#endif //TG1_ARM_DETECTION_COLOR_DEMO_H
