#pragma once

#include "opencv2/opencv.hpp"

class Utils {
public:
    [[nodiscard]] static std::vector<std::vector<double>> cvt2dVector(const cv::Mat& srcImg) {
        std::vector<std::vector<double>> img;
        for (int i = 0; i < srcImg.rows; ++i) {
            img.emplace_back(srcImg.cols);
            for (int j = 0; j < srcImg.cols; ++j) {
                cv::Vec3b pixelColor = srcImg.at<cv::Vec3b>(i, j);

                double B = pixelColor[0];
                double G = pixelColor[1];
                double R = pixelColor[2];

                img[i][j] = double(0.299 * R + 0.587 * G + 0.144 * B);
            }
        }
        return img;
    }
};