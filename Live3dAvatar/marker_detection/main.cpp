#include <iostream>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include "Camera.h"

using namespace cv;
using namespace std;

int main(int argc, char **argv) {

    string configFile = "";

    if (const char *env_config_file = std::getenv("MARKER_CONFIG_FILE")) {
        configFile = string(env_config_file);
    }

    if (configFile.empty()) {
        configFile = "config.yml";
    }

    cout << "configuration being read from: " << configFile << endl;


    FileStorage fs("config.yml", FileStorage::READ);
    string videoFile1 = (string) fs["input01"];
    string videoFile2 = (string) fs["input02"];
    fs.release();

    cout << "video 1 being read from: " << videoFile1 << endl;
    cout << "video 2 being read from: " << videoFile2 << endl;

    Camera camera;
    camera.setTheCameras(videoFile1, videoFile2, 3, 4);

    camera.calibrateMarkers();
    if (camera.endProgram)
        return 0;

    camera.detectMarkers(); //detecta os marcadores em todas as cameras, os valores de X Y Z de cada marcador
    // ficam armazenados nas variaveis do tipo map markerZ, markerX, markerY, onde as keys são as Ids dos marcadores


    return 0;
}