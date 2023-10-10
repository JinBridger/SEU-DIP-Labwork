#pragma once

#include "Utils.hpp"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>


class FourierTrans {
public:
    [[nodiscard]] cv::Mat fourierTrans(cv::Mat srcImage) {
        cv::cvtColor(srcImage, srcImage, cv::COLOR_BGR2GRAY);

        cv::Mat planes[] = { cv::Mat_<float>(srcImage), cv::Mat::zeros(srcImage.size(), CV_32F) };

        cv::Mat complexI;
        cv::merge(planes, 2, complexI);
        std::cout << complexI.size() << std::endl;
        std::cout << planes->size() << std::endl;

        cv::dft(complexI, complexI);

        split(complexI, planes);
        magnitude(planes[0], planes[1], planes[0]);
        cv::Mat magnitudeImage = planes[0];

        magnitudeImage += cv::Scalar::all(1);
        cv::log(magnitudeImage, magnitudeImage);

        magnitudeImage = magnitudeImage(cv::Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));

        int cx = magnitudeImage.cols / 2;
        int cy = magnitudeImage.rows / 2;

        cv::Mat q0(magnitudeImage, cv::Rect(0, 0, cx, cy));
        cv::Mat q1(magnitudeImage, cv::Rect(cx, 0, cx, cy));
        cv::Mat q2(magnitudeImage, cv::Rect(0, cy, cx, cy));
        cv::Mat q3(magnitudeImage, cv::Rect(cx, cy, cx, cy));

        cv::Mat tmp;
        q0.copyTo(tmp);
        q3.copyTo(q0);
        tmp.copyTo(q3);
        q1.copyTo(tmp);
        q2.copyTo(q1);
        tmp.copyTo(q2);

        cv::normalize(magnitudeImage, magnitudeImage, 0, 1, cv::NORM_MINMAX);
        magnitudeImage.convertTo(magnitudeImage, CV_8UC1, 255, 0);

        return magnitudeImage;
    }

    [[nodiscard]] cv::Mat customFourierTrans(const cv::Mat& srcImg) {
        // convert source image to double vector
        auto img = Utils().cvt2dVector<double>(srcImg);

        // calculate fourier transform
        double maxValue = 0;
        double minValue = 1000;

        std::vector<std::vector<double>> dst(img.size(), std::vector<double>(img[0].size()));
        for (auto u = 0; u < img.size(); ++u) {
            for (auto v = 0; v < img[0].size(); ++v) {
                double real = 0;
                double imag = 0;
                for (auto x = 0; x < img.size(); ++x) {
                    for (auto y = 0; y < img[0].size(); ++y) {
                        double theta =
                            -2.0 * _pi * (double(u * x) / double(img[0].size()) + double(v * y) / double(img.size()));
                        real += cos(theta) * img[x][y];
                        imag += sin(theta) * img[x][y];
                    }
                }
                dst[u][v] = log(sqrt(real * real + imag * imag) + 1);
                if (dst[u][v] > maxValue)
                    maxValue = dst[u][v];
                if (dst[u][v] < minValue)
                    minValue = dst[u][v];
            }
        }

        // normalization
        for (auto u = 0; u < dst.size(); ++u) {
            for (auto v = 0; v < dst[0].size(); ++v) {
                dst[u][v] = (dst[u][v] - minValue) * 255.0 / (maxValue - minValue);
            }
        }

        // cut to let the length of side be even
        if (dst.size() % 2)
            dst.pop_back();
        if (dst[0].size() % 2)
            for (auto& line : dst) {
                line.pop_back();
            }

        // swap
        for (auto i = 0; i < dst.size() / 2; ++i) {
            for (auto j = 0; j < dst[0].size() / 2; ++j) {
                std::swap(dst[i][j], dst[i + dst.size() / 2][j + dst[0].size() / 2]);
                std::swap(dst[i][j + dst[0].size() / 2], dst[i + dst.size() / 2][j]);
            }
        }

        // output
        cv::Mat ret(dst.size(), dst[0].size(), CV_64F);
        for (int i = 0; i < ret.rows; ++i) {
            for (int j = 0; j < ret.cols; ++j) {
                ret.at<double>(i, j) = dst[i][j];
            }
        }
        ret.convertTo(ret, CV_8U);
        return ret;
    }

private:
    const double _pi = 3.1415926535897932;
};