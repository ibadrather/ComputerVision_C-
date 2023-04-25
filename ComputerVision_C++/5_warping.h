#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

// warp image
cv::Mat warpImage(const cv::Mat& inputImage, const std::vector<cv::Point2f> sourcePoints, int width, int height);