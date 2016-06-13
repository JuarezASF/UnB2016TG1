//
// Created by jasf on 4/25/16.
//

#ifndef STEP00_TRACKABLEOBJINFO_H
#define STEP00_TRACKABLEOBJINFO_H

#include <opencv2/opencv.hpp>
#include <set>
#include <string>

class TrackableObjInfo {

public:
    cv::Vec3b colorToPaintObject;
    std::set<std::string> connections;
    int markerId;

    TrackableObjInfo();
    TrackableObjInfo(cv::Vec3b color, int id);

    void add_connection(std::string o);

    void printConnections() const;

    inline void setColorToPaint(cv::Vec3b c) { colorToPaintObject = c; }

    inline void setMarkerId(int markerId) { TrackableObjInfo::markerId = markerId; }

    TrackableObjInfo& operator=(TrackableObjInfo A);
};

std::ostream &operator<<(std::ostream &STR, TrackableObjInfo const &v);

std::ostream &operator<<(std::ostream &STR, std::set<std::string> const &v);


#endif //STEP00_TRACKABLEOBJINFO_H
