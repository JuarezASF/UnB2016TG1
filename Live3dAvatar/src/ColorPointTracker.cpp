//
// Created by jasf on 4/7/16.
//

#include "ColorPointTracker.h"
#include "Demo.h"

ColorPointTracker::ColorPointTracker() {

}


void ColorPointTracker::update(std::vector<cv::Mat> &imgs) {

    //cvt all to hsv where tracking is realized
    for (int k = 0; k < imgs.size(); k++) {
        cv::cvtColor(imgs[k], imgs[k], CV_BGR2HSV);
    }

    for (int k = 0; k < targets.size(); k++) {
        targets[k]->update(imgs);
    }

    for (int i = 0; i < imgs.size(); i++) {
        for (int j = 0; j < targets.size(); j++) {
            auto point3d = targets[j]->getEstimatedCenter();

            cv::circle(imgs[i],cv::Point(point3d.x, point3d.y) , 10, targets[j]->getHSVHigh(), -1 );
        }
    }

    //cvt it back
    for (int k = 0; k < imgs.size(); k++) {
        cv::cvtColor(imgs[k], imgs[k], CV_HSV2BGR);
    }


}


void ColorPointTracker::addHSVRangeToTrack(const cv::Scalar &low_hsv, const cv::Scalar &high_hsv,
                                           std::string obj_name) {

    int idx = (int) targets.size();
    idx_name_map[idx] = obj_name;
    name_idx_map[obj_name] = idx;
    targets.push_back(new RangeMultipleViewTracker(low_hsv, high_hsv));

}


ColorPointTracker::~ColorPointTracker() {
    targets.clear();

}

std::vector<cv::Point3d> ColorPointTracker::getCenters() const {
    std::vector<cv::Point3d> out;

    for (int i = 0; i < targets.size(); i++) {
        out.push_back(targets[i]->getEstimatedCenter());
    }

    return out;
}
