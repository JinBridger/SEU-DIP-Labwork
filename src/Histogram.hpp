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

        normalize(histogram, histogram, 0, hist_h, cv::NORM_MINMAX, -1, cv::Mat());
        for (int i = 1; i < histsize; i++) {
            line(histImage, cv::Point((i - 1) * bin_w, hist_h - cvRound(histogram.at<float>(i - 1))),
                 cv::Point((i)*bin_w, hist_h - cvRound(histogram.at<float>(i))), cv::Scalar(0, 0, 0), 2, 8, 0);
        }

        return histImage;
    }

    [[nodiscard]] cv::Mat histogramEqualization(cv::Mat oriImg);
    [[nodiscard]] cv::Mat CLAHE(cv::Mat oriImg);
private:
};