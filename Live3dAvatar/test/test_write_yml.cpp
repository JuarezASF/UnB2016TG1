//
// Created by jasf on 4/25/16.
//

#include <opencv2/opencv.hpp>
#include <set>
#include <string>
#include <vector>

using namespace cv;
using namespace std;


int main() {

    FileStorage fs("yml/sample.yml", FileStorage::WRITE);

    map<string, set<string>> connections;
    int qtd = 6;

    for(int i = 0; i < qtd; i++){
        connections["obj" + to_string(i)] = set<string>();
        connections["obj" + to_string(i)].insert("obj" + to_string((i+2)%qtd));
        connections["obj" + to_string(i)].insert("obj" + to_string((i-2 + qtd)%qtd));
    }

    fs << "qtd" << qtd;

    fs << "objs" << "[";
    for (auto it : connections)
    for (int i = 0; i < qtd; i++) {
        fs << "{";
        fs << "name" << it.first;
        fs << "connectedTo" << "[";
        for(auto iit : it.second){
            fs << iit;
        }

        fs << "]";
        fs << "}";
    }
    fs << "]";


    fs.release();
}

