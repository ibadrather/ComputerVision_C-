#pragma once
#include <opencv2/opencv.hpp>

// apply color mask based on HSV color range: lower and upper
cv::Mat applyColorMask(const cv::Mat& bgrImage, const cv::Point3f& lower, const cv::Point3f& upper);

// generate masked images for all frames based on a given HSV color range
std::vector<cv::Mat> generateMaskedImages(const std::vector<cv::Mat>& frames, const cv::Point3f& lower, const cv::Point3f& upper);

// save vector to a text file
void saveVectorToFile(const std::vector<cv::Point2f> pointVector, const std::string& fileName);

// find the 2D position of an object in a binary frame
cv::Point2f findObjectPosition(const cv::Mat& frame);