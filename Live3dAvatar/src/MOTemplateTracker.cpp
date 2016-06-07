//
// Created by jasf on 5/17/16.
//

#include "MOTemplateTracker.h"
#include "MultipleViewMerger.h"
#include "Demo.h"

MOTemplateTracker::MOTemplateTracker() {

}

void MOTemplateTracker::update(const std::vector<cv::Mat> &imgs) {
    centers.clear();
    for (unsigned i = 0; i < imgs.size(); i++) {
        Mat input(imgs[i]);


        if (input.empty()) {
            std::cerr << "Input idx " << i << " is empty!" << endl;
            exit(0);

        }

        centers.push_back(markers.detect(input, input));

    }


}

std::vector<cv::Point3d> MOTemplateTracker::getCenters() const {
    std::vector<cv::Point3d> out;

//    for (int i = 0; i < centers.size(); i++){
//        for(int j = 0; j < centers.size(); j++){
//            cv::Point2d p = centers[i][j];
//            out.push_back(cv::Point3d(p.x, p.y, 0.0));
//        }
//    }

    return MultipleViewMerger::mergeViews(centers, Demo::getInstance()->getFs());
}
