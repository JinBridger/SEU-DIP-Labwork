#pragma once

#include "opencv2/opencv.hpp"
#include "Utils.hpp"

class Morphology {
public:
    cv::Mat erosion(cv::Mat srcImg) {
        auto img = Utils().cvt2dVector<int>(srcImg);
        auto ret = img;
        for (auto &line: img)
            for (auto &pixel: line) {
                if (pixel > 100) pixel = 255;
                else
                    pixel = 0;
            }

        std::vector<std::vector<int>> core = {
                {255, 255, 255},
                {255, 255, 255},
                {255, 255, 255},
        };
        int padding = core.size() / 2;

        for (auto i = padding; i < img.size() - padding; ++i) {
            for (auto j = padding; j < img[0].size() - padding; ++j) {
                bool reserve = true;

                for (auto dx = -padding; dx <= padding; ++dx)
                    for (auto dy = -padding; dy <= padding; ++dy)
                        if (img[i + dx][j + dy] != core[padding + dx][padding + dy])
                            reserve = false;

                if (reserve) ret[i][j] = 255;
                else ret[i][j] = 0;
            }
        }

        return Utils().cvtCvMat(ret);
    }

    cv::Mat dilation(cv::Mat srcImg) {
        auto img = Utils().cvt2dVector<int>(srcImg);
        auto ret = img;
        for (auto &line: img)
            for (auto &pixel: line) {
                if (pixel > 100) pixel = 255;
                else
                    pixel = 0;
            }

        for (auto &line: ret)
            for (auto &pixel: line)
                pixel = 0;

        std::vector<std::vector<int>> core = {
                {255, 255, 255},
                {255, 255, 255},
                {255, 255, 255},
        };
        int padding = core.size() / 2;

        for (auto i = padding; i < img.size() - padding; ++i) {
            for (auto j = padding; j < img[0].size() - padding; ++j)
                if(img[i][j] == 255) {
                    for (auto dx = -padding; dx <= padding; ++dx)
                        for (auto dy = -padding; dy <= padding; ++dy)
                            ret[i + dx][j + dy] = core[padding + dx][padding + dy];
            }
        }

        return Utils().cvtCvMat(ret);
    }
private:
};