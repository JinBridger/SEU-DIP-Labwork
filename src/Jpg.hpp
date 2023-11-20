#pragma once

#include "opencv2/opencv.hpp"

class Jpg {
public:
    cv::Mat jpgCompress(cv::Mat srcImg) {
        const int compressRatio = 50;
        std::vector<uchar> buffer;
        std::vector<int> compressParams;
        compressParams.push_back(cv::IMWRITE_JPEG_QUALITY);
        compressParams.push_back(compressRatio);

        cv::imencode(".jpg", srcImg, buffer, compressParams);
        auto ret = cv::imdecode(buffer, -1);
        return ret;
    }

    cv::Mat jpg2KCompress(cv::Mat srcImg) {
        const int compressRatio = 500;
        std::vector<uchar> buffer;
        std::vector<int> compressParams;
        compressParams.push_back(cv::IMWRITE_JPEG2000_COMPRESSION_X1000);
        compressParams.push_back(compressRatio);

        cv::imencode(".jpg", srcImg, buffer, compressParams);
        auto ret = cv::imdecode(buffer, -1);
        return ret;
    }
};