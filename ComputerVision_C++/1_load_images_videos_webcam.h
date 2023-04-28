#pragma once
#include <vector>
#include <string>
#include <opencv2/core.hpp>


// Display an image from a file.
void loadDisplayImage(const std::string& imagePath);

// Display a video from a file.
void loadDisplayVideo(const std::string& videoPath);

// Display a video from a webcam.
void displayWebcam(int cameraId);

// Load all frames of a video from a file into a vector of cv::Mat.
std::vector<cv::Mat> loadVideoFrames(const std::string& videoPath);

// display video frames
void displayVideoFrames(const std::vector<cv::Mat>& frames, const std::string& windowName = "Video");
