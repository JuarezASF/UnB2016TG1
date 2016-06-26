//
// Created by jasf on 6/7/16.
//

#include <set>
#include "MultipleViewMerger.h"

double MultipleViewMerger::baseline = 0.0;

std::map<int, cv::Point3d> MultipleViewMerger::mergeViews(
        std::vector<std::map<int, cv::Point2d>> pointsPerView, std::vector<double> f, int qtdPointsExpected) {
    std::map<int, cv::Point3d> out;

    if (pointsPerView.empty()) {
        std::cerr << "points per view is empty!" << std::endl;
        return out;
    }

    int qtdViews = pointsPerView.size();
    int qtdPoints = qtdPointsExpected;

    std::map<int, std::vector<cv::Point2d>> viewsPerPoint;

    std::set<int> idsOnCameras;

    for (std::vector<std::map<int, cv::Point2d>>::iterator it = pointsPerView.begin();
         it != pointsPerView.end(); it++) {
        if (it->size() != qtdPoints) {
            std::cerr << "Not all points are in all cameras!" << std::endl;
            return out;
        }
        for (auto iit = (*it).begin(); iit != it->end(); iit++) {
            idsOnCameras.insert(iit->first);
        }
    }

    for (int markerId : idsOnCameras) {
        std::vector<cv::Point2d> points;
        for (int i = 0; i < qtdViews; i++) {
            points.push_back(pointsPerView[i][markerId]);
        }
        viewsPerPoint[markerId] = points;
    }

    double b;
    double x_view, x_other, y1, y2, z, x, y;

    for(std::set<int>::iterator it = idsOnCameras.begin(); it != idsOnCameras.end(); it++ ){}
    for(int it : idsOnCameras){}
    for(auto it : idsOnCameras){}



    for (int markerId : idsOnCameras) {
        cv::Vec3d vecSum(0.0, 0.0, 0.0);
        int qtdTimesSummed = 0;
        for (int viewIdx = qtdViews - 1; viewIdx >= 0; viewIdx--) {
            for (int otherViewIdx = 0; otherViewIdx < viewIdx; otherViewIdx++) {
                b = baseline * abs(viewIdx - otherViewIdx);
                x_view = viewsPerPoint[markerId][viewIdx].x;
                x_other = viewsPerPoint[markerId][otherViewIdx].x;

                //compute z from x1 and x2 measurements
                z = -f[viewIdx] * f[otherViewIdx] * b / (x_view * f[otherViewIdx] - x_other * f[viewIdx]);

                //fix readings for x based on z and average result
                x = (x_view * z / f[viewIdx] + x_other * z / f[otherViewIdx]) * 0.5;

                //average y
                y1 = viewsPerPoint[markerId][viewIdx].y;
                y2 = viewsPerPoint[markerId][otherViewIdx].y;
                y = (y1 + y2) * 0.5;

                vecSum += cv::Vec3d(x, y, z);
                qtdTimesSummed += 1;
            }

        }

        //average predictions for 3d points among all cameras
        out[markerId] = vecSum * (1.0 / qtdTimesSummed);
    }


    for (int k = 0; k < out.size(); k++) {
        std::cout << "pt" << k << ":" << out[k] << "\t";

    }
    std::cout << std::endl << std::endl;

    return out;

}
