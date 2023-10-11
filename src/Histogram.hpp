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
        auto result = getHistogramValue(img);

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
        cv::Mat ext;
        cv::copyMakeBorder(srcImage, ext, 0, 8 - (srcImage.size().height % 8), 0, 8 - (srcImage.size().width % 8), cv::BORDER_REFLECT_101);

        auto img = Utils().cvt2dVector<int>(ext);

        int tileSizeX = img[0].size() / 8;
        int tileSizeY = img.size() / 8;
        const int clipLimit = 100;

        int height = img.size();
        int width = img[0].size();
        std::vector<std::vector<int>> result(height, std::vector<int>(width));

        for(int i = 0; i < 8; ++i) {
            for(int j = 0; j < 8; ++j) {
                // copy the part
                auto part = std::vector<std::vector<int>>(tileSizeY, std::vector<int>(tileSizeX));
                int partY = i * tileSizeY;
                int partX = j * tileSizeX;
                for(int curY = 0; curY < tileSizeY; ++curY) {
                    for(int curX = 0; curX < tileSizeX; ++curX) {
                        part[curY][curX] = img[partY + curY][partX + curX];
                    }
                }

                auto ret = handleCLAHEpart(part, clipLimit);
                for(int curY = 0; curY < tileSizeY; ++curY) {
                    for(int curX = 0; curX < tileSizeX; ++curX) {
                         result[partY + curY][partX + curX] = ret[curY][curX];
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
    std::vector<int> getHistogramValue(std::vector<std::vector<int>> src) {
        auto result = std::vector<int>(256, 0);

        for(auto& line: src)
            for(auto& pixel: line) {
                int idx = pixel;

                idx = std::max(idx, 0);
                idx = std::min(idx, 255);

                result[idx]++;
            }

        return result;
    }

    std::vector<std::vector<int>> handleCLAHEpart(std::vector<std::vector<int>> src, int clipLimit) {
        auto hist = getHistogramValue(src);

        int clipped = 0;
        for(auto i = 0; i < 256; ++i)
            if(hist[i] > clipLimit) {
                clipped += hist[i] - clipLimit;
                hist[i] = clipLimit;
            }

        int redistBatch = clipped / 256;
        int residual = clipped - redistBatch * 256;

        for(auto& val : hist)
            val += redistBatch;

        if(residual) {
            int residualStep = std::max(256 / residual, 1);
            for(auto i = 0; i < 256 && residual > 0; i += residualStep, residual--)
                hist[i]++;
        }

        // calculate cdf
        int imgSize = src.size() * src[0].size();

        auto cdf = std::vector<double>(256, 0);
        cdf[0] = hist[0];
        for(auto i = 1; i < cdf.size(); ++i)
            cdf[i] = cdf[i - 1] + hist[i];

        for(auto& prob: cdf)
            prob /= double(imgSize);

        // calculate equ
        auto equ = std::vector<int>(256, 0);
        for(auto i = 0; i < 256; ++i)
            equ[i] = std::min(std::max(int(255.0 * cdf[i]), 0), 255);

        for(auto& line: src)
            for(auto& pixel: line) {
                pixel = equ[pixel];
            }

        return src;
    }
};