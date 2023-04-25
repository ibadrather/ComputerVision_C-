#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

// load color image as BGR
cv::Mat loadBGRImage(const std::string& imagePath);

// display image
void displayImage(const cv::Mat& image, const std::string& windowName);

// convert an image to grayscale
cv::Mat convertToGrayscale(const cv::Mat& image);

// apply gaussian blur to an image
cv::Mat applyGaussianBlur(const cv::Mat& inputImage, const cv::Size& kernelSize, double sigmaX);

// canny edge detection
cv::Mat applyCannyEdgeDetection(const cv::Mat& inputImage, double threshold1, double threshold2);

// dialate
cv::Mat applyDialate(const cv::Mat& inputImage, int kernelSize);

// erode
cv::Mat applyErode(const cv::Mat& inputImage, int kernelSize);