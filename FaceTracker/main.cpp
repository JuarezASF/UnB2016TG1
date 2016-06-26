#include <iostream>
#include <tracker/FaceTracker.hpp>
#include <opencv2/highgui.hpp>


using namespace std;

int main() {

    //loads tracker and its parameters
    FACETRACKER::FaceTracker *tracker = FACETRACKER::LoadFaceTracker();
    if (tracker == nullptr) {
        cerr << "Cannot load tracker!" << endl;
        return 0;
    }
    FACETRACKER::FaceTrackerParams *params = FACETRACKER::LoadFaceTrackerParams();

    if (params == nullptr) {
        cerr << "Cannot load tracker params!" << endl;
        return 0;

    }

    cv::VideoCapture cam(0);

    if (!cam.isOpened()) {
        cerr << "cannot open camera!" << endl;
        return 0;
    }

    bool shouldFinish = false;

    //frame is used for web cam input; but the CSIRO face detection works only on gray scale images
    cv::Mat frame, grayScale;
    int detectionQuality;

    cout << "press 'q' to quit" << endl;
    while (!shouldFinish) {
        cam >> frame;

        cv::cvtColor(frame, grayScale, cv::COLOR_BGR2GRAY);

        //update state of tracker with new frame
        detectionQuality = tracker->NewFrame(grayScale, params);

        if (detectionQuality == 0 || detectionQuality == FACETRACKER::FaceTracker::TRACKER_FAILED) {
            tracker->Reset();
        }

        cout << "Detection quality is: " << detectionQuality << endl;

        //obtain points that were tracked
        auto points = tracker->getShape();

        //draw point on input frame
        for (auto p : points) {
            cv::circle(frame, p, 2, cv::Scalar(255, 0, 0), 2);
        }
        cv::imshow("input", frame);

        if (char q = (char) (cv::waitKey(30) & 0xFF) == 'q') {
            shouldFinish = true;
        }


    }


    return 0;
}