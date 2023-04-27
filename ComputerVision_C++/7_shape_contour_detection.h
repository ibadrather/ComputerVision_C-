#pragma once
#include <opencv2/opencv.hpp>


// preprocessor directives
cv::Mat preprocessImageForContourDetection(cv::Mat inputImage, int lowerThreshold = 50, int upperThreshold = 100, int dilationSize = 5, int erosionSize = 1);


// find and draw contours
cv::Mat findAndDrawContours(cv::Mat preprocessedImage, cv::Mat drawingImage, double minArea = 1000.0);