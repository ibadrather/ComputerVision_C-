#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "1_load_images_videos_webcam.h"
#include "2_basic_functions.h"
#include "3_resize_crop.h"
#include "4_draw_write.h"
#include "5_warping.h"
#include "6_color_detection.h"
#include "7_shape_contour_detection.h"


int main() {
    
    // 1. ############## Load and Display ###################
    
    //// Load and display an image
    //const std::string imagePath = "Resources/sunset.jpeg";
    //loadDisplayImage(imagePath);

    //// Load and display a video
    //const std::string videoPath = "Resources/countdown.mp4";
    //loadDisplayVideo(videoPath);

    //// Display webcam
    //const int cameraId = 0;
    //displayWebcam(cameraId);

    // 2. ############# Basic Image Processing #####################
    //const std::string imagePath = "Resources/sunset.jpeg";
    //
    //// load color image as BGR
    //cv::Mat bgr_image = loadBGRImage(imagePath);

    //// convert an image to grayscale
    //cv::Mat gray_image = convertToGrayscale(bgr_image);

    //// blur the grayscale image
    //cv::Size kernelSize(5, 5);
    //cv::Mat blurred_image = applyGaussianBlur(gray_image, kernelSize, 0);

    //// apply canny edge detection on grayscale image
    //cv::Mat canny_image = applyCannyEdgeDetection(gray_image, 50, 100);


    //// dialate
    //cv::Mat dialate_image = applyDialate(canny_image, 5);

    //// erode
    //cv::Mat erode_image = applyErode(canny_image, 1);

    //// display the images
    //displayImage(bgr_image, "BGR Image");
    //displayImage(gray_image, "Grayscale Image");
    //displayImage(blurred_image, "Blurred Image");
    //displayImage(canny_image, "Canny Image");
    //displayImage(dialate_image, "Dialate Image");
    //displayImage(erode_image, "Erode Image");

    // 3. ############### Size Manipulation ################

    //std::string imagePath = "Resources/sunset.jpeg";
    //
    //// load color image as BGR
    //cv::Mat bgr_image = loadBGRImage(imagePath);

    //// resize image
    //cv::Size newSize(512, 512);
    //cv::Mat resized_image = resizeImage(bgr_image, newSize);

    //// scale image
    //double scaleX = 0.5;
    //double scaleY = 0.5;
    //cv::Mat scaled_image = scaleImage(bgr_image, scaleX, scaleY);

    //// crop image
    //cv::Rect roi(100, 100, 300, 300);   // Region of interest; x, y, width, height
    //cv::Mat cropped_image = cropImage(bgr_image, roi);

    //// display the images
    //displayImage(bgr_image, "Original Image");
    //displayImage(resized_image, "Resized Image");
    //displayImage(scaled_image, "Scaled Image");
    //displayImage(cropped_image, "Cropped Image");

    // 4. ############### Drawing ################

    //// create blank image
    //cv::Mat blank_image = createImage(512, 512, cv::Scalar(255, 255, 255));

    //// draw a cicrle on the blank image
    //cv::Point center(256, 256);
    //int radius = 100;
    //cv::Mat circle_image = drawCircleOnImage(blank_image, center, radius, cv::Scalar(255, 0, 255), cv::LineTypes::FILLED);

    //// draw a rectangle on the circle image
    //cv::Point topLeft(100, 100);
    //cv::Point bottomRight(400, 400);
    //cv::Mat rectangle_image = drawRectangleOnImage(circle_image, topLeft, bottomRight, cv::Scalar(0, 100, 0), cv::LineTypes::FILLED);

    //// draw a line on the rectangle image
    //cv::Point start(100, 100);
    //cv::Point end(400, 400);
    //cv::Mat line_image = drawLineOnImage(rectangle_image, start, end, cv::Scalar(0, 0, 255), 5);

    //// put text on the line image
    //std::string text = "Computer Vision with C++";
    //cv::Point origin(100, 90);
    //cv::Mat text_image = drawTextOnImage(line_image, text, origin, cv::FONT_HERSHEY_COMPLEX, 0.65, cv::Scalar(0, 0, 0), 1);


    //// display the images
    //displayImage(blank_image, "Blank Image");
    //displayImage(circle_image, "Circle Image");
    //displayImage(rectangle_image, "Rectangle Circle Image");
    //displayImage(line_image, "Line Rectangle Circle Image");
    //displayImage(text_image, "Text Line Rectangle Circle Image");

    // 5. ############### Image Warping ################
    
    //std::string imagePath = "Resources/cards.png";
    //cv::Mat cardImage = loadBGRImage(imagePath);

    //// Sequence of points should be top-left, top-right, bottom-left, bottom-right

    //// define the 4 points of the original image
    //std::vector<cv::Point2f> originalPoints;
    //originalPoints.push_back(cv::Point2f(432, 105));
    //originalPoints.push_back(cv::Point2f(635, 145));
    //originalPoints.push_back(cv::Point2f(330, 320));
    //originalPoints.push_back(cv::Point2f(554, 371));

    //// warp image
    //cv::Mat warpedImage = warpImage(cardImage, originalPoints, 200, 200);

    //// display the images
    //displayImage(cardImage, "Card Image");
    //displayImage(warpedImage, "Warped Image");


    // 6. ################# Color Detection #######################################
    
    //std::string imagePath = "Resources/lambo.png";
    //std::string imagePath = "Resources/shapes.png";
    //cv::Mat bgrImage = loadBGRImage(imagePath);

    //// hsv color selection
    //interactiveHSVColorRangeSelection(bgrImage);

    // 7. ################# Contours #######################################
    
    std::string imagePath = "Resources/shapes.png";

    // load color image as BGR
    cv::Mat bgrImage = loadBGRImage(imagePath);

    // preprocessed image for contour detection
    cv::Mat preprocessedImage = preprocessImageForContourDetection(bgrImage, 50, 100, 3, 1);

    // find and draw contours on the original image
    cv::Mat countouredImage = findAndDrawContours(preprocessedImage, bgrImage);

    // contoured processed image
    cv::Mat countouredProcessedImage = findAndDrawContours(preprocessedImage, preprocessedImage);

    // display the image
    cv::imshow("Original Image 4", bgrImage);
    cv::imshow("Preprocessed Image", preprocessedImage);
    cv::imshow("Countoured Original Image", countouredImage);
    cv::imshow("Countoured Preprocessed Image", countouredProcessedImage);
    cv::waitKey(0);
    

    return 0;
    }