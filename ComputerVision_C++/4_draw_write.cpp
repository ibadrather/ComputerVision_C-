#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "4_draw_write.h"

// create an image
cv::Mat createImage(int width, int height, cv::Scalar color) {
	cv::Mat image(height, width, CV_8UC3, color);
	return image;
}

// draw a line
cv::Mat drawLine(cv::Mat& inputImage, cv::Point start, cv::Point end, cv::Scalar color, int thickness) {
	cv::Mat outputImage = inputImage.clone();
	cv::line(outputImage, start, end, color, thickness);
	return outputImage;
}

// draw a rectangle
cv::Mat drawRectangle(cv::Mat& inputImage, cv::Point topLeft, cv::Point bottomRight, cv::Scalar color, int thickness) {
	cv::Mat outputImage = inputImage.clone();
	cv::rectangle(outputImage, topLeft, bottomRight, color, thickness);
	return outputImage;
}

// draw a circle
cv::Mat drawCircle(cv::Mat& inputImage, cv::Point center, int radius, cv::Scalar color, int thickness) {
	cv::Mat outputImage = inputImage.clone();
	cv::circle(outputImage, center, radius, color, thickness);
	return outputImage;
}

// put text
cv::Mat drawText(cv::Mat& inputImage, std::string text, cv::Point origin, int fontFace, double fontScale, cv::Scalar color, int thickness) {
	cv::Mat outputImage = inputImage.clone();
	cv::putText(outputImage, text, origin, fontFace, fontScale, color, thickness);
	return outputImage;
}