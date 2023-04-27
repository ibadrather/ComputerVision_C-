#include <iostream>
#include <string>
#include <opencv2/core.hpp> // Include OpenCV core header for cv::glob
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <fstream>

#include "8_callibration_checkerboard.h" 


// Get image paths from a folder
std::vector<std::string> getImagePathsFromFolder(const std::string& folderPath) {
    std::vector<std::string> imagePaths;
    std::vector<cv::String> tempPaths;

    // List of extensions to search for
    std::vector<std::string> extensions = { ".png", ".jpg", ".jpeg" };

    for (const auto& ext : extensions) {
        std::string searchPattern = folderPath + "/*" + ext;
        cv::glob(searchPattern, tempPaths, false);
         
        // Insert the paths to the end of the vector
        imagePaths.insert(imagePaths.end(), tempPaths.begin(), tempPaths.end());
    }

    return imagePaths;
}


/**
 * @brief Generates the world coordinates for 3D points on the checkerboard.
 *
 * This function generates a vector of 3D points representing the world
 * coordinates of the checkerboard corners. It takes the dimensions of the
 * checkerboard as input and returns the world coordinates.
 *
 * @param checkerboardSize An array containing the dimensions of the checkerboard.
 *                         checkerboardSize[0] corresponds to the number of columns,
 *                         and checkerboardSize[1] corresponds to the number of rows.
 * @return A vector of 3D points representing the world coordinates of the
 *         checkerboard corners.
 */
std::vector<cv::Point3f> generateWorldCoordinates(const int checkerboardSize[2]) {
    std::vector<cv::Point3f> worldCoordinates;
    for (int row = 1; row < checkerboardSize[1]; ++row) {
        for (int col = 1; col < checkerboardSize[0]; ++col) {
            worldCoordinates.push_back(cv::Point3f(col, row, 0));
        }
    }
    return worldCoordinates;
}


/**
 * @brief Detects checkerboard corners and refines them using cv::cornerSubPix().
 *
 * This function takes a list of file names containing checkerboard images,
 * the dimensions of the checkerboard, and a reference to a vector of world
 * coordinates. It detects the corners in each image and refines them using
 * cv::cornerSubPix(). The function updates the input world coordinates
 * and returns the detected and refined corners.
 *
 * @param fileNames A vector of strings representing the file paths of the checkerboard images.
 * @param patternSize A cv::Size object representing the dimensions of the checkerboard.
 * @param checkerboardDimensions An array containing the dimensions of the checkerboard.
 * @param Q A reference to a vector of vectors of 3D points representing the world coordinates of the checkerboard corners.
 * @return A vector of vectors of 2D points representing the detected and refined corners.
 */
std::vector<std::vector<cv::Point2f>> detectCorners(const std::vector<std::string>& fileNames, const cv::Size& patternSize, const int checkerboardDimensions[2], std::vector<std::vector<cv::Point3f>>& Q, bool displayDetectedPoints) {
    std::vector<std::vector<cv::Point2f>> q(fileNames.size());
    std::vector<cv::Point3f> objp = generateWorldCoordinates(checkerboardDimensions);

    for (std::size_t i = 0; i < fileNames.size(); i++) {
        std::cout << fileNames[i] << std::endl;

        cv::Mat img = cv::imread(fileNames[i]);
        cv::Mat gray;
        cv::cvtColor(img, gray, cv::COLOR_RGB2GRAY);

        bool patternFound = cv::findChessboardCorners(gray, patternSize, q[i], cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK);

        if (patternFound) {
            cv::cornerSubPix(gray, q[i], cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 30, 0.1));
            Q.push_back(objp);
        }

        if (displayDetectedPoints) {
            
            cv::drawChessboardCorners(img, patternSize, q[i], patternFound);
            cv::imshow("chessboard detection", img);
            cv::waitKey(0);

        }



    }

    return q;
}


/**
 * @brief Calibrates the camera using the detected checkerboard corners and computes the reprojection error.
 * @param Q The world coordinates of the checkerboard corners.
 * @param q The image coordinates of the checkerboard corners.
 * @param frameSize The size of the images used for calibration.
 * @param K The intrinsic camera matrix to be computed.
 * @param k The distortion coefficients to be computed.
 * @return The reprojection error.
 */
float calibrateCameraAndComputeErrors(const std::vector<std::vector<cv::Point3f>>& Q, const std::vector<std::vector<cv::Point2f>>& q, const cv::Size& frameSize, cv::Matx33f& K, cv::Vec<float, 5>& k) {
    std::vector<cv::Mat> rvecs, tvecs;
    int flags = cv::CALIB_FIX_ASPECT_RATIO + cv::CALIB_FIX_K3 +
        cv::CALIB_ZERO_TANGENT_DIST + cv::CALIB_FIX_PRINCIPAL_POINT;

    float error = cv::calibrateCamera(Q, q, frameSize, K, k, rvecs, tvecs, flags);

    return error;
}

/**
 * @brief Undistorts the images using the computed intrinsic camera matrix and distortion coefficients.
 * @param fileNames The paths to the images to be undistorted.
 * @param mapX The x coordinates of the undistorted image points.
 * @param mapY The y coordinates of the undistorted image points.
 */
void undistortImages(const std::vector<std::string>& fileNames, const cv::Mat& mapX, const cv::Mat& mapY) {
    for (const auto& fileName : fileNames) {
        cv::Mat img = cv::imread(fileName);
        cv::Mat undistortedImg;

        cv::remap(img, undistortedImg, mapX, mapY, cv::INTER_LINEAR);

        // Join the images and display them side by side and reduce their size by half for display purposes.
        cv::Mat combinedImg;
        cv::hconcat(img, undistortedImg, combinedImg);
        cv::resize(combinedImg, combinedImg, cv::Size(), 0.5, 0.5);

        cv::imshow("Correction Comparison", combinedImg);
        cv::waitKey(0);
    }
}


/**
 * @brief Initializes the undistortion maps using the computed intrinsic camera matrix and distortion coefficients.
 * @param K The intrinsic camera matrix.
 * @param k The distortion coefficients.
 * @param frameSize The size of the images used for calibration.
 * @param mapX The x coordinates of the undistorted image points to be computed.
 * @param mapY The y coordinates of the undistorted image points to be computed.
 */
void initUndistortMaps(const cv::Matx33f& K, const cv::Vec<float, 5>& k, const cv::Size& frameSize, cv::Mat& mapX, cv::Mat& mapY) {
    cv::initUndistortRectifyMap(K, k, cv::Matx33f::eye(), K, frameSize, CV_32FC1, mapX, mapY);
}



/**
 * @brief Saves the camera calibration parameters to a file.
 * @param filename The name of the file to save the calibration parameters.
 * @param K The intrinsic camera matrix.
 * @param k The distortion coefficients.
 * @param frameSize The size of the images used for calibration.
 * @return true if the parameters were saved successfully, false otherwise.
 */
bool saveCameraCalibration(const std::string& filename, const cv::Matx33f& K, const cv::Vec<float, 5>& k, const cv::Size& frameSize) {
    std::ofstream outFile(filename);

    if (!outFile) {
        std::cerr << "Error: Could not open file for saving camera calibration parameters." << std::endl;
        return false;
    }

    outFile << "Intrinsic Camera Matrix:" << std::endl;
    outFile << K << std::endl;

    outFile << "Distortion Coefficients:" << std::endl;
    outFile << k << std::endl;

    outFile << "Frame Size:" << std::endl;
    outFile << frameSize << std::endl;

    outFile.close();
    return true;
}
