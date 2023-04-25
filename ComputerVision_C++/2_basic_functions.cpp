#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "2_basic_functions.h"

// load color image as BGR
cv::Mat loadBGRImage(const std::string& imagePath)
{
	cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
	return image;
}

// display image
void displayImage(const cv::Mat& image, const std::string& windowName)
{
	cv::imshow(windowName, image);
	cv::waitKey(0);
}

// convert an image to grayscale
cv::Mat convertToGrayscale(const cv::Mat& image)
{
	cv::Mat grayImage;
	cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
	return grayImage;
}

// apply gaussian blur to an image
cv::Mat applyGaussianBlur(const cv::Mat& inputImage, const cv::Size& kernelSize, double sigmaX)
{
	cv::Mat outputImage;
	cv::GaussianBlur(inputImage, outputImage, kernelSize, sigmaX);
	return outputImage;
}

// canny edge detection
cv::Mat applyCannyEdgeDetection(const cv::Mat& inputImage, double threshold1, double threshold2)
{
	cv::Mat cannyImage, blurredImage;

	// blur the image
	cv::GaussianBlur(inputImage, blurredImage, cv::Size(5, 5), 0);

	cv::Canny(blurredImage, cannyImage, threshold1, threshold2);
	return cannyImage;
}


// dialate
cv::Mat applyDialate(const cv::Mat& inputImage, int kernelSize)
{
	cv::Mat dialateImage;
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kernelSize, kernelSize));
	cv::dilate(inputImage, dialateImage, kernel);
	return dialateImage;
}

// erode
cv::Mat applyErode(const cv::Mat& inputImage, int kernelSize)
{
	cv::Mat erodeImage;
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kernelSize, kernelSize));
	cv::erode(inputImage, erodeImage, kernel);
	return erodeImage;
}