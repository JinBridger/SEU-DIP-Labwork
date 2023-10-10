#pragma once

#include "opencv2/opencv.hpp"

class Utils {
public:
    template<typename T>
    [[nodiscard]] std::vector<std::vector<T>> cvt2dVector(const cv::Mat& srcImg) {
        std::vector<std::vector<T>> img;
        for (int i = 0; i < srcImg.rows; ++i) {
            img.emplace_back(srcImg.cols);
            for (int j = 0; j < srcImg.cols; ++j) {
                cv::Vec3b pixelColor = srcImg.at<cv::Vec3b>(i, j);

                T B = pixelColor[0];
                T G = pixelColor[1];
                T R = pixelColor[2];

                img[i][j] = T(0.299 * R + 0.587 * G + 0.144 * B);
            }
        }
        return img;
    }
};