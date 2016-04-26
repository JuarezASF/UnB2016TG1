//
// Created by jasf on 4/25/16.
//

#include "TrackableObjInfo.h"

TrackableObjInfo::TrackableObjInfo() {

}

void TrackableObjInfo::set_low(cv::Vec3b low) {
    low_hsv = low;

}

void TrackableObjInfo::set_high(cv::Vec3b low) {
    high_hsv = low;

}

void TrackableObjInfo::add_connection(std::string o) {
    connections.insert(o);
}
