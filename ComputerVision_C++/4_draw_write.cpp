#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "4_draw_write.h"

/**
 * Creates an image of the specified dimensions and color.
 *
 * @param width The width of the image.
 * @param height The height of the image.
 * @param color The color of the image.
 * @return The created image.
 */
cv::Mat createImage(int width, int height, cv::Scalar color) {
    cv::Mat image(height, width, CV_8UC3, color);
    return image;
}

/**
 * Draws a line on the input image.
 *
 * @param inputImage The image on which to draw the line.
 * @param start The starting point of the line.
 * @param end The ending point of the line.
 * @param color The color of the line.
 * @param thickness The thickness of the line.
 * @return The output image with the line drawn.
 */
cv::Mat drawLineOnImage(cv::Mat& inputImage, cv::Point start, cv::Point end, cv::Scalar color, int thickness) {
    cv::Mat outputImage = inputImage.clone();
    cv::line(outputImage, start, end, color, thickness);
    return outputImage;
}

/**
 * Draws a rectangle on the input image.
 *
 * @param inputImage The image on which to draw the rectangle.
 * @param topLeft The top-left corner of the rectangle.
 * @param bottomRight The bottom-right corner of the rectangle.
 * @param color The color of the rectangle.
 * @param thickness The thickness of the rectangle.
 * @return The output image with the rectangle drawn.
 */
cv::Mat drawRectangleOnImage(cv::Mat& inputImage, cv::Point topLeft, cv::Point bottomRight, cv::Scalar color, int thickness) {
    cv::Mat outputImage = inputImage.clone();
    cv::rectangle(outputImage, topLeft, bottomRight, color, thickness);
    return outputImage;
}

/**
 * Draws a circle on the input image.
 *
 * @param inputImage The image on which to draw the circle.
 * @param center The center of the circle.
 * @param radius The radius of the circle.
 * @param color The color of the circle.
 * @param thickness The thickness of the circle.
 * @return The output image with the circle drawn.
 */
cv::Mat drawCircleOnImage(cv::Mat& inputImage, cv::Point center, int radius, cv::Scalar color, int thickness) {
    cv::Mat outputImage = inputImage.clone();
    cv::circle(outputImage, center, radius, color, thickness);
    return outputImage;
}

/**
 * Adds text to the input image.
 *
 * @param inputImage The image on which to put the text.
 * @param text The text to be added to the image.
 * @param origin The starting point of the text.
 * @param fontFace The font type.
 * @param fontScale The font scale factor.
 * @param color The color of the text.
 * @param thickness The thickness of the text.
 * @return The output image with the text added.
 */
cv::Mat drawTextOnImage(cv::Mat& inputImage, const std::string& text, const cv::Point& origin, int fontFace, double fontScale, const cv::Scalar& color, int thickness) {
    cv::Mat outputImage = inputImage.clone();
    cv::putText(outputImage, text, origin, fontFace, fontScale, color, thickness);
    return outputImage;
}
