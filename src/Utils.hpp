#pragma once

#include "opencv2/opencv.hpp"

class Utils {
public:
    template<typename T>
    [[nodiscard]] std::vector<std::vector<T>> cvt2dVector(const cv::Mat& srcImg) {
        cv::Mat grayImg = srcImg;
        if(srcImg.type() == CV_8UC3)
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

    template<typename T>
    [[nodiscard]] cv::Mat cvtCvMat(const std::vector<std::vector<T>>& vec) {
        cv::Mat ret(vec.size(), vec[0].size(), CV_8UC1);
        for(auto i = 0; i < vec.size(); ++i) {
            for(auto j = 0; j < vec[0].size(); ++j) {
                ret.at<uchar>(i, j) = uchar(vec[i][j]);
            }
        }

        return ret;
    }
};