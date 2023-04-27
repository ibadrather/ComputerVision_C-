#pragma once

// Get image paths from a folder
std::vector<std::string> getImagePathsFromFolder(const std::string& folderPath);


// Generates the world coordinates for 3D points on the checkerboard
std::vector<cv::Point3f> generateWorldCoordinates(const int checkerboardSize[2]);

// Detect Corners in 2d plane
std::vector<std::vector<cv::Point2f>> detectCorners(const std::vector<std::string>& fileNames, const cv::Size& patternSize, const int checkerboardDimensions[2], std::vector<std::vector<cv::Point3f>>& Q, bool displayDetectedPoints=false);


// Calibrate camera and compute errors
float calibrateCameraAndComputeErrors(const std::vector<std::vector<cv::Point3f>>& Q, const std::vector<std::vector<cv::Point2f>>& q, const cv::Size& frameSize, cv::Matx33f& K, cv::Vec<float, 5>& k);

// Undistort the images
void undistortImages(const std::vector<std::string>& fileNames, const cv::Mat& mapX, const cv::Mat& mapY);


// init undistort maps
void initUndistortMaps(const cv::Matx33f& K, const cv::Vec<float, 5>& k, const cv::Size& frameSize, cv::Mat& mapX, cv::Mat& mapY);


// Save camera callibration to a file
bool saveCameraCalibration(const std::string& filename, const cv::Matx33f& K, const cv::Vec<float, 5>& k, const cv::Size& frameSize);