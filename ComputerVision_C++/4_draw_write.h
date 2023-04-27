#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

// Create an image
cv::Mat createImage(int width, int height, cv::Scalar color);

// Draw a line on the input image
cv::Mat drawLineOnImage(cv::Mat& inputImage, cv::Point start, cv::Point end, cv::Scalar color, int thickness);

// Draw a rectangle on the input image
cv::Mat drawRectangleOnImage(cv::Mat& inputImage, cv::Point topLeft, cv::Point bottomRight, cv::Scalar color, int thickness);

// Draw a circle on the input image
cv::Mat drawCircleOnImage(cv::Mat& inputImage, cv::Point center, int radius, cv::Scalar color, int thickness);

// Add text to the input image
cv::Mat drawTextOnImage(cv::Mat& inputImage, const std::string& text, const cv::Point& origin, int fontFace, double fontScale, const cv::Scalar& color, int thickness);
