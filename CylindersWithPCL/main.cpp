#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <memory>

#include <boost/thread/thread.hpp>
#include <pcl/common/common_headers.h>
#include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>
#include <Eigen/Dense>

// --------------
// -----Help-----
// --------------
void
printUsage(const char *progName) {
    std::cout << "\n\nUsage: " << progName << " [options]\n\n"
    << "Options:\n"
    << "-------------------------------------------\n"
    << "-h           this help\n"
    << "\n\n";
}

boost::shared_ptr<pcl::visualization::PCLVisualizer> shapesVis(std::vector<pcl::ModelCoefficients *> cylinders, std::vector<Eigen::Vector3f> centers) {
    // --------------------------------------------
    // -----Open 3D viewer and add point cloud-----
    // --------------------------------------------
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
    viewer->setBackgroundColor(0, 0, 0);
    viewer->addCoordinateSystem(10.0);
    viewer->initCameraParameters();

    //---------------------------------------
    //-----Add shapes at other locations-----
    //---------------------------------------
    int i = 0;
    for(auto it = cylinders.begin(); it != cylinders.end(); it++){
        std::string name = std::to_string(i++);
        viewer->addCylinder(**it, name);
    }

    i = 0;
    for (auto c : centers)
        viewer->addSphere (pcl::PointXYZ(c.x(), c.y(), c.z()), 0.2, 0.5, 0.5, 0.0, "sphere" + std::to_string(i++));
    return (viewer);
}


// --------------
// -----Main-----
// --------------
int main(int argc, char **argv) {
    // --------------------------------------
    // -----Parse Command Line Arguments-----
    // --------------------------------------
    if (pcl::console::find_argument(argc, argv, "-h") >= 0) {
        printUsage(argv[0]);
        return 0;
    }

    // --------------------------------------
    // -------Create cylinders---------------
    // --------------------------------------
    std::vector<pcl::ModelCoefficients *> cylinders;

    int N = 16;
    float radius(1);
    float r = 5;
    float dz = 3;
    float theta = 0;

    std::vector<Eigen::Vector3f> centers;
    for(int i = 0; i < N; i++)
        centers.emplace_back(r*cos(i*2*M_PI/N) - r, r*sin(i*2*M_PI/N), i*dz);

    int i = 0;
    for(auto center : centers){
        if(i == centers.size() - 1)
            break;
        pcl::ModelCoefficients *coeffs = new pcl::ModelCoefficients();
        coeffs->values.resize(7);    // We need 7 values
        coeffs->values.clear();

        coeffs->values[0] = center.x();
        coeffs->values[1] = center.y();
        coeffs->values[2] = center.z();

        auto axis_direction = centers[(i+1)%centers.size()] - center;

        coeffs->values[3] = axis_direction.x();
        coeffs->values[4] = axis_direction.y();
        coeffs->values[5] = axis_direction.z();
        coeffs->values[6] = radius;

        cylinders.push_back(coeffs);
        i++;
    }


    // ------------------------------------
    // -----Create example point cloud-----
    // ------------------------------------

    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
    viewer = shapesVis(cylinders, centers);

    //--------------------
    // -----Main loop-----
    //--------------------
    while (!viewer->wasStopped()) {
        viewer->spinOnce(100);
        boost::this_thread::sleep(boost::posix_time::microseconds(100000));
    }
}
