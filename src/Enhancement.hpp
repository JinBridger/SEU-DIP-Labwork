#pragma once

#include "Utils.hpp"
#include "opencv2/opencv.hpp"

class Enhancement {
public:
    cv::Mat laplaceSharpening(cv::Mat srcImg) {
        const int padding = 1;
        cv::Mat ext;
        cv::copyMakeBorder(srcImg, ext, padding, padding, padding, padding, cv::BORDER_REFLECT_101);
        auto img = Utils().cvt2dVector<double>(ext);
        auto ret = Utils().cvt2dVector<int>(srcImg);

        double laplaceMat[3][3] = {
                {+0, +1, +0},
                {+1, -4, +1},
                {+0, +1, +0}};

        for(auto i = 1; i < img.size() - 1; ++i) {
            for(auto j = 1; j < img[0].size() - 1; ++j) {
                double val = 0;
                for(auto di = -1; di <= 1; ++di) {
                    for(auto dj = -1; dj <= 1; ++dj) {
                        val += laplaceMat[di + 1][dj + 1] * img[i + di][j + dj];
                    }
                }
                ret[i - 1][j - 1] = std::min(std::max(int(img[i][j] - 1 * val), 0), 255);
            }
        }

        return Utils().cvtCvMat(ret);
    }

    cv::Mat unsharpMasking(cv::Mat srcImg) {
        auto blurImg = Utils().cvt2dVector<int>(gaussianFilter(srcImg));
        auto img = Utils().cvt2dVector<int>(srcImg);

        auto delta = img;
        for(auto i = 0; i < img.size(); ++i) {
            for(auto j = 0; j < img[0].size(); ++j) {
                delta[i][j] = img[i][j] + 5 * (img[i][j] - blurImg[i][j]);
                delta[i][j] = std::min(std::max(delta[i][j], 0), 255);
            }
        }

        return Utils().cvtCvMat(delta);
    }

    cv::Mat gaussianFilter(cv::Mat srcImg) {
        const int padding = 1;
        cv::Mat ext;
        cv::copyMakeBorder(srcImg, ext, padding, padding, padding, padding, cv::BORDER_REFLECT_101);
        auto img = Utils().cvt2dVector<double>(ext);
        auto ret = Utils().cvt2dVector<int>(srcImg);

        double gaussianMat[3][3] = {
                {0.094741, 0.118318, 0.094741},
                {0.118318, 0.147761, 0.118318},
                {0.094741, 0.118318, 0.094741}};

        for(auto i = 1; i < img.size() - 1; ++i) {
            for(auto j = 1; j < img[0].size() - 1; ++j) {
                double val = 0;
                for(auto di = -1; di <= 1; ++di) {
                    for(auto dj = -1; dj <= 1; ++dj) {
                        val += gaussianMat[di + 1][dj + 1] * img[i + di][j + dj];
                    }
                }
                ret[i - 1][j - 1] = std::min(std::max(int(val), 0), 255);
            }
        }

        return Utils().cvtCvMat(ret);
    }
};