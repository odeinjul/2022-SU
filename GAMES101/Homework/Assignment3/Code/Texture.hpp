//
// Created by LEI XU on 4/27/19.
//

#ifndef RASTERIZER_TEXTURE_H
#define RASTERIZER_TEXTURE_H
#include "global.hpp"
#include <eigen3/Eigen/Eigen>
#include <opencv2/opencv.hpp>
class Texture{
private:
    cv::Mat image_data;

public:
    Texture(const std::string& name)
    {
        image_data = cv::imread(name);
        cv::cvtColor(image_data, image_data, cv::COLOR_RGB2BGR);
        width = image_data.cols;
        height = image_data.rows;
    }

    int width, height;

    Eigen::Vector3f getColor(float u, float v)
    {
        auto u_img = u * width;
        auto v_img = (1 - v) * height;
        auto color = image_data.at<cv::Vec3b>(v_img, u_img);
        return Eigen::Vector3f(color[0], color[1], color[2]);
    }

    Eigen::Vector3f getColorBilinear(float u, float v)
    {
        auto u_img = u * width;
        auto v_img = (1 - v) * height;
        auto u0 = int(u_img + 0.5);
        auto v0 = int(v_img + 0.5);
        auto u00 = image_data.at<cv::Vec3b>(v0 - 0.5, u0 - 0.5);
        auto u01 = image_data.at<cv::Vec3b>(v0 + 0.5, u0 - 0.5);
        auto u10 = image_data.at<cv::Vec3b>(v0 - 0.5, u0 + 0.5);
        auto u11 = image_data.at<cv::Vec3b>(v0 + 0.5, u0 + 0.5);

        auto s = u_img - (u0 -0.5);
        auto top = u11 * s + u01 * (1 - s);
        auto bottom = u10 * s + u00 * (1 - s);

        auto t = v_img - (v0 - 0.5);
        auto color = bottom * (1 - t) + top * t;
        return Eigen::Vector3f(color[0], color[1], color[2]);
    }

};
#endif //RASTERIZER_TEXTURE_H
