#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>


/**
 * @brief Applies a range-based color mask on an input BGR image.
 *
 * @param bgrImage The input BGR image to be processed.
 * @param lower The lower bound for the range in the HSV color space (as cv::Point3f).
 * @param upper The upper bound for the range in the HSV color space (as cv::Point3f).
 * @return cv::Mat The processed image with a color mask applied.
 */
cv::Mat applyColorMask(const cv::Mat& bgrImage, const cv::Point3f& lower, const cv::Point3f& upper) {
    // Convert BGR image to HSV
    cv::Mat hsvImage;
    cv::cvtColor(bgrImage, hsvImage, cv::COLOR_BGR2HSV);

    cv::Scalar lowerBound(lower.x, lower.y, lower.z);
    cv::Scalar upperBound(upper.x, upper.y, upper.z);

    // Detect the color
    cv::Mat mask;
    cv::inRange(hsvImage, lowerBound, upperBound, mask);

    return mask;
}


/**
 * @brief Generates masked images for all frames based on a given HSV color range.
 *
 * @param frames A vector containing the input video frames.
 * @param lower The lower bound for the HSV color range (as cv::Point3f).
 * @param upper The upper bound for the HSV color range (as cv::Point3f).
 * @return std::vector<cv::Mat> A vector containing the masked images.
 */
std::vector<cv::Mat> generateMaskedImages(const std::vector<cv::Mat>& frames, const cv::Point3f& lower, const cv::Point3f& upper) {
    std::vector<cv::Mat> maskedImages;
    for (const auto& frame : frames) {
        maskedImages.push_back(applyColorMask(frame, lower, upper));
    }
    return maskedImages;
}


// save vector to a text file
void saveVectorToFile(const std::vector<cv::Point2f> pointVector, const std::string& fileName) {
	std::ofstream file(fileName);
    if (file.is_open()) {
        for (const auto& point : pointVector) {
			file << point.x << "," << point.y << std::endl;
		}
		file.close();
	}
}

/**
 * @brief Finds the 2D position of an object in a binary frame.
 *
 * @param frame The input binary frame containing the object.
 * @return cv::Point2f The 2D position of the object.
 */
cv::Point2f findObjectPosition(const cv::Mat& frame) {
    // Calculate moments of the binary image
    cv::Moments m = cv::moments(frame, true);

    // Check for division by zero
    if (m.m00 == 0) {
        return cv::Point2f(-1, -1);
    }

    // Calculate the centroid (center of mass) of the object
    float x = static_cast<float>(m.m10 / m.m00);
    float y = static_cast<float>(m.m01 / m.m00);

    return cv::Point2f(x, y);
}