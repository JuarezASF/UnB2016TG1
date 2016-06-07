//
// Created by jasf on 6/7/16.
//

#include "MultipleViewMerger.h"

double MultipleViewMerger::baseline = 0.0;

std::vector<cv::Point3d> MultipleViewMerger::mergeViews(std::vector<std::vector<cv::Point2d>> pointsPerView,
                                                        std::vector<double> f) {
    std::vector<cv::Point3d> out;

    if(pointsPerView.empty()){
        std::cerr << "points per view is empty!" << std::endl;
        return out;
    }

    int qtdViews = pointsPerView.size();
    int qtdPoints = pointsPerView[0].size();

    std::vector<std::vector<cv::Point2d>> viewsPerPoint;

    for(auto it : pointsPerView){
        if (it.size() != qtdPoints){
            std::cerr << "Not all points are in all cameras!" << std::endl;
            return out;
        }
    }

    for(int j = 0; j < qtdPoints; j++){
        std::vector<cv::Point2d> points;
        for(int i = 0; i < qtdViews; i++){
            points.push_back(pointsPerView[i][j]);
        }
        viewsPerPoint.push_back(points);
    }

    double b;
    double x1, x2, y1, y2, z, x, y;

    for (int j = 0; j < qtdPoints; j++) {
        cv::Vec3d vecSum(0.0, 0.0, 0.0);
        int qtdTimesSummed = 0;
        for (int i = qtdViews-1; i >= 0 ; i--) {
            for (int k = 0; k < i; k++) {
                b = baseline * abs(i - k);
                x1 = viewsPerPoint[j][i].x;
                x2 = viewsPerPoint[j][k].x;

                //compute z from x1 and x2 measurements
                z = -f[i] * f[k] * b / (x1 * f[k] - x2 * f[i]);

                //fix readings for x based on z and average result
                x = (x1  * z/f[i] + x2 * z/f[k]) * 0.5;

                //average y
                y1 = viewsPerPoint[j][i].y;
                y2 = viewsPerPoint[j][k].y;
                y = (y1 + y2) * 0.5;

                vecSum += cv::Vec3d(x, y, z);
                qtdTimesSummed += 1;
            }

        }

        //average predictions for 3d points among all cameras
        out.push_back(vecSum*(1.0/qtdTimesSummed));
    }

    return out;

}
