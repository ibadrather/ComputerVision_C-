#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>

#include "8_callibration_checkerboard.h"


void checkboardCameraCalib();


int main() {
    
    // Checkboard camera calibration
    checkboardCameraCalib();
    

    return 0;
}


void checkboardCameraCalib() {
    std::string checkerboardImagesDir = "Resources/checkerboard_images";

    std::vector<std::string> checkerboardImagesPaths = getImagePathsFromFolder(checkerboardImagesDir);

    // Get the image paths from the directory
    std::vector<std::string> fileNames = getImagePathsFromFolder(checkerboardImagesDir);

    // Define the pattern size and checkerboard dimensions
    cv::Size patternSize(25 - 1, 18 - 1);
    int checkerboardDimensions[2] = { 25, 18 };

    // Detect and refine corners
    std::vector<std::vector<cv::Point3f>> Q;
    std::vector<std::vector<cv::Point2f>> q = detectCorners(fileNames, patternSize, checkerboardDimensions, Q);

    // Calibrate the camera and compute errors
    cv::Matx33f K(cv::Matx33f::eye());
    cv::Vec<float, 5> k(0, 0, 0, 0, 0);
    cv::Size frameSize(1440, 1080);
    float error = calibrateCameraAndComputeErrors(Q, q, frameSize, K, k);

    // Print the results
    std::cout << "Reprojection error = " << error << "\nK =\n"
        << K << "\nk=\n"
        << k << std::endl;

    // Undistort the images
    cv::Mat mapX, mapY;
    initUndistortMaps(K, k, frameSize, mapX, mapY);
    undistortImages(fileNames, mapX, mapY);

    // Save the camera calibration
    std::string outputFilename = "camera_calibration_checkerboard.txt";

    if (saveCameraCalibration(outputFilename, K, k, frameSize)) {
        std::cout << "Camera calibration parameters saved to " << outputFilename << std::endl;
    }
    else {
        std::cerr << "Error: Unable to save camera calibration parameters." << std::endl;
    }

}

