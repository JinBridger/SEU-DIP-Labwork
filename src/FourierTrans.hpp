#pragma once

#include <opencv2/opencv.hpp>

class FourierTrans {
public:
    [[nodiscard]] cv::Mat fourierTrans(cv::Mat srcImage) {
        cv::cvtColor(srcImage, srcImage, cv::COLOR_BGR2GRAY);

//        int m = cv::getOptimalDFTSize(srcImage.rows);
//        int n = cv::getOptimalDFTSize(srcImage.cols);
//
//        cv::Mat padded;
//        cv::copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, cv::BORDER_CONSTANT,
//                       cv::Scalar::all(0));
//        std::cout << padded.size() << padded.channels() << std::endl;

//        cv::Mat planes[] = {cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F)};
        cv::Mat planes[] = {cv::Mat_<float>(srcImage), cv::Mat::zeros(srcImage.size(), CV_32F)};

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

        return magnitudeImage;
    }

private:
};