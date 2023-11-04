#pragma once

#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <random>
#include <chrono>

class Noise {
public:
    [[nodiscard]] cv::Mat gaussianNoise(cv::Mat srcImg) {
        auto img = Utils().cvt2dVector<int>(srcImg);

        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);
        std::normal_distribution<double> distribution(0, 20);

        for(auto& line: img) {
            for(auto& pixel: line) {
                pixel = pixel + int(distribution(generator));
                if(pixel > 255) pixel = 255;
                if(pixel < 0) pixel = 0;
            }
        }

        return Utils().cvtCvMat(img);
    }

    [[nodiscard]] cv::Mat saltPepperNoise(cv::Mat srcImg) {
        srand(time(0));

        auto img = Utils().cvt2dVector<int>(srcImg);
        for(auto& line: img) {
            for(auto& pixel: line) {
                int randVal = rand() % 256;
                if(randVal < 30) pixel = 0;
                if(randVal > 226) pixel = 255;
            }
        }

        return Utils().cvtCvMat(img);
    }

    [[nodiscard]] cv::Mat medianFilter(cv::Mat srcImg, int window = 5) {
        auto padding = (window - 1) / 2;
        cv::Mat ext;
        cv::copyMakeBorder(srcImg, ext, padding, padding, padding, padding, cv::BORDER_REFLECT_101);
        auto thres = window * window / 2 + 1;
        auto img = Utils().cvt2dVector<int>(ext);
        auto res = Utils().cvt2dVector<int>(srcImg);
        auto hist = std::vector<int>(256, 0);

        auto func = [](int i, int j, std::vector<std::vector<int>>& vec) -> int {
            if(i >= vec.size() || j >= vec[0].size() || i < 0 || j < 0) {
                return 0;
            } else {
                return vec[i][j];
            }
        };

        auto getMedian = [](std::vector<int>& hist, int thres) {
            int sum = 0;
            for(auto i = 0; i < hist.size(); ++i) {
                sum += hist[i];
                if(sum >= thres)
                    return i;
            }
            return 255;
        };

        for(auto i = padding; i < img.size() - padding; ++i) {
            for(auto j = padding; j < img[0].size() - padding; ++j) {
                if(j == padding) {
                    hist = std::vector<int>(256, 0);
                    for(auto offsetY = -padding; offsetY <= padding; offsetY++) {
                        for(auto offsetX = -padding; offsetX <= padding; offsetX++) {
                            hist[func(i + offsetY, j + offsetX, img)]++;
                        }
                    }
                } else {
                    auto lt = j - padding - 1;
                    auto rt = j + padding;
                    for(auto y = i - padding; y <= i + padding; ++y) {
                        hist[func(y, lt, img)]--;
                        hist[func(y, rt, img)]++;
                    }
                }
                res[i - padding][j - padding] = getMedian(hist, thres);
            }
        }

        return Utils().cvtCvMat(res);
    }

    [[nodiscard]] cv::Mat adaptiveMedianFilter(cv::Mat srcImg, int minWindow = 3, int maxWindow = 5) {
        auto padding = (maxWindow - 1) / 2;
        cv::Mat ext;
        cv::copyMakeBorder(srcImg, ext, padding, padding, padding, padding, cv::BORDER_REFLECT_101);
        auto img = Utils().cvt2dVector<int>(ext);
        auto res = Utils().cvt2dVector<int>(srcImg);

        for(auto i = padding; i < img.size() - padding; ++i) {
            for(auto j = padding; j < img[0].size() - padding; ++j) {
                res[i - padding][j - padding] = adaptiveMedianFilterWorker(img, i, j, minWindow, maxWindow);
            }
        }

        return Utils().cvtCvMat(res);
    }

    [[nodiscard]] cv::Mat averagingFilter(cv::Mat srcImg, int window = 3) {
        auto padding = (window - 1) / 2;
        cv::Mat ext;
        cv::copyMakeBorder(srcImg, ext, padding, padding, padding, padding, cv::BORDER_REFLECT_101);
        auto thres = window * window / 2 + 1;
        auto img = Utils().cvt2dVector<int>(ext);
        auto res = Utils().cvt2dVector<int>(srcImg);
        int tmpSum = 0;

        auto func = [](int i, int j, std::vector<std::vector<int>>& vec) -> int {
            if(i >= vec.size() || j >= vec[0].size() || i < 0 || j < 0) {
                return 0;
            } else {
                return vec[i][j];
            }
        };

        for(auto i = padding; i < img.size() - padding; ++i) {
            for(auto j = padding; j < img[0].size() - padding; ++j) {
                if(j == padding) {
                    tmpSum = 0;
                    for(auto offsetY = -padding; offsetY <= padding; offsetY++) {
                        for(auto offsetX = -padding; offsetX <= padding; offsetX++) {
                            tmpSum += func(i + offsetY, j + offsetX, img);
                        }
                    }
                } else {
                    auto lt = j - padding - 1;
                    auto rt = j + padding;
                    for(auto y = i - padding; y <= i + padding; ++y) {
                        tmpSum -= func(y, lt, img);
                        tmpSum += func(y, rt, img);
                    }
                }
                res[i - padding][j - padding] = tmpSum / 9;
            }
        }

        return Utils().cvtCvMat(res);
    }

    [[nodiscard]] cv::Mat nonLocalMeansFilter(cv::Mat srcImg, double h = 15.0, int halfKernelSize = 3, int halfSearchSize = 15) {
        auto padding = halfKernelSize + halfSearchSize;
        cv::Mat ext;
        cv::copyMakeBorder(srcImg, ext, padding, padding, padding, padding, cv::BORDER_REFLECT_101);
        auto img = Utils().cvt2dVector<int>(ext);
        auto res = Utils().cvt2dVector<int>(srcImg);
        auto h2 = h * h;

        auto cast = [](int a) -> int {
            if(a < 0) return 0;
            if(a > 255) return 255;
            return a;
        };

        for(auto i = padding; i < img.size() - padding; ++i) {
            for(auto j = padding; j < img[0].size() - padding; ++j) {
                double w = 0;
                double p = 0;
                double sum_w = 0;

                for(auto searchI = -halfSearchSize; searchI <= halfSearchSize; ++searchI) {
                    for(auto searchJ = -halfSearchSize; searchJ <= halfSearchSize; ++searchJ) {

                        double d2 = 0;
                        for(auto kernelI = -halfKernelSize; kernelI <= halfKernelSize; ++kernelI) {
                            for(auto kernelJ = -halfKernelSize; kernelJ <= halfKernelSize; ++kernelJ) {
                                auto diff = img[i + kernelI][j + kernelJ] - img[i + searchI + kernelI][j + searchJ + kernelJ];
                                d2 += diff * diff;
                            }
                        }
                        d2 /= ((halfKernelSize * 2 + 1) * (halfKernelSize * 2 + 1));
                        w = exp(-d2 / h2);
                        p += w * img[i + searchI][j + searchJ];
                        sum_w += w;
                    }
                }

                res[i - padding][j - padding] = cast(int(p / sum_w));
            }
        }

        return Utils().cvtCvMat(res);
    }
private:
    int adaptiveMedianFilterWorker(std::vector<std::vector<int>>& img, int i, int j, int window, int maxWindow) {
        std::vector<int> pixels;
        auto padding = (window - 1) / 2;

        for(auto y = i - padding; y <= i + padding; ++y) {
            for(auto x = j - padding; x <= j + padding; ++x) {
                pixels.push_back(img[y][x]);
            }
        }

        std::sort(pixels.begin(), pixels.end());
        int minVal = pixels[0];
        int maxVal = pixels[pixels.size() - 1];
        int midVal = pixels[(pixels.size() - 1) / 2];

        if(minVal < midVal && midVal < maxVal) {
            if(minVal < img[i][j] && img[i][j] < maxVal) {
                return img[i][j];
            }
            return midVal;
        }

        if(window == maxWindow) {
            return img[i][j];
        }

        return adaptiveMedianFilterWorker(img, i, j, window + 1, maxWindow);
    }
};