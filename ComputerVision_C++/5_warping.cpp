#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "5_warping.h"

/**
 * Warps an input image using the provided source points and destination dimensions.
 *
 * @param inputImage The input image to be warped.
 * @param sourcePoints A vector containing 4 source points that define the region to be warped.
 * @param width The width of the destination (warped) image.
 * @param height The height of the destination (warped) image.
 * @return The warped image.
 */
cv::Mat warpImage(const cv::Mat& inputImage, const std::vector<cv::Point2f>& sourcePoints, int width, int height) {

    // Define destination points for the warped image
    std::vector<cv::Point2f> destinationPoints;
    destinationPoints.push_back(cv::Point2f(0.0f, 0.0f));
    destinationPoints.push_back(cv::Point2f(width, 0.0f));
    destinationPoints.push_back(cv::Point2f(0.0f, height));
    destinationPoints.push_back(cv::Point2f(width, height));

    // Get the perspective transform matrix
    cv::Mat transformMatrix = cv::getPerspectiveTransform(sourcePoints, destinationPoints);

    // Warp the input image using the transform matrix
    cv::Mat warpedImage;
    cv::warpPerspective(inputImage, warpedImage, transformMatrix, cv::Size(width, height));

    return warpedImage;
}
