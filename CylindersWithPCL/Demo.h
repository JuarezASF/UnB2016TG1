//
// Created by jasf on 4/4/16.
//

#ifndef STEP00_DEMO_H
#define STEP00_DEMO_H


#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/common/common_headers.h>
#include "State.h"

class Demo {

protected:
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
    State state;

    void cleanVisualizer();
    void updateVisualizer();

public:

    Demo();

    virtual ~Demo();

    void run();

};


#endif //STEP00_DEMO_H
