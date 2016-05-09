//
// Created by rodrigo on 4/30/16.
//

#include <unistd.h>
#include "Camera.h"


using namespace std;

void Camera::setTheCameras(int num1)
{
    VideoCapture capAux;
    Markers markerAux;

    numberOfCameras = 1;

    cameraLabels.push_back(0);
    cameraLabels.at(0) = num1;

    markersArray.push_back(markerAux);
    cap.push_back(capAux);

    if(cameraLabels.at(0))
        cap.at(0).open(1);
    else
        cap.at(0).open(0);

}

void Camera::setTheCameras(int num1, int num2)
{
    VideoCapture capAux;
    Markers markerAux;

    numberOfCameras = 2;

    for(int i = 0; i<= numberOfCameras; i++)
        cameraLabels.push_back(0);

    cameraLabels.at(1) = num1;
    cameraLabels.at(2) = num2;


    for(unsigned i = 0; i<= numberOfCameras; i++)
    {
        markersArray.push_back(markerAux);
        cap.push_back(capAux);
        if(i)
        {
            cap.at(i).open(i);
        }
    }


}

void Camera::setTheCameras(int num1, int num2, int num3)
{
    VideoCapture capAux;
    Markers markerAux;

    numberOfCameras = 3;

    for(int i = 0; i<= numberOfCameras; i++)
        cameraLabels.push_back(0);

    cameraLabels.at(1) = num1;
    cameraLabels.at(2) = num2;
    cameraLabels.at(3) = num3;


    for(unsigned i = 0; i<= numberOfCameras; i++)
    {
        markersArray.push_back(markerAux);
        cap.push_back(capAux);
        if(i)
        {
            cap.at(i).open(i);
        }


    }

}

void Camera::setTheCameras(int num1, int num2, int num3, int num4)
{
    VideoCapture capAux;
    Markers markerAux;

    numberOfCameras = 4;

    for(int i = 0; i<= numberOfCameras; i++)
        cameraLabels.push_back(0);

    cameraLabels.at(1) = num1;
    cameraLabels.at(2) = num2;
    cameraLabels.at(3) = num3;
    cameraLabels.at(4) = num4;


    for(unsigned i = 0; i<= numberOfCameras; i++)
    {
        markersArray.push_back(markerAux);
        cap.push_back(capAux);
        if(i)
        {
            cap.at(i).open(i);
        }

    }

}

void Camera::setTheCameras(String firstVideo, String secondVideo, int num1, int num2)
{
    VideoCapture capAux;
    Markers markerAux;

    inputIsFile = true;

    numberOfCameras = 2;

    for(int i = 0; i<= numberOfCameras; i++)
        cameraLabels.push_back(0);

    cameraLabels.at(1) = num1;
    cameraLabels.at(2) = num2;


    for(unsigned i = 0; i<= numberOfCameras; i++)
    {
        markersArray.push_back(markerAux);
        cap.push_back(capAux);
    }
    cap.at(1).open(firstVideo);
    cap.at(2).open(secondVideo);
}

void Camera::calibrateMarkers()
{

    Mat frameOriginal;
    Mat frameCalib;
    int answerCalib;

    while(true)
    {

        cout << "Go to position" << endl;

        if(!inputIsFile)
        {
            for(int j = timerCalib; j >= 0 ; j--) // timerCalib se refere a quantidade de segundos para
                // a pessoar ir para posição de calibração
            {

                cout << "\rStarting calibration in " << j << "s" << flush;
                sleep(1);
            }
        }

        else
        {
            for(int j = 0; j < filesFramesToStart; j++)
            {
                for(unsigned i = 1; i <= numberOfCameras; i++) // um loop que passa por todas as cameras
                {
                    cap.at(i) >> frameOriginal;
                }
            }
        }

        cout << endl;

        markersCalib.markersAmount = 0;

        for(int j = 0; j< numFramesCalib ; j++) //numFrames é a quantidade de frames capturados até o fim da calibração
        {
            cout << "\r" << 100*j/numFramesCalib << "%" << flush;
            if(numberOfCameras > 1) //caso estaja sendo usada mais de uma camera
            {
                for(unsigned i = 1; i <= numberOfCameras; i++) // um loop que passa por todas as cameras
                {
                    cap.at(i) >> frameOriginal;

                    windowTitle = "Original " + to_string(cameraLabels.at(i));
                    if(frameOriginal.empty())
                        break;
                    imshow(windowTitle, frameOriginal);

                    frameCalib = frameOriginal;
                    markersCalib.findAllIds(frameOriginal, frameCalib); //método que encontra todos os Ids e os
                    // relaciona as partes do corpo

                    windowTitle = "Calibration " + to_string(cameraLabels.at(i));
                    if(frameOriginal.empty())
                        break;
                    imshow(windowTitle, frameCalib);
                }
                if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
                {
                    cout << "esc key is pressed by user" << endl;
                    endProgram = true;
                    break;
                }
            }
            else
            {
                capPos = 0;
                if(cameraLabels.at(0))
                    capPos = 1;

                cap.at(capPos) >> frameOriginal;

                windowTitle = "Original " + to_string(cameraLabels.at(0));
                if(frameOriginal.empty())
                    break;
                imshow(windowTitle, frameOriginal);

                frameCalib = frameOriginal;
                markersCalib.findAllIds(frameOriginal, frameCalib);

                windowTitle = "Calibration " + to_string(cameraLabels.at(0));
                if(frameOriginal.empty())
                    break;
                imshow(windowTitle, frameCalib);

                if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
                {
                    cout << "esc key is pressed by user" << endl;
                    endProgram = true;
                    break;
                }

            }

        }

        if(endProgram)
            break;

        cout << "\r100%" << endl;

        cout << "Is the total of markers " << markersCalib.markersAmount << " (" << markersCalib.markersDistribution <<
                ")? (y/n)" << endl;

        if(inputIsFile)
        {
            answerCalib = 'y';
        }
        else
        {
            answerCalib = getchar();
            getchar();
        }

        if(answerCalib == 'y' || answerCalib == 'Y' || answerCalib == '\n')
        {
            if(!markersCalib.markersAmount)
            {
                cout << "No markers were found, calibrate again? (y/n)" << endl;
                answerCalib = getchar();
                getchar();
                if(answerCalib == 'n' || answerCalib == 'N')
                {
                    endProgram = true;
                    break;
                }
                else
                {
                    while(answerCalib != 'y' && answerCalib != 'Y' && answerCalib != '\n' && answerCalib != 'n' && answerCalib != 'N')
                    {
                        
                        cout << "Calibrate again? (y/n)" << endl;
                        answerCalib = getchar();
                        getchar();
                    }

                    if(answerCalib == 'n' || answerCalib == 'N')
                    {
                        endProgram = true;
                        break;
                    }
                }
            }
            else
                break;
        }
        else
        {
            while(answerCalib != 'n' && answerCalib != 'N' && answerCalib != 'y' && answerCalib != 'Y' && answerCalib != '\n')
            {
                cout << "Press y/n to answer if the total number of markers is " << markersCalib.markersAmount << " (" <<
                        markersCalib.markersDistribution<< ")" << endl;
                answerCalib = getchar();
                getchar();
            }

            if(answerCalib == 'y' || answerCalib == 'Y' || answerCalib == '\n')
            {
                break;
            }
        }
    }

}

void Camera::detectMarkers()  // esta método chama a detecção de marcadores enviando os frames de cada camera
{
    
    Mat imgOriginal, imgDetection;
    double f1, f2, f3, f4, x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4, z5, z6, b;
    int count, id;
    int countFrame=0;
    
    if(numberOfCameras>1) // se tem mais de uma camera então a detecção de profundidade é possível, implementei isso
        // para caso precise testar cada camera individualmente em algum aspecto
    {
        while(true)
        {
            countFrame++;

            for(unsigned i = 1; i <= numberOfCameras; i++) // um loop que passa por todas as cameras
            {
                cap.at(i) >> imgOriginal;

                windowTitle = "Original " + to_string(cameraLabels.at(i));

                if(imgOriginal.empty())
                    break;

                imshow(windowTitle, imgOriginal);

                imgDetection = imgOriginal;
                markersArray.at(i).detect(imgOriginal,imgDetection); // aqui acontece a detecção, markersArray é um
                // vetor de markers onde cada objeto markers se refere aos marcadores de cada camera

                windowTitle = "Detection " + to_string(cameraLabels.at(i));

                imshow(windowTitle, imgDetection);

                if(imgOriginal.empty())
                    break;
            }

            if(imgOriginal.empty() || imgDetection.empty())
                break;

            f1 = focal.at((unsigned)cameraLabels.at(1));
            f2 = focal.at((unsigned)cameraLabels.at(2));
            count = 0;

            switch(numberOfCameras) // aqui é calculada a distancia
            {
                case 2 : // Z = f1*f2*b/(x1*f2 - x2*f1); //fórmula base de triangulação utilizada

                    b = baseline*(cameraLabels.at(2) - cameraLabels.at(1));

                    for(unsigned i = 0; i < markersCalib.allIds.size(); i++)
                    {
                        id = markersCalib.allIds.at(i);
                        x1 = markersArray.at(1).xCenter[id];
                        x2 = markersArray.at(2).xCenter[id];
                        markerZ[id] = -f1*f2*b/(x1*f2 - x2*f1);

                        markerX[id] = x1*markerZ[id]/f1;
                        y1 = markersArray.at(1).yCenter[id];
                        markerY[id] = y1*markerZ[id]/f1;
                    }

                    break;

                case 3:
                    f3 = focal.at((unsigned)cameraLabels.at(3));


                    for(unsigned i = 0; i < markersCalib.allIds.size(); i++)
                    {
                        id = markersCalib.allIds.at(i);
                        
                        x1 = markersArray.at(1).xCenter[id];
                        x2 = markersArray.at(2).xCenter[id];
                        x3 = markersArray.at(3).xCenter[id];



                        b = baseline*(cameraLabels.at(2) - cameraLabels.at(1));
                        if(true) // estou também assumindo um Z preciso apenas se o marcador estiver visível em todas as
                            // cameras em uso, por isso o if esta sempre true (por enquanto)
                        {
                            count++;
                            z1 = f1*f2*b/(x1*f2 - x2*f1);
                        }
                        else // caso o objeto não esteja visivel o z1 é zero para não influenciar no valor final
                            z1 = 0;

                        b = baseline*(cameraLabels.at(3) - cameraLabels.at(1));
                        if(true)
                        {
                            count++;
                            z2 = f1*f3*b/(x1*f3 - x3*f1);
                        }
                        else
                            z2 = 0;

                        b = baseline*(cameraLabels.at(3) - cameraLabels.at(2));
                        if(true)
                        {
                            count++;
                            z3 = f2*f3*b/(x2*f3 - x3*f2);
                        }
                        else
                            z3 = 0;

                        if(!count)
                            markerZ[id] = -(z1+z2+z3)/count;

                        markerX[id] = x1*markerZ[id]/f1;
                        y1 = markersArray.at(1).yCenter[id];
                        markerY[id] = y1*markerZ[id]/f1;
                    }

                    break;

                case 4:
                    f3 = focal.at((unsigned)cameraLabels.at(3));
                    f4 = focal.at((unsigned)cameraLabels.at(4));

                    for(unsigned i = 0; i < markersCalib.allIds.size(); i++)
                    {
                        id = markersCalib.allIds.at(i);
                        x1 = markersArray.at(1).xCenter[id];
                        x2 = markersArray.at(2).xCenter[id];
                        x3 = markersArray.at(3).xCenter[id];
                        x4 = markersArray.at(4).xCenter[id];

                        b = baseline*(cameraLabels.at(2) - cameraLabels.at(1));
                        if(true)
                        {
                            count++;
                            z1 = f1*f2*b/(x1*f2 - x2*f1);
                        }
                        else
                            z1 = 0;

                        b = baseline*(cameraLabels.at(3) - cameraLabels.at(1));
                        if(true)
                        {
                            count++;
                            z2 = f1*f3*b/(x1*f3 - x3*f1);
                        }
                        else
                            z2 = 0;

                        b = baseline*(cameraLabels.at(4) - cameraLabels.at(1));
                        if(true)
                        {
                            count++;
                            z3 = f1*f4*b/(x1*f4 - x4*f1);
                        }
                        else
                            z3 = 0;

                        b = baseline*(cameraLabels.at(3) - cameraLabels.at(2));
                        if(true)
                        {
                            count++;
                            z4 = f2*f3*b/(x2*f3 - x3*f2);
                        }
                        else
                            z4 = 0;

                        b = baseline*(cameraLabels.at(4) - cameraLabels.at(2));
                        if(true)
                        {
                            count++;
                            z5 = f2*f4*b/(x2*f4 - x4*f2);
                        }
                        else
                            z5 = 0;

                        b = baseline*(cameraLabels.at(4) - cameraLabels.at(3));
                        if(true)
                        {
                            count++;
                            z6 = f3*f4*b/(x3*f4 - x4*f3);
                        }
                        else
                            z6 = 0;

                        if(!count)
                            markerZ[id] = -(z1+z2+z3+z4+z5+z6)/count;

                        markerX[id] = x1*markerZ[id]/f1;
                        y1 = markersArray.at(1).yCenter[id];
                        markerY[id] = y1*markerZ[id]/f1;
                    }

                    break;

                default:
                    break;
            }

//            if(countFrame%30 == 0)
//            {
//                cout << "left hand: X = " << markerX[markersCalib.leftArm.at(0)] << "\tY = " << markerY[markersCalib.leftArm.at(0)] <<
//                "\tZ = " << markerZ[markersCalib.leftArm.at(0)] << endl;
//                cout << "left elbow: X = " << markerX[markersCalib.leftArm.at(1)] << "\tY = " << markerY[markersCalib.leftArm.at(1)] <<
//                "\tZ = " << markerZ[markersCalib.leftArm.at(1)] << endl;
//                cout << "left shoulder: X = " << markerX[markersCalib.leftArm.at(2)] << "\tY = " << markerY[markersCalib.leftArm.at(2)] <<
//                "\tZ = " << markerZ[markersCalib.leftArm.at(2)] << endl;
//
//            }

            if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
            {
                cout << "esc key is pressed by user" << endl;
                break;
            }
        }
    }

    else
    {
        capPos = 0;
        if(cameraLabels.at(0))
            capPos = 1;

        while(true) {
            cap.at(capPos) >> imgOriginal;

            windowTitle = "Original " + to_string(cameraLabels.at(0));

            if (imgOriginal.empty())
                break;

            imshow(windowTitle, imgOriginal);

            imgDetection = imgOriginal;
            markersArray.at(0).detect(imgOriginal, imgDetection);

            windowTitle = "Detection " + to_string(cameraLabels.at(0));

            imshow(windowTitle, imgDetection);

            if (imgOriginal.empty())
                break;

            if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
            {
                cout << "esc key is pressed by user" << endl;
                break;
            }
        }
    }
    
}