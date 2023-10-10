#pragma once

#include "opencv2/opencv.hpp"

class Histogram {
public:
    [[nodiscard]] cv::Mat getHistogram(cv::Mat oriImg);
    [[nodiscard]] cv::Mat histogramEqualization(cv::Mat oriImg);
    [[nodiscard]] cv::Mat CLAHE(cv::Mat oriImg);
private:
};