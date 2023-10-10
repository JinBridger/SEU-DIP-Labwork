#pragma once

#include "opencv2/opencv.hpp"

class Histogram {
public:
    [[nodiscard]] cv::Mat getHistogram(cv::Mat srcImage) {
        // using opencv to draw histogram
        cv::Mat histogram;
        cv::cvtColor(srcImage, srcImage, cv::COLOR_BGR2GRAY);

        int histsize = 256;
        float ranges[] = { 0,256 };
        const float* histRanges = { ranges };
        calcHist(&srcImage, 1, 0, cv::Mat(), histogram, 1, &histsize, &histRanges, true, false);

        int hist_h = 256;
        int hist_w = 256;
        int bin_w = hist_w / histsize;
        cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(255, 255, 255));

        normalize(histogram, histogram, 0, hist_h - 1, cv::NORM_MINMAX, -1, cv::Mat());

        for(auto i = 0; i < histsize; ++i)
            for(auto j = hist_h - 1 - cvRound(histogram.at<float>(i)); j < hist_h; ++j)
                histImage.at<cv::Vec3b>(j, i) = cv::Vec3b(0, 0, 0);

        return histImage;
    }

    [[nodiscard]] cv::Mat customGetHistogram(cv::Mat srcImage) {
        // custom draw histogram
        auto img = Utils().cvt2dVector<int>(srcImage);
        auto result = std::vector<int>(256, 0);

        for(auto& line: img)
            for(auto& pixel: line) {
                int idx = pixel;

                idx = std::max(idx, 0);
                idx = std::min(idx, 255);

                result[idx]++;
            }

        // normalization
        int maxVal = 0;
        int minVal = 0x7fffffff;
        for(auto& val: result) {
            maxVal = std::max(maxVal, val);
            minVal = std::min(minVal, val);
        }

        for(auto& val: result) {
            val = val - minVal;
            val = int(val * 255.0 / (maxVal - minVal));
        }

        int hist_h = 256;
        int hist_w = 256;
        cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(255, 255, 255));

        for(auto i = 0; i < result.size(); ++i)
            for(auto j = hist_h - 1 - result[i]; j < hist_h; ++j)
                histImage.at<cv::Vec3b>(j, i) = cv::Vec3b(0, 0, 0);

        return histImage;
    }

    [[nodiscard]] cv::Mat histogramEqualization(cv::Mat oriImg);
    [[nodiscard]] cv::Mat CLAHE(cv::Mat oriImg);
private:
};