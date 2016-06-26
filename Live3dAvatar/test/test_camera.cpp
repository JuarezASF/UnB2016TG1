//
// Created by jasf on 4/23/16.
//

#include "../src/Camera.h"

void test00() {

    std::vector<cv::Mat> imgs;


    int qtdOfCameras = 2;
    for (int k = 0; k < qtdOfCameras; k++)
        imgs.push_back(cv::Mat());

    Camera c1("avi/input00.avi");
    Camera c2("avi/input.avi");

    cv::Mat f1, f2;

    bool b1, b2;
    b1 = c1.cap.read(imgs[0]);
    b2 = c2.cap.read(imgs[1]);

    while (b1 && b2) {
        b1 = c1.cap.read(imgs[0]);
        b2 = c2.cap.read(imgs[1]);

        cv::imshow("out 1", imgs[0]);
        cv::imshow("out 2", imgs[1]);

        char c = cv::waitKey(33);
        if (c == 'q')
            break;
    }


}

void test01() {

    cv::VideoCapture cap;

    cap.open("avi/input.avi");

    cv::Mat f;

    while (cap.read(f)) {
        cv::imshow("out", f);

        char c = cv::waitKey(33);
        if (c == 'q')
            break;
    }

    cap.release();

}

int main() {
    test00();

    return 0;
}
