#include <iostream>

#include "Demo.h"

#include "CommandLineParser.h"


int main(int argc, char **argv) {
    util::CommandLineParser parser;
    parser.addStrArg("-f", true, "");
    parser.parseCommandLine(argc, argv);

    Demo d(parser.getStrVal("-f"));

    d.run();

    return 0;
}
