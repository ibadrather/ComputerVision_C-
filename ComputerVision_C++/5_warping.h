#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

/**
 * Warps an input image using the provided source points and destination dimensions.
 *
 * @param inputImage The input image to be warped.
 * @param sourcePoints A vector containing 4 source points that define the region to be warped.
 * @param width The width of the destination (warped) image.
 * @param height The height of the destination (warped) image.
 * @return The warped image.
 */
cv::Mat warpImage(const cv::Mat& inputImage, const std::vector<cv::Point2f>& sourcePoints, int width, int height);
