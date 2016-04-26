//
// Created by jasf on 4/25/16.
//
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {

    FileStorage fs("yml/sample.yml", FileStorage::READ);

    int qtd = (int) fs["qtd"];

    FileNode objs = fs["objs"];

    for(auto it : objs){
        cout << "name:" << (string) it["name"] << endl;
        FileNode o = fs["connectTo"];
        for(auto oo : o){
            cout << "\t" << (string) oo << endl;

        }
    }

    fs.release();
}

