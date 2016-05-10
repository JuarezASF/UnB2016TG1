//
// Created by jasf on 5/10/16.
//

#include "MVMOTemplateTracker.h"
#include "Logger.h"

void MVMOTemplateTracker::calibrateMarkers(std::vector<cv::VideoCapture> cap, int framesToSkip,
                                           int qtdFrames2CalibreFrom, int qtdMarkersToTrack) {
    Mat frameOriginal;
    Mat frameCalib;
    int answerCalib;

    while (true) {

        cout << "Go to position" << endl;

        Logger::log("skiping first " + to_string(framesToSkip) + "frames");

        for (int j = 0; j < framesToSkip; j++) {
            for (unsigned i = 0; i < cap.size(); i++) {
                cap[i] >> frameOriginal;
            }
        }

        markersCalib.markersAmount = qtdMarkersToTrack;
        // calibrate using a few frames
        for (int j = 0; j < qtdFrames2CalibreFrom; j++) {
            cout << "\r" << 100 * j / qtdFrames2CalibreFrom << "%" << flush;

            //case of multiple cameras
            for (unsigned i = 0; i < cap.size(); i++) {
                cap[i] >> frameOriginal;

                string windowTitle = "Original " + to_string(i);
                if (frameOriginal.empty())
                    break;
                imshow(windowTitle, frameOriginal);

                frameCalib = frameOriginal;

                markersCalib.findAllIds(frameOriginal, frameCalib);

                // show frame used for calib
                windowTitle = "Calibration " + to_string(i);
                imshow(windowTitle, frameCalib);
            }
            if ((char) waitKey(30) == 'q') //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
            {
                cout << "esc key is pressed by user" << endl;
                quitRequested = true;
                break;
            }

        }

        if (quitRequested)
            break;

        cout << "\r100%" << endl;

    }

}
