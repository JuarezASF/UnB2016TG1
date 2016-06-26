//
// Created by rodrigo on 4/30/16.
//

#include "Markers.h"

using namespace cv;
using namespace std;

void Markers::createMarkers(int markersNum) // este método cria os marcadores, deixei implementado aqui pra
// vc conseguir criar as imagens pra teste
{
    Mat marker;
    String outName;

//    aruco::Dictionary dictionary = aruco::getPredefinedDictionary(
//            aruco::DICT_6X6_250); // define as imagens como 6x6 (quadrados
//    // preto-branco e não pixels) usando um dicionário de 250 imagens

    for (int i = 1; i <= markersNum; ++i) {

        aruco::drawMarker(dictionary, i, 200, marker, 1); // desenha os marcadores (200x200 pixels) começando pela Id 1
        // e indo até markersNum

        outName = "marker_" + std::to_string(i);

        imshow(outName, marker);

        outName = "/home/rodrigo/ClionProjects/TG1_marker_detection/marker_" + to_string(i) + ".png"; // mude esse PATH
        // para a pasta que vc quer salvar as imagens em seu pc

        imwrite(outName, marker);

    }

    waitKey(0);
}

void Markers::findAllIds(Mat frameInput, Mat frameOutput) // encontra a quantidade de Ids e relaciona cada uma com
// cada parte do corpo
{


    detect(frameInput, frameOutput);// a detecçao retorna as ids no vetor markerIds na rdem que elas aparecem de
    // baixo para cima no frame

    int pos;

    if (markerIds.size() >= markersAmount) {
        markersAmount = (int) markerIds.size();

        for (unsigned i = 0; i < markerIds.size(); i++) {
            allIds.push_back(markerIds.at(i));
        }

        if (markersAmount == 3) // estou assumindo braço esquerdo para 3 marcadores
        {
            markersDistribution = "three markers on the left arm";
            if (firstCalib) {
                for (unsigned i = 0; i < markerIds.size(); i++)
                    leftArm.push_back(0);

            }
            pos = (yCenter[markerIds.at(0)] < yCenter[markerIds.at(1)]) +
                  (yCenter[markerIds.at(0)] < yCenter[markerIds.at(2)]);
            leftArm.at((unsigned) pos) = markerIds.at(0);
            pos = (yCenter[markerIds.at(1)] < yCenter[markerIds.at(0)]) +
                  (yCenter[markerIds.at(1)] < yCenter[markerIds.at(2)]);
            leftArm.at((unsigned) pos) = markerIds.at(1);
            pos = (yCenter[markerIds.at(2)] < yCenter[markerIds.at(0)]) +
                  (yCenter[markerIds.at(2)] < yCenter[markerIds.at(1)]);
            leftArm.at((unsigned) pos) = markerIds.at(2);

            firstCalib = false;
        }

        if (markersAmount == 6) //estou assumindo dois braços para 6 marcadores
        {
            markersDistribution = "three markers on each arm";

            if (xCenter[markerIds.at(0)] < xCenter[markerIds.at(1)]) //o menor valor de x se refere ao braço esquerdo
            {
                leftArm.push_back(markerIds.at(0));
                rightArm.push_back(markerIds.at(1));
            }
            else {
                leftArm.push_back(markerIds.at(1));
                rightArm.push_back(markerIds.at(0));
            }

            if (xCenter[markerIds.at(2)] < xCenter[markerIds.at(3)]) {
                leftArm.push_back(markerIds.at(2));
                rightArm.push_back(markerIds.at(3));
            }
            else {
                leftArm.push_back(markerIds.at(3));
                rightArm.push_back(markerIds.at(2));
            }

            if (xCenter[markerIds.at(4)] < xCenter[markerIds.at(5)]) {
                leftArm.push_back(markerIds.at(4));
                rightArm.push_back(markerIds.at(5));
            }
            else {
                leftArm.push_back(markerIds.at(5));
                rightArm.push_back(markerIds.at(4));
            }

        }

    }

    if (markersAmount == 0) {
        markersDistribution = "no markers";
    }


}

map<int, cv::Point2d> Markers::detect(Mat imgO, Mat imgD) {

    map<int, cv::Point2d> out;

    aruco::detectMarkers(imgO, dictionary, markerCorners, markerIds, parameters, rejectedCandidates);

    aruco::drawDetectedMarkers(imgD, markerCorners, markerIds);


    double x, y;

    //for each marker, find its center as the averages of its corners
    for (unsigned i = 0; i < markerIds.size(); i++)
    {

        int id = markerIds[i];
        x = (markerCorners.at(i)[0].x + markerCorners.at(i)[1].x +
                  markerCorners.at(i)[2].x + markerCorners.at(i)[3].x) / 4;

        y = (markerCorners.at(i)[0].y + markerCorners.at(i)[1].y +
                  markerCorners.at(i)[2].y + markerCorners.at(i)[3].y) / 4;

        //set the corresponding position
        out[id] = cv::Point2d(x,y);
    }

    return out;

}

vector<int> Markers::getMarkersIds() {
    return markerIds;
}
