//
// Created by jasf on 4/7/16.
//

#ifndef TG1_ARM_DETECTION_COLOR_OUTPUTWINDOW_H
#define TG1_ARM_DETECTION_COLOR_OUTPUTWINDOW_H

#include <string>
#include <opencv2/opencv.hpp>

class OutputWindow {
protected:
    std::string name;

public:
    OutputWindow();
    OutputWindow(std::string name);

    void display(const cv::Mat & img) const;


};


#endif //TG1_ARM_DETECTION_COLOR_OUTPUTWINDOW_H
