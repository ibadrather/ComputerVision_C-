#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "3_resize_crop.h"

// resize image
cv::Mat resizeImage(const cv::Mat& inputImage, const cv::Size& size) {
	cv::Mat outputImage;
	cv::resize(inputImage, outputImage, size);
	return outputImage;
}

// sclae image
cv::Mat scaleImage(const cv::Mat& inputImage, double scaleX, double scaleY) {
	cv::Mat outputImage;
	cv::resize(inputImage, outputImage, cv::Size(), scaleX, scaleX);
	return outputImage;
}


// crop image
cv::Mat cropImage(const cv::Mat& inputImage, const cv::Rect& rect) {
	cv::Mat outputImage;
	outputImage = inputImage(rect);
	return outputImage;
}

