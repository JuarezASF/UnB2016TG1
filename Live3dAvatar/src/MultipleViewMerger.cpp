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
    double x_view, x_other, y1, y2, z, x, y;

    for (int pointIdx = 0; pointIdx < qtdPoints; pointIdx++) {
        cv::Vec3d vecSum(0.0, 0.0, 0.0);
        int qtdTimesSummed = 0;
        for (int viewIdx = qtdViews - 1; viewIdx >= 0 ; viewIdx--) {
            for (int otherViewIdx = 0; otherViewIdx < viewIdx; otherViewIdx++) {
                b = baseline * abs(viewIdx - otherViewIdx);
                x_view = viewsPerPoint[pointIdx][viewIdx].x;
                x_other = viewsPerPoint[pointIdx][otherViewIdx].x;

                //compute z from x1 and x2 measurements
                z = -f[viewIdx] * f[otherViewIdx] * b / (x_view * f[otherViewIdx] - x_other * f[viewIdx]);

                //fix readings for x based on z and average result
                x = (x_view * z / f[viewIdx] + x_other * z / f[otherViewIdx]) * 0.5;

                //average y
                y1 = viewsPerPoint[pointIdx][viewIdx].y;
                y2 = viewsPerPoint[pointIdx][otherViewIdx].y;
                y = (y1 + y2) * 0.5;

                vecSum += cv::Vec3d(x, y, z);
                qtdTimesSummed += 1;
            }

        }

        //average predictions for 3d points among all cameras
        out.push_back(vecSum*(1.0/qtdTimesSummed));
    }


    for(int k = 0; k < out.size(); k++){
        std::cout << "pt" << k << ":" << out[k] << "\t";

    }
    std::cout << std::endl << std::endl;

    return out;

}
