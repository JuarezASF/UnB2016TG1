//
// Created by jasf on 4/4/16.
//

#include <string>
#include "Demo.h"
#include "Logger.h"
#include "util.h"
#include "MultipleViewMerger.h"

MOTemplateTracker Demo::tracker;
std::unordered_map<std::string, OutputWindow> Demo::window;

Demo::Demo(std::string yml_file)
        : state(), quitRequested(false) {

    viewer = new pcl::visualization::PCLVisualizer("Live 3d Avatar Visualizer");
    viewer->setBackgroundColor(0, 0, 0);
    viewer->addCoordinateSystem(10.0);
    viewer->initCameraParameters();

    std::cout << yml_file << endl;

    cv::FileStorage fs(yml_file, cv::FileStorage::READ);

    if (!fs.isOpened()) {
        std::cerr << "cannot open config file named " << yml_file << endl;
        exit(0);
    }

    qtdCameras = (int) fs["qtdInput"];

    for (int k = 0; k < qtdCameras; k++) {

        std::stringstream argnameBuilder;

        argnameBuilder << "input" << std::setfill('0') << std::setw(2) << k;

        std::string argname = argnameBuilder.str();

        std::string cameraFilename = (std::string) fs[argname];

        setCamera(cameraFilename);

        std::string fArgName = "f" + std::to_string(k);

        focal.push_back((double) fs[fArgName]);

    }

    baseline = (double) fs["baseline"];
    qtdObjectsBeingTracker = (int) fs["qtdObjects"];

    //skip a few frames
    for (int k = 0; k < 30; k++)
        updateCameraStates();

    std::unordered_map<std::string, TrackableObjInfo> connection_map = util::parseConnectionYML(yml_file);
    state.setHyerarhcyMap(connection_map);

    cout << "Hyerarchy map build" << endl;
    state.printHyerarchyMap();

    MultipleViewMerger::setBaseline(baseline);

}

Demo::~Demo() {
    if (viewer)
        delete viewer;
}

void Demo::run() {
    char c;
    while (!quitRequested) {
        viewer->spinOnce(100);
        if (viewer->wasStopped())
            break;

        updateCameraStates();
        tracker.update(frameCollection);
        for (int k = 0; k < frameCollection.size(); k++) {
            cv::imshow("input " + std::to_string(k), frameCollection[k]);
        }


        state.update(0.1);
        cleanVisualizer();
        updateVisualizer();



        //check for opencv input
        c = cv::waitKey(5);
        if (c == 'q' || c == 27) {
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
        cv::Vec3b color = ((TrackableObjInfo) state.pointHyerarchyMap[it->first]).colorToPaintObject;

        viewer->addSphere(pcl::PointXYZ(c.x, c.y, c.z), 10, color[0] / 255.0, color[1] / 255.0, color[2] / 255.0,
                          it->first);
    }

}


OutputWindow &Demo::getOutput(std::string name) {
    if (window.find(name) == window.end())
        window[name] = OutputWindow(name);

    return window[name];
}


void Demo::setCamera(std::string file) {


    videoInputArray.push_back(new Camera(file));

    if (!videoInputArray[videoInputArray.size() - 1]->cap.isOpened()) {
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


std::map<int, cv::Point3d> Demo::getPointsToConnect() {
    return tracker.getCenters();
}

Demo *Demo::instance = nullptr;

Demo *Demo::getInstance() {

    return instance;
}

void Demo::init(std::string yml_file) {
    instance = new Demo(yml_file);

}
