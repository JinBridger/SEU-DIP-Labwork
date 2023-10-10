#pragma once

#include "opencv2/opencv.hpp"

class Utils {
public:
    template<typename T>
    [[nodiscard]] std::vector<std::vector<T>> cvt2dVector(const cv::Mat& srcImg) {
        cv::Mat grayImg;
        cv::cvtColor(srcImg, grayImg, cv::COLOR_BGR2GRAY);

        std::vector<std::vector<T>> img;
        for (int i = 0; i < grayImg.rows; ++i) {
            img.emplace_back(grayImg.cols);
            for (int j = 0; j < grayImg.cols; ++j) {
                uchar pixelColor = grayImg.at<uchar>(i, j);

                img[i][j] = T(pixelColor);
            }
        }
        return img;
    }
};