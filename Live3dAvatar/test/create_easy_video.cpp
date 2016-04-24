//
// Created by jasf on 4/23/16.
//

#include <opencv2/opencv.hpp>

int main(int argc, char** argv){

    std::string out_name = "avi/simple.avi";

    cv::VideoWriter out;
    out.open(out_name, cv::VideoWriter::fourcc('M','J','P','G'), 30, cv::Size(640, 480), true);

    std::vector<cv::Scalar> colors;
    std::vector<cv::Point2d> points;

    int qtdPoints = 6;
    double r = 100;

    for(int i = 0 ; i < qtdPoints; i++)
        points.push_back(cv::Point2d(240 + r*cos(2* M_PI/qtdPoints * i),320 + r*sin(2* M_PI/qtdPoints * i)));
    for(int i = 0 ; i < qtdPoints; i++)
        colors.push_back(cv::Scalar((int)20 + 220.0/qtdPoints * i, 255, 179));

    unsigned int total_time = 33*20;

    unsigned int t = 0;

    double w = M_PI;

    double rr = 20;

    double x_c = 320;
    double y_c = 240;

    cv::Mat img(480, 640, CV_8UC3);
    while(t < total_time){
        img = cv::Mat::zeros(480, 640, CV_8UC3);

        r = 100 + 20*cos(t/33.0*w);
        x_c = 320 + 50 * cos(t/33.0*2/w*2);
        y_c = 240 + 80 * sin(t/33.0*2/w*2);

        //update circle pos
        for(int i = 0 ; i < qtdPoints; i++)
            points[i] = cv::Point2d(x_c + r*cos(2* M_PI/qtdPoints * i + w * t / 33.0), y_c + r * sin(2 * M_PI / qtdPoints * i + w *
                                                                                                                                t / 33.0));

        for(int i = 0 ; i < qtdPoints; i++)
            cv::circle(img, points[i], rr, colors[i], -1);

        cv::cvtColor(img, img, CV_HSV2BGR);

        out.write(img);

        cv::imshow("writting...", img);

        t += 1;

        char c = cv::waitKey(1);
        if(c == 'q')
            break;
    }

    out.release();

    cv::VideoCapture cap("avi/simple.avi");
    cv::Mat f;

    if (cap.isOpened())
    {
        std::cout << "error" << std::endl;
    }

    while(cap.read(f)){
        cv::imshow("out", f);
        char c = cv::waitKey(33);
        if(c == 'q')
            break;

    }

}

