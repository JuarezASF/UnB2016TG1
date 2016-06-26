#include <iostream>

#include "Demo.h"

#include "CommandLineParser.h"


int main(int argc, char **argv) {
    std::string configFile = "";

    if (const char *env_config_file = std::getenv("CONFIG_FILENAME")) {
        configFile = std::string(env_config_file);
    }

    if (configFile.empty()) {
        configFile = "config.yml";
    }

    cout << "configuration being read from: " << configFile << endl;


    Demo::init(configFile);
    Demo *d = Demo::getInstance();

    d->run();

    return 0;
}
