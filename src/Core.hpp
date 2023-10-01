#pragma once

#include <string>
#include <opencv2/opencv.hpp>

class Core {
public:
    Core() = default;

    [[nodiscard]] std::string getImgPath() const {
        return _imgPath;
    }

    [[nodiscard]] cv::Mat getImgMat() const {
        return _imgMat;
    }

    void loadImg(std::string img_path) {
        _imgPath = img_path;
        _imgMat = cv::imread(_imgPath);
    }
private:
    std::string _imgPath;
    cv::Mat _imgMat;
};