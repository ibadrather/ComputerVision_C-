#include <iostream>
#include <opencv2/opencv.hpp>
#include "6_color_detection.h"


/**
 * @brief Displays an interactive window with trackbars to select a color range in the HSV color space.
 *
 * @param bgrImage Input image in the BGR color space.
 */
void interactiveHSVColorRangeSelection(const cv::Mat& bgrImage) {
    // Convert BGR image to HSV
    cv::Mat hsvImage;
    cv::cvtColor(bgrImage, hsvImage, cv::COLOR_BGR2HSV);

    // Define the color range
    int hueMinimum = 0, hueMaximum = 19;
    int saturationMinimum = 110, saturationMaximum = 240;
    int valueMinimum = 153, valueMaximum = 255;

    // Create a window with trackbars
    cv::namedWindow("Trackbars", cv::WINDOW_NORMAL);
    cv::createTrackbar("Hue Min", "Trackbars", &hueMinimum, 179);
    cv::createTrackbar("Hue Max", "Trackbars", &hueMaximum, 179);
    cv::createTrackbar("Sat Min", "Trackbars", &saturationMinimum, 255);
    cv::createTrackbar("Sat Max", "Trackbars", &saturationMaximum, 255);
    cv::createTrackbar("Val Min", "Trackbars", &valueMinimum, 255);
    cv::createTrackbar("Val Max", "Trackbars", &valueMaximum, 255);

    while (true) {
        // Update the color range based on trackbar values
        cv::Scalar lower(hueMinimum, saturationMinimum, valueMinimum);
        cv::Scalar upper(hueMaximum, saturationMaximum, valueMaximum);

        // Detect the color
        cv::Mat mask;
        cv::inRange(hsvImage, lower, upper, mask);

        // Display the mask
        cv::imshow("Mask", mask);

        // Break the loop if the 'Esc' key is pressed
        if (cv::waitKey(1) == 27) {
            break;
        }
    }
}