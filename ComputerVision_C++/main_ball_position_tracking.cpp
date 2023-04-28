#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "1_load_images_videos_webcam.h"
#include "6_color_detection.h"
#include "9_pose_tracking.h"


int main() {

	std::string ballVideoPath = "Resources/ball.mp4";

	// load video frames
	std::vector<cv::Mat> ballVideoFrames = loadVideoFrames(ballVideoPath);

	//// display video frames
	//displayVideoFrames(ballVideoFrames, "Ball Video");

	// detect the ball using color detection by using just the first frame
	cv::Mat ballFrame = ballVideoFrames[0];

	// resize the frame to half its size
	cv::resize(ballFrame, ballFrame, cv::Size(), 0.5, 0.5);

	// detect the ball using HSV color detection
	// do this when you want to find the HSV color range for the ball
	// comment it out after finding out the lower and upper HSV color range
	/*interactiveHSVColorRangeSelection(ballFrame);*/

	// following values were found using interactiveHSVColorRangeSelection
	cv::Point3f lower(0, 108, 150);		// Hue, Saturation, Value
	cv::Point3f upper(179, 255, 255);	// Hue, Saturation, 

	// generate masked images for all frames based on a given HSV color range
	std::vector<cv::Mat> maskedFrames = generateMaskedImages(ballVideoFrames, lower, upper);

	// iterate over all masked frames to find the ball position and append to a vector
	std::vector<cv::Point2f> ballPositions;

	for (const cv::Mat& maskedFrame : maskedFrames) {

		// find the ball position in the masked frame
		cv::Point2f ballPosition = findObjectPosition(maskedFrame);
		
		// append the ball position to the vector
		ballPositions.push_back(ballPosition);
	}

	// save ball positions to a file
	std::string ballPositionsFilePath = "Resources/ball_positions.txt";
	saveVectorToFile(ballPositions, ballPositionsFilePath);


	return 0;
}

