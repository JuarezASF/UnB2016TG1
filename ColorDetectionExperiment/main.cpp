#include <iostream>
#include <opencv2/opencv.hpp>
#include "HSVRangeTrackableObject.h"
#include "Camera.h"
#include "CommandLineParser.h"
#include "Logger.h"
#include "Demo.h"


int main( int argc, char** argv )
{
    util::CommandLineParser parser;
    parser.addStrArg("-f", true, "");
    parser.parseCommandLine(argc, argv);

    Demo d(parser.getStrVal("-f"));

    d.run();

    return 0;
}
