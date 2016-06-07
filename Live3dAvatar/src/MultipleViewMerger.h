//
// Created by jasf on 6/7/16.
//

#ifndef STEP00_MULTIPLEVIEWMERGER_H
#define STEP00_MULTIPLEVIEWMERGER_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <iostream>


class MultipleViewMerger {
private:

    static double baseline;

public:

    /**
     * input: pointsPerVies[i][j] is point j detected at camera i
     *        f: f[i] is focus parameter on camera i
     *
     * output: out[j] is point 3d j
     */
    static std::vector<cv::Point3d> mergeViews(std::vector<std::vector<cv::Point2d>> pointsPerView,
                                        std::vector<double> f);

    /**
     * distance from camera i to camera j is assumed to be:
     *      baseline * abs(j - i)
     */
    inline static void setBaseline(double d) { baseline = d; }

};


#endif //STEP00_MULTIPLEVIEWMERGER_H
