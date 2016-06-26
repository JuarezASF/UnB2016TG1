//
// Created by jasf on 6/7/16.
//
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>


using namespace cv;
using namespace std;


int main() {
    std::string out_left_name = "avi/left_template.avi";
    std::string out_right_name = "avi/right_template.avi";

    cv::VideoWriter out_left, out_right;
    out_left.open(out_left_name, cv::VideoWriter::fourcc('P', 'I', 'M', '1'), 30, cv::Size(640, 640), false);
    out_right.open(out_right_name, cv::VideoWriter::fourcc('P', 'I', 'M', '1'), 30, cv::Size(640, 640), false);

    cv::aruco::Dictionary dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);

    int w = 40;
    int gap = 1;


    vector<cv::Mat> imgs;

    int ids[] = {3,4,5};
    int qtd = 3;
    for(int i = 0 ; i < qtd; i++){
        cv::Mat roi;
        cv::aruco::drawMarker(dictionary, ids[i], w, roi, 1);
        imgs.push_back(roi);

    }

    double r = 100;

    cv::Mat left, right;
    cv::Vec2d c(320, 320);
    int dd = 20;
    for(double t = 0; t < 500; t+= 0.2){
        right = 255*cv::Mat::ones(640, 640, CV_8UC1);
        left = 255*cv::Mat::ones(640, 640, CV_8UC1);
        for(int i = 0; i < imgs.size(); i++){
            const Mat &roi = imgs[i];
            double theta = 2.0*M_PI * t / 8.0 + 2.0*M_PI / qtd * i;
            cv::Vec2d d(r * cos(theta), r*sin(theta));
            cv::Vec2d p (c[0] + d[0], c[1] + d[1]);

            roi.copyTo(left(Rect((int)(p[0] + dd*(1 + i)),(int)p[1], w, w)));

            roi.copyTo(right(Rect((int)p[0],(int)p[1], w, w)));
        }

        cv::imshow("left", left);
        cv::imshow("right", right);
        char key = (char)(0xFF & cv::waitKey(33));

        //write
        out_left.write(left);
        out_right.write(right);

        if (key == 'q')
            break;



    }

    out_left.release();
    out_right.release();


    return 0;


}

