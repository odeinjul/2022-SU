#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>

std::vector<cv::Point2f> control_points;

void mouse_handler(int event, int x, int y, int flags, void *userdata) 
{
    if (event == cv::EVENT_LBUTTONDOWN && control_points.size() < 4) 
    {
        std::cout << "Left button of the mouse is clicked - position (" << x << ", "
        << y << ")" << '\n';
        control_points.emplace_back(x, y);
    }     
}

void naive_bezier(const std::vector<cv::Point2f> &points, cv::Mat &window) 
{
    auto &p_0 = points[0];
    auto &p_1 = points[1];
    auto &p_2 = points[2];
    auto &p_3 = points[3];

    for (double t = 0.0; t <= 1.0; t += 0.001) 
    {
        auto point = std::pow(1 - t, 3) * p_0 + 3 * t * std::pow(1 - t, 2) * p_1 +
                 3 * std::pow(t, 2) * (1 - t) * p_2 + std::pow(t, 3) * p_3;

        window.at<cv::Vec3b>(point.y, point.x)[2] = 255;
    }
}

cv::Point2f recursive_bezier(const std::vector<cv::Point2f> &control_points, float t) 
{
    // Implement de Casteljau's algorithm
    auto p_0 = control_points[0];
    auto p_1 = control_points[1];
    auto p_2 = control_points[2];
    auto p_3 = control_points[3];

    auto p_return = pow(1 - t, 3) * p_0 + 3 * pow(1 - t, 2) * t * p_1 +
            3 * pow(t, 2) * (1 - t) * p_2 + pow(t, 3) * p_3;

    return p_return;

}

void bezier(const std::vector<cv::Point2f> &control_points, cv::Mat &window) 
{
    // Iterate through all t = 0 to t = 1 with small steps, and call de Casteljau's
    // recursive Bezier algorithm.
    for(float t = 0; t <= 1; t +=0.001)
    {
        auto point = recursive_bezier(control_points, t);
        window.at<cv::Vec3b>(point.y, point.x)[1] = 255;
    }

}

void bezier_antialiasing(const std::vector<cv::Point2f> &control_points, cv::Mat &window)
{
    // Iterate through all t = 0 to t = 1 with small steps, and call de Casteljau's
    // recursive Bezier algorithm.
    for(float t = 0; t <= 1; t +=0.001){
        auto point = recursive_bezier(control_points, t);
        int x_0 = int(point.x + 0.5), y_0 = int(point.y + 0.5);
        std::vector<cv::Point2i> points = {
                cv::Point2i(x_0, y_0), cv::Point2i(x_0 - 1, y_0),
                cv::Point2i(x_0, y_0 - 1), cv::Point2i(x_0 - 1, y_0 - 1)
        };
        std::vector<float> distance;
        float dis_sum = 0;
        for(auto p : points) {
            float x_temp = p.x + 0.5f, y_temp = p.y + 0.5f;
            float dis_temp = sqrt(2) - sqrt(pow(x_temp - point.x, 2) + pow(y_temp - point.y, 2));
            dis_sum += dis_temp;
            distance.push_back(dis_temp);
        }
        for(int i = 0; i < 4; i ++) {
            float k = distance[i] / dis_sum ;
            window.at<cv::Vec3b>(points[i].y, points[i].x)[1] = std::min(255.f, 255.f * k + window.at<cv::Vec3b>(points[i].y, points[i].x)[1]);
        }
    }


}

int main() 
{
    cv::Mat window = cv::Mat(700, 700, CV_8UC3, cv::Scalar(0));
    cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
    cv::namedWindow("Bezier Curve", cv::WINDOW_AUTOSIZE);

    cv::setMouseCallback("Bezier Curve", mouse_handler, nullptr);

    int key = -1;
    while (key != 27) 
    {
        for (auto &point : control_points) 
        {
            cv::circle(window, point, 3, {255, 255, 255}, 3);
        }

        if (control_points.size() == 4) 
        {
            //naive_bezier(control_points, window);
            bezier_antialiasing(control_points, window);

            cv::imshow("Bezier Curve", window);
            cv::imwrite("my_bezier_curve.png", window);
            key = cv::waitKey(0);

            return 0;
        }

        cv::imshow("Bezier Curve", window);
        key = cv::waitKey(20);
    }

return 0;
}
