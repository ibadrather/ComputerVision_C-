#include <iostream>
#include <opencv2/opencv.hpp>
#include "7_shape_contour_detection.h"

/**
 * @brief Preprocesses an image for contour detection by applying Gaussian blur, Canny edge detection, dilation, and erosion.
 *
 * @param inputImage a BGR image.
 * @param lowerThreshold Lower threshold for Canny edge detection.
 * @param upperThreshold Upper threshold for Canny edge detection.
 * @param dilationSize Size of the dilation kernel.
 * @param erosionSize Size of the erosion kernel.
 * @return cv::Mat Preprocessed image.
 */
cv::Mat preprocessImageForContourDetection(cv::Mat inputImage, int lowerThreshold, int upperThreshold, int dilationSize, int erosionSize) {
    // convert the image to grayscale
    cv::Mat grayImage;
    cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);
    
    // Apply Gaussian blur
    cv::Size kernelSize(5, 5);
    double sigma = 0;
    cv::Mat blurredImage;
    cv::GaussianBlur(grayImage, blurredImage, kernelSize, sigma);

    // Apply Canny edge detection
    cv::Mat cannyImage;
    cv::Canny(blurredImage, cannyImage, lowerThreshold, upperThreshold);

    // Apply dilation to connect broken edges and fill gaps
    cv::Mat dilatedImage;
    cv::Mat dilationKernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * dilationSize + 1, 2 * dilationSize + 1));
    cv::dilate(cannyImage, dilatedImage, dilationKernel);

    // Apply erosion to remove noise introduced during dilation and refine object boundaries
    // This combined operation of dilation followed by erosion is called "closing"
    cv::Mat erodedImage;
    cv::Mat erosionKernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * erosionSize + 1, 2 * erosionSize + 1));
    cv::erode(dilatedImage, erodedImage, erosionKernel);

    return erodedImage;
}


/**
 * @brief Finds and draws contours on a given preprocessed image if their area is above the specified threshold.
 *
 * @param preprocessedImage Input image after preprocessing (e.g., edge detection, dilation, and erosion).
 * @param drawingImage Image to draw the contours on.
 * @param minArea Minimum area for a contour to be drawn.
 * @return cv::Mat Image with drawn contours.
 */
cv::Mat findAndDrawContours(cv::Mat preprocessedImage, cv::Mat drawingImage, double minArea) {
    // Check if the input images are empty
    if (preprocessedImage.empty() || drawingImage.empty()) {
        std::cerr << "Error: One or both input images are empty." << std::endl;
        return cv::Mat();
    }

    // Check if the input images have the same dimensions
    if (preprocessedImage.size() != drawingImage.size()) {
        std::cerr << "Error: Input images have different dimensions." << std::endl;
        return cv::Mat();
    }

    // Find contours
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(preprocessedImage, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    // Draw contours with area greater than minArea
    for (int i = 0; i < contours.size(); i++) {
        double area = cv::contourArea(contours[i]);
        if (area > minArea) {
            cv::Scalar color = cv::Scalar(0, 255, 0);
            cv::drawContours(drawingImage, contours, i, color, 2, cv::LINE_8, hierarchy, 0);
        }
    }

    return drawingImage;
}



