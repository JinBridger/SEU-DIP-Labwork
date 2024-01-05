#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "opencv2/opencv.hpp"

class Raw {
public:
    cv::Mat readFromRaw(std::string file_path) {
        std::ifstream rawFile(file_path, std::ios::in | std::ios::binary);
        unsigned int width = 0, height = 0;

        unsigned char byte;
        rawFile.read((char*)(&width), sizeof(width));
        rawFile.read((char*)(&height), sizeof(height));

        auto img = std::vector<std::vector<int>>(height);
        for(int i = 0; i < height; ++i) {
            for(int j = 0; j < width; ++j) {
                unsigned short tmp;
                rawFile.read((char*)(&tmp), sizeof(tmp));
                img[i].push_back(tmp / 16);
            }
        }

        auto cvimg = Utils().cvtCvMat(img);
        return cvimg;
    }
};