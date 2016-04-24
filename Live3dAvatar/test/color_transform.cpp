//
// Created by jasf on 4/23/16.
//

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;


int main(){

    Mat hsv, rgb;
    hsv = Mat::ones(1, 1, CV_8UC3);
    hsv.at<Vec3b>(0,0) = Vec3b(100,100,100);

    cvtColor(hsv, rgb, CV_HSV2BGR);

    std::cout << hsv << std::endl;
    std::cout << rgb << std::endl;





}

