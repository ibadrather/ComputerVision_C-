#pragma once
#include <string>

// Display an image from a file.
void loadDisplayImage(const std::string& imagePath);

// Display a video from a file.
void loadDisplayVideo(const std::string& videoPath);

// Display a video from a webcam.
void displayWebcam(int cameraId);
