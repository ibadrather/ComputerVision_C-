#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

// resize
cv::Mat resizeImage(const cv::Mat& inputImage, const cv::Size& size);

// scale
cv::Mat scaleImage(const cv::Mat& inputImage, double scaleX, double scaleY);

// crop
cv::Mat cropImage(const cv::Mat& inputImage, const cv::Rect& rect);