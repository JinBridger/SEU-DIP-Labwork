#pragma once

#include "Core.hpp"
#include "Histogram.hpp"

#include <QQuickImageProvider>
#include <opencv2/opencv.hpp>


class ImgProvider : public QQuickImageProvider {
public:
    ImgProvider(Core* imgCorePtr) : QQuickImageProvider(QQuickImageProvider::Pixmap), _imgCore(imgCorePtr) {}

    QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize) override {
        if (id.startsWith("ori"))
            return cvtMat2Pixmap(_imgCore->getOriImgMat());
        if (id.startsWith("dst"))
            return cvtMat2Pixmap(_imgCore->getDstImgMat());

        if (id.startsWith("hist_ori"))
            return cvtMat2Pixmap(Histogram().getHistogram(_imgCore->getOriImgMat()));
        if (id.startsWith("hist_dst"))
            return cvtMat2Pixmap(Histogram().getHistogram(_imgCore->getDstImgMat()));
    }

private:
    QPixmap cvtMat2Pixmap(const cv::Mat& mat) {
        QImage img;
        std::cout << mat.type();
        switch (mat.type()) {
        case CV_8UC1:
            img = QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
            break;
        case CV_8UC3:
            img = QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
            img = img.rgbSwapped();
            break;
        case CV_8UC4:
            img = QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
            break;
        default:
            break;
        }

        QPixmap pixmap = QPixmap::fromImage(img);
        return pixmap;
    }

    Core* _imgCore;
};