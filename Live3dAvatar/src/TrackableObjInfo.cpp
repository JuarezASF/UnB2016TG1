//
// Created by jasf on 4/25/16.
//

#include "TrackableObjInfo.h"

TrackableObjInfo::TrackableObjInfo() {

}

TrackableObjInfo::TrackableObjInfo(cv::Vec3b color, int id) : colorToPaintObject(color), markerId(id) {
}


void TrackableObjInfo::add_connection(std::string o) {
    connections.insert(o);
}

std::ostream &operator<<(std::ostream &STR, TrackableObjInfo const &v) {
    STR << "[markerId:" << v.markerId << "] connections" << v.connections;
    return STR;
}

std::ostream &operator<<(std::ostream &STR, std::set<std::string> const &v) {
    for (auto it : v)
        STR << it << ' ';
    return STR;
}

void TrackableObjInfo::printConnections() const {

    for (const auto &it : connections) {
        std::cout << "\t\t" << it << std::endl;

    }

}

TrackableObjInfo &TrackableObjInfo::operator=(TrackableObjInfo A) {
    this->colorToPaintObject = A.colorToPaintObject;

    this->connections.clear();
    for (auto it : A.connections)
        this->connections.insert(it);

    this->markerId = A.markerId;
}
