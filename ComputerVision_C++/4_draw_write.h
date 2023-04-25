#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

// create an image
cv::Mat createImage(int width, int heigh, cv::Scalar color);
// draw a line
cv::Mat drawLine(cv::Mat& inputImage, cv::Point start, cv::Point end, cv::Scalar color, int thickness);

// draw a rectangle
cv::Mat drawRectangle(cv::Mat& inputImage, cv::Point topLeft, cv::Point bottomRight, cv::Scalar color, int thickness);

// draw a circle
cv::Mat drawCircle(cv::Mat& inputImage, cv::Point center, int radius, cv::Scalar color, int thickness);

// put text
cv::Mat drawText(cv::Mat& inputImage, std::string text, cv::Point origin, int fontFace, double fontScale, cv::Scalar color, int thickness);