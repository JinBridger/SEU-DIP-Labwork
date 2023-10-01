#pragma once

#include <opencv2/opencv.hpp>
#include <string>


class Core {
public:
    Core() = default;

    [[nodiscard]] std::string getImgPath() const {
        return _imgPath;
    }

    [[nodiscard]] cv::Mat getOriImgMat() const {
        return _oriImgMat;
    }

    [[nodiscard]] cv::Mat getDstImgMat() const {
        return _dstImgMat;
    }

    void setDstImgMat(cv::Mat img) {
        _dstImgMat = img;
    }

    void loadImg(std::string img_path) {
        _imgPath   = img_path;
        _oriImgMat = cv::imread(_imgPath);
        _dstImgMat = cv::Mat();
    }

private:
    std::string _imgPath;
    cv::Mat     _oriImgMat;
    cv::Mat     _dstImgMat;
};