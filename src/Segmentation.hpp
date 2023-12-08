#pragma once

#include "opencv2/opencv.hpp"
#include "Utils.hpp"

class Segmentation {
public:
    cv::Mat globalThreshold(cv::Mat srcImg, int thres = 100) {
        auto img = Utils().cvt2dVector<int>(srcImg);

        int allSum = 0;
        for(auto& line : img)
            for(auto& pixel: line)
                allSum += pixel;
        allSum /= (img.size() * img[0].size());

        int t_0 = allSum;
        int t_1 = 0;
        while(abs(t_0 - t_1) > 1) {
            int m_0 = 0, m_1 = 0;
            int c_0 = 0, c_1 = 0;
            for(auto& line: img) {
                for (auto &pixel: line) {
                    if (pixel < t_0) {
                        m_0 += pixel;
                        c_0++;
                    } else {
                        m_1 += pixel;
                        c_1++;
                    }
                }
            }
            m_0 /= c_0;
            m_1 /= c_1;
            t_1 = (m_0 + m_1) / 2;
            int tmp = t_0;
            t_0 = t_1;
            t_1 = tmp;
        }

        for(auto& line: img)
            for(auto& pixel: line)
                if(pixel > t_0) {
                    pixel = 255;
                } else {
                    pixel = 0;
                }

        return Utils().cvtCvMat(img);
    }

    cv::Mat otsuThreshold(cv::Mat srcImg) {
        auto img = Utils().cvt2dVector<int>(srcImg);
        auto histogram = std::vector<int>(256);
        auto probability = std::vector<double>(256);

        for(auto line: img)
            for(auto pixel: line)
                histogram[pixel]++;

        for(auto i = 0; i < 256; ++i)
            probability[i] = double(histogram[i]) / double(img.size() * img[0].size());

        int threshold = 0;
        double delta_max = 0;
        double w0, w1, u0_tmp, u1_tmp, u0, u1, delta_tmp;
        for(auto i = 0; i < 256; ++i) {
            w0 = w1 = u0 = u1 = u0_tmp = u1_tmp= delta_tmp = 0;
            for(auto j = 0; j < 256; ++j) {
                if(j <= i) {
                    w0 += probability[j];
                    u0_tmp += j * probability[j];
                } else {
                    w1 += probability[j];
                    u1_tmp += j * probability[j];
                }
            }

            u0 = u0_tmp / w0;
            u1 = u1_tmp / w1;

            delta_tmp = w0 * w1 * pow(u0 - u1, 2);
            if(delta_tmp > delta_max) {
                delta_max = delta_tmp;
                threshold = i;
            }
        }

        for(auto& line: img)
            for(auto& pixel: line) {
                if (pixel > threshold)
                    pixel = 255;
                else
                    pixel = 0;
            }

        return Utils().cvtCvMat(img);
    }

    cv::Mat cannyBorderDetect(cv::Mat srcImg) {
        cv::Mat ret;
        cv::Canny(srcImg, ret, 50, 100);
        return ret;
    }
};