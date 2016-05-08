#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include "Camera.h"
#include "Markers.h"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{

    Camera camera;



    camera.setTheCameras(2, 4); // este método aceita até 4 inteiros como entrada, ou duas strings. Eu fiz uma implementação que aceita a conexão de qualquer combinação de camera
    // da minha plataforma já definindo as distancias focais e as baselines corretas automaticamente

    camera.calibrateMarkers();
    if(camera.endProgram)
        return 0;

    camera.detectMarkers(); //detecta os marcadores em todas as cameras, os valores de X Y Z de cada marcador
    // ficam armazenados nas variaveis do tipo map markerZ, markerX, markerY, onde as keys são as Ids dos marcadores


    return 0;
}