//
// Created by jasf on 4/23/16.
//

#include <opencv2/opencv.hpp>
#include <set>

int main(int argc, char **argv) {

    std::string out_left_name = "avi/left.avi";
    std::string out_right_name = "avi/right.avi";

    cv::VideoWriter out_left, out_right;
    out_left.open(out_left_name, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(640, 480), true);
    out_right.open(out_right_name, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(640, 480), true);

    std::vector<cv::Vec3b> colors;
    std::vector<cv::Point2d> points;
    std::vector<double> offsets_x;
    std::vector<std::string> names;
    std::vector<std::string> connectedTo;

    int qtdPoints = 8;
    double r = 100;

    for (int i = 0; i < qtdPoints; i++) {
        points.push_back(cv::Point2d(240 + r * cos(2 * M_PI / qtdPoints * i), 320 + r * sin(2 * M_PI / qtdPoints * i)));
        colors.push_back(cv::Vec3b((int) 10 + 150 / (qtdPoints-1) * i, 240, 240));
        offsets_x.push_back((i % 2 == 0) ? 30 : 0);
        names.push_back("center#" + std::to_string(i));
        connectedTo.push_back("center#" + std::to_string((i + 2) % qtdPoints));
        connectedTo.push_back("center#" + std::to_string((i - 2 + qtdPoints) % qtdPoints));

    }

    //create yml filw specifying how to connect dots

    cv::FileStorage fs("yml/simple_config.yml", cv::FileStorage::WRITE);

    fs << "qtdObjects" << qtdPoints;
    fs << "objNames" << "[";
    for (int i = 0; i < qtdPoints; i++)
        fs << names[i];
    fs << "]";

    fs << "objs" << "[";
    for (int i = 0; i < qtdPoints; i++) {
        fs << "{";
        fs << "name" << names[i];
        fs << "low_hsv" << colors[i] - cv::Vec3b(10, 10, 5);
        fs << "high_hsv" << colors[i] + cv::Vec3b(10, 10, 5);
        fs << "qtdConnections" << 2;
        fs << "connections" << "[" << connectedTo[2 * i] << connectedTo[2 * i + 1] << "]";
        fs << "}";

    }
    fs << "]";

    fs.release();


    unsigned int total_time = 33 * 20;

    unsigned int t = 0;

    double w = M_PI;

    double rr = 20;

    double x_c = 320;
    double y_c = 240;

    cv::Mat left_img(480, 640, CV_8UC3);
    cv::Mat right_img(480, 640, CV_8UC3);
    while (t < total_time) {
        left_img = cv::Mat::zeros(480, 640, CV_8UC3);
        right_img = cv::Mat::zeros(480, 640, CV_8UC3);

        r = 100 + 20 * cos(t / 33.0 * w);
        x_c = 320 + 50 * cos(t / 33.0 * 2 / w * 2);
        y_c = 240 + 80 * sin(t / 33.0 * 2 / w * 2);

        //update left img
        for (int i = 0; i < qtdPoints; i++)
            points[i] = cv::Point2d(x_c + r * cos(2 * M_PI / qtdPoints * i + w * t / 33.0),
                                    y_c + r * sin(2 * M_PI / qtdPoints * i + w * t / 33.0));
        for (int i = 0; i < qtdPoints; i++)
            cv::circle(left_img, points[i], rr, (cv::Scalar) colors[i], -1);
        cv::cvtColor(left_img, left_img, CV_HSV2BGR);

        //update  right img
        for (int i = 0; i < qtdPoints; i++)
            points[i] = cv::Point2d(offsets_x[i] + x_c + r * cos(2 * M_PI / qtdPoints * i + w * t / 33.0),
                                    y_c + r * sin(2 * M_PI / qtdPoints * i + w * t / 33.0));
        for (int i = 0; i < qtdPoints; i++)
            cv::circle(right_img, points[i], rr, (cv::Scalar) colors[i], -1);
        cv::cvtColor(right_img, right_img, CV_HSV2BGR);

        //write
        out_left.write(left_img);
        out_right.write(right_img);

        //show
        cv::imshow("left...", left_img);
        cv::imshow("right...", right_img);

        t += 1;

        char c = cv::waitKey(1);
        if (c == 'q')
            break;
    }

    out_left.release();
    out_right.release();

    cv::VideoCapture cap("avi/left.avi");
    cv::Mat f;

    if (!cap.isOpened()) {
        std::cout << "error" << std::endl;
    }

    while (cap.read(f)) {
        cv::imshow("out", f);
        char c = cv::waitKey(33);
        if (c == 'q')
            break;

    }

    cap.release();

}

