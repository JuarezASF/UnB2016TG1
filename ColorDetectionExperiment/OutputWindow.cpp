//
// Created by jasf on 4/7/16.
//

#include "OutputWindow.h"

OutputWindow::OutputWindow(std::string name) : name(name) {

}

OutputWindow::OutputWindow() : name("default") {

}

void OutputWindow::display(const cv::Mat &img) const {
    cv::imshow(name, img);

}
