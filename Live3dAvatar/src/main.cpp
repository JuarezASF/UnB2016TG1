#include <iostream>

#include "Demo.h"

#include "CommandLineParser.h"


int main(int argc, char **argv) {
    util::CommandLineParser parser;
    parser.addStrArg("-f", true, "");
    parser.addStrArg("--yml", false, "yml/simple_config.yml");
    parser.addBoolArg("--view-3d", false, false);
    parser.addBoolArg("--true-tracker", false, false);

    parser.parseCommandLine(argc, argv);

    Demo::init(parser.getStrVal("-f"), parser.getStrVal("--yml"));
    Demo *d = Demo::getInstance();

    d->run();

    return 0;
}
