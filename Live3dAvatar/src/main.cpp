#include <iostream>

#include "Demo.h"

#include "CommandLineParser.h"


int main(int argc, char **argv) {
    util::CommandLineParser parser;
    parser.addStrArg("-f", true, "");
    parser.addBoolArg("--view-3d", false, false);
    parser.addBoolArg("--true-tracker", false, false);

    parser.parseCommandLine(argc, argv);

    Demo::init(parser.getStrVal("-f"), parser.getBoolVal("--view-3d"), parser.getBoolVal("--true-tracker"));
    Demo *d = Demo::getInstance();

    d->run();

    return 0;
}
