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

    [[nodiscard]] cv::Mat histogramEqualization(cv::Mat srcImage) {
        cv::Mat ret;

        cv::cvtColor(srcImage, srcImage, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(srcImage, ret);

        return ret;
    }

    [[nodiscard]] cv::Mat customHistogramEqualization(cv::Mat srcImage) {
        auto img = Utils().cvt2dVector<int>(srcImage);

        auto result = std::vector<int>(256, 0);

        for(auto& line: img)
            for(auto& pixel: line) {
                int idx = pixel;

                idx = std::max(idx, 0);
                idx = std::min(idx, 255);

                result[idx]++;
            }

        // calculate cdf
        int imgSize = img.size() * img[0].size();

        auto cdf = std::vector<double>(256, 0);
        cdf[0] = result[0];
        for(auto i = 1; i < cdf.size(); ++i)
            cdf[i] = cdf[i - 1] + result[i];

        for(auto& prob: cdf)
            prob /= double(imgSize);

        // calculate equ
        auto equ = std::vector<int>(256, 0);
        for(auto i = 0; i < 256; ++i)
            equ[i] = std::min(std::max(int(255.0 * cdf[i]), 0), 255);

        for(auto& line: img)
            for(auto& pixel: line) {
                pixel = equ[pixel];
            }

        cv::Mat ret(srcImage.rows, srcImage.cols, CV_8UC1);
        for(auto i = 0; i < srcImage.rows; ++i) {
            for(auto j = 0; j < srcImage.cols; ++j) {
                ret.at<uchar>(i, j) = uchar(img[i][j]);
            }
        }

        return ret;
    }

    [[nodiscard]] cv::Mat CLAHE(cv::Mat srcImage) {
        cv::Mat gray;
        cv::cvtColor(srcImage, gray, cv::COLOR_BGR2GRAY);
        cv::Mat ret;

        cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
        clahe->setClipLimit(4);
        clahe->apply(gray, ret);

        return ret;
    }

    [[nodiscard]] cv::Mat customCLAHE(cv::Mat srcImage) {
        auto img = Utils().cvt2dVector<int>(srcImage);

        int tileSize = 24;
        const int clipLimit = 4;

        int height = img.size();
        int width = img[0].size();
        std::vector<std::vector<int>> result(height, std::vector<int>(width));

        for (int i = 0; i < height; i += tileSize) {
            for (int j = 0; j < width; j += tileSize) {

                std::vector<int> histogram(256, 0);
                int actualTileHeight = std::min(tileSize, height - i);
                int actualTileWidth = std::min(tileSize, width - j);
                for (int di = 0; di < actualTileHeight; ++di) {
                    for (int dj = 0; dj < actualTileWidth; ++dj) {
                        int pixel = img[i + di][j + dj];
                        histogram[pixel]++;
                    }
                }

                int total = 0;
                for (int intensity = 0; intensity < 256; ++intensity) {
                    if (histogram[intensity] > clipLimit) {
                        total += histogram[intensity] - clipLimit;
                        histogram[intensity] = clipLimit;
                    }
                }

                int increment = total / 256;
                total -= increment * 256;
                for (int intensity = 0; intensity < 256; ++intensity) {
                    histogram[intensity] += increment;
                }
                for (int intensity = 0; intensity < total; ++intensity) {
                    histogram[intensity]++;
                }

                std::vector<int> cdf(256, 0);
                cdf[0] = histogram[0];
                for (int intensity = 1; intensity < 256; ++intensity) {
                    cdf[intensity] = cdf[intensity - 1] + histogram[intensity];
                }

                for (int di = 0; di < actualTileHeight; ++di) {
                    for (int dj = 0; dj < actualTileWidth; ++dj) {
                        int pixel = img[i + di][j + dj];
                        result[i + di][j + dj] = cdf[pixel] * 255 / cdf[255];
                    }
                }
            }
        }

        cv::Mat ret(srcImage.rows, srcImage.cols, CV_8UC1);
        for(auto i = 0; i < srcImage.rows; ++i) {
            for(auto j = 0; j < srcImage.cols; ++j) {
                ret.at<uchar>(i, j) = uchar(result[i][j]);
            }
        }

        return ret;
    }
private:
};