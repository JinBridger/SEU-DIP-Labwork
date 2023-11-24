#pragma once

#include "opencv2/opencv.hpp"
#include "Jpg.hpp"

class Utils {
public:
    template<typename T>
    [[nodiscard]] std::vector<std::vector<T>> cvt2dVector(const cv::Mat& srcImg) {
        cv::Mat grayImg = srcImg;
        if(srcImg.type() == CV_8UC3)
            cv::cvtColor(srcImg, grayImg, cv::COLOR_BGR2GRAY);

        std::vector<std::vector<T>> img;
        for (int i = 0; i < grayImg.rows; ++i) {
            img.emplace_back(grayImg.cols);
            for (int j = 0; j < grayImg.cols; ++j) {
                uchar pixelColor = grayImg.at<uchar>(i, j);

                img[i][j] = T(pixelColor);
            }
        }
        return img;
    }

    template<typename T>
    [[nodiscard]] cv::Mat cvtCvMat(const std::vector<std::vector<T>>& vec) {
        cv::Mat ret(vec.size(), vec[0].size(), CV_8UC1);
        for(auto i = 0; i < vec.size(); ++i) {
            for(auto j = 0; j < vec[0].size(); ++j) {
                ret.at<uchar>(i, j) = uchar(vec[i][j]);
            }
        }

        return ret;
    }

    double calcMSE(cv::Mat oriImg, cv::Mat aftImg) {
        cv::Mat grayOriImg, grayAftImg, diff;
        if(oriImg.type() == CV_8UC3)
            cv::cvtColor(oriImg, grayOriImg, cv::COLOR_BGR2GRAY);
        else
            grayOriImg = oriImg;
        grayOriImg.convertTo(grayOriImg, CV_32F);

        if(aftImg.type() == CV_8UC3)
            cv::cvtColor(aftImg, grayAftImg, cv::COLOR_BGR2GRAY);
        else
            grayAftImg = aftImg;
        grayAftImg.convertTo(grayAftImg, CV_32F);

        diff.convertTo(diff, CV_32F);
        cv::absdiff(grayOriImg, grayAftImg, diff);
        diff = diff.mul(diff);

        auto mse = cv::sum(diff)[0];
        auto totPixel = grayAftImg.cols * grayAftImg.rows;

        return mse / totPixel;
    }

    double calcPSNR(cv::Mat oriImg, cv::Mat aftImg) {
        auto mse = calcMSE(oriImg, aftImg);
        double psnr = 10.0 * log10( 255.0*255.0 / mse );
        return psnr;
    }

    double testFun(cv::Mat oriImg) {
        std::vector<double> jpgMSE;
        std::vector<double> jpgPSNR;
        std::vector<double> jp2MSE;
        std::vector<double> jp2PSNR;

        for(auto i = 0; i <= 100; ++i) {
            auto jpgMat = Jpg().jpgCompress(oriImg, i);
            auto jp2Mat = Jpg().jpg2KCompress(oriImg, i*10);
            jpgMSE.push_back(Utils().calcMSE(oriImg, jpgMat));
            jpgPSNR.push_back(Utils().calcPSNR(oriImg, jpgMat));
            jp2MSE.push_back(Utils().calcMSE(oriImg, jp2Mat));
            jp2PSNR.push_back(Utils().calcPSNR(oriImg, jp2Mat));
        }

        std::cout << "Compress Ratio,JPG MSE,JPG PSNR,J2K MSE,J2K PSNR" << std::endl;
        for(auto i = 0; i <= 100; ++i) {
            std::cout << i << ",";
            std::cout << std::to_string(jpgMSE[i]) << ",";
            std::cout << std::to_string(jpgPSNR[i]) << ",";
            std::cout << std::to_string(jp2MSE[i]) << ",";
            std::cout << std::to_string(jp2PSNR[i]) << std::endl;
        }
    }
};