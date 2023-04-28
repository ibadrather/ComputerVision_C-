#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "1_load_images_videos_webcam.h"


// Function to display an image from a file.
void loadDisplayImage(const std::string& imagePath) {
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
    if (!image.empty()) {
        cv::imshow("Image", image);
        cv::waitKey(0);
    }
    else {
        std::cerr << "Error: Cannot display an empty image." << std::endl;
    }
}

// Function to display a video from a file.
void loadDisplayVideo(const std::string& videoPath) {
    cv::VideoCapture video(videoPath);
    if (!video.isOpened()) {
        std::cerr << "Error: Cannot open the video file." << std::endl;
        return;
    }

    // Play the video until it ends or the user presses the "Esc" key.
    while (true) {
        cv::Mat frame;
        video >> frame;
        if (frame.empty()) {
            break;
        }

        cv::imshow("Video", frame);

        if (cv::waitKey(10) == 27) {
            break;
        }
    }
}

// Function to display a video from a webcam.
void displayWebcam(int cameraId) {
    cv::VideoCapture video(cameraId);

    if (!video.isOpened()) {
        std::cerr << "Error: Cannot open the video file." << std::endl;
        return;
    }

    // Display the webcam video until the user presses the "Esc" key.
    while (true) {
        cv::Mat frame;
        video >> frame;
        if (frame.empty()) {
            break;
        }
        cv::imshow("Webcam", frame);

        if (cv::waitKey(10) == 27) {
            break;
        }
    }
}


/**
 * @brief Loads video frames from a given video file into a vector of cv::Mat objects.
 *
 * @param videoPath The path to the video file.
 * @return std::vector<cv::Mat> A vector containing the video frames.
 */
std::vector<cv::Mat> loadVideoFrames(const std::string& videoPath) {
    cv::VideoCapture video(videoPath);

    if (!video.isOpened()) {
        std::cerr << "Error: Cannot open the video file." << std::endl;
        return std::vector<cv::Mat>();
    }

    std::vector<cv::Mat> frames;
    cv::Mat frame;

    while (video.read(frame)) {
        frames.push_back(frame.clone());
    }

    return frames;
}

// display video frames
void displayVideoFrames(const std::vector<cv::Mat>& frames, const std::string& windowName) {
    if (frames.empty()) {
		std::cerr << "Error: Cannot display an empty video." << std::endl;
		return;
	}
    for (const cv::Mat& frame : frames) {
		cv::imshow(windowName, frame);
        if (cv::waitKey(10) == 27) {
			break;
		}
	}
}