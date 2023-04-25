#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "5_warping.h"

// warp image
cv::Mat warpImage(const cv::Mat& inputImage, const std::vector<cv::Point2f> sourcePoints, int width, int height) {

	std::vector<cv::Point2f> destinationPoints;
	destinationPoints.push_back(cv::Point2f(0.0f, 0.0f));
	destinationPoints.push_back(cv::Point2f(width, 0.0f));
	destinationPoints.push_back(cv::Point2f(0.0f, height));
	destinationPoints.push_back(cv::Point2f(width, height));

	// get the perspective transform matrix
	cv::Mat transformMatrix = cv::getPerspectiveTransform(sourcePoints, destinationPoints);

	// warp the image
	cv::Mat warpedImage;
	cv::warpPerspective(inputImage, warpedImage, transformMatrix, cv::Size(width, height));
	return warpedImage;
}