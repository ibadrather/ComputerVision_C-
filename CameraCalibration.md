
# Camera Calibration Documentation
This codebase provides a set of functions to perform camera calibration, corner detection, and image undistortion. The following sections describe each function in detail.
## 1. getImagePathsFromFolder
```cpp
std::vector<std::string> getImagePathsFromFolder(const std::string&amp; folderPath);

```
This function retrieves the file paths of all images in the specified folder. It takes a string `folderPath` as input, which is the path to the folder containing the images. It returns a `std::vector<std::string>` containing the file paths of the images.
## 2. generateWorldCoordinates
```
std::vector<cv::Point3f> generateWorldCoordinates(const int checkerboardSize[2]);

```
This function generates the world coordinates for 3D points on the checkerboard. It takes an array `checkerboardSize` with two integers representing the number of columns and rows on the checkerboard. It returns a `std::vector<cv::Point3f>` containing the 3D coordinates of the checkerboard corners in the world coordinate system.
## 3. detectCorners
```
std::vector<std::vector<cv::Point2f>> detectCorners(const std::vector<std::string>&amp; fileNames, const cv::Size&amp; patternSize, const int checkerboardDimensions[2], std::vector<std::vector<cv::Point3f>>&amp; Q, bool displayDetectedPoints=false);

```
This function detects the checkerboard corners in the 2D image plane. It takes the following inputs:
* `fileNames`: A `std::vector<std::string>` containing the file paths of the images to process.* `patternSize`: A `cv::Size` object representing the number of internal corners along the width and height of the checkerboard.* `checkerboardDimensions`: An array with two integers representing the number of columns and rows on the checkerboard.* `Q`: A reference to a `std::vector<std::vector<cv::Point3f>>` where the function will store the world coordinates of the detected corners.* `displayDetectedPoints` (optional): A boolean flag indicating whether to display the detected corners on the input images. The default value is `false`.The function returns a `std::vector<std::vector<cv::Point2f>>` containing the detected 2D image coordinates of the checkerboard corners.
## 4. calibrateCameraAndComputeErrors
```
float calibrateCameraAndComputeErrors(const std::vector<std::vector<cv::Point3f>>&amp; Q, const std::vector<std::vector<cv::Point2f>>&amp; q, const cv::Size&amp; frameSize, cv::Matx33f&amp; K, cv::Vec<float, 5>&amp; k);

```
This function calibrates the camera and computes the reprojection error. It takes the following inputs:
* `Q`: A `std::vector<std::vector<cv::Point3f>>` containing the world coordinates of the checkerboard corners.* `q`: A `std::vector<std::vector<cv::Point2f>>` containing the 2D image coordinates of the checkerboard corners.* `frameSize`: A `cv::Size` object representing the dimensions of the image frame.The function also takes the following output parameters:
* `K`: A reference to a `cv::Matx33f` where the function will store the intrinsic camera matrix.* `k`: A reference to a `cv::Vec<float, 5>` where the function will store the distortion coefficients.The function returns a float representing the reprojection error.
## 5. undistortImages
```
void undistort

```

## 5. undistortImages
```
void undistortImages(const std::vector<std::string>&amp; fileNames, const cv::Mat&amp; mapX, const cv::Mat&amp; mapY);

```
This function undistorts the input images using the provided undistortion maps. It takes the following inputs:
* `fileNames`: A `std::vector<std::string>` containing the file paths of the images to undistort.* `mapX`: A `cv::Mat` containing the x-coordinate undistortion map.* `mapY`: A `cv::Mat` containing the y-coordinate undistortion map.This function does not return any value.
## 6. initUndistortMaps
```
void initUndistortMaps(const cv::Matx33f&amp; K, const cv::Vec<float, 5>&amp; k, const cv::Size&amp; frameSize, cv::Mat&amp; mapX, cv::Mat&amp; mapY);

```
This function initializes the undistortion maps for a given camera calibration. It takes the following inputs:
* `K`: A `cv::Matx33f` representing the intrinsic camera matrix.* `k`: A `cv::Vec<float, 5>` representing the distortion coefficients.* `frameSize`: A `cv::Size` object representing the dimensions of the image frame.The function also takes the following output parameters:
* `mapX`: A reference to a `cv::Mat` where the function will store the x-coordinate undistortion map.* `mapY`: A reference to a `cv::Mat` where the function will store the y-coordinate undistortion map.This function does not return any value.
## 7. saveCameraCalibration
```
bool saveCameraCalibration(const std::string&amp; filename, const cv::Matx33f&amp; K, const cv::Vec<float, 5>&amp; k, const cv::Size&amp; frameSize);

```
This function saves the camera calibration data to a file. It takes the following inputs:
* `filename`: A `std::string` representing the name of the file where the camera calibration data will be saved.* `K`: A `cv::Matx33f` representing the intrinsic camera matrix.* `k`: A `cv::Vec<float, 5>` representing the distortion coefficients.* `frameSize`: A `cv::Size` object representing the dimensions of the image frame.The function returns a boolean value indicating the success of the save operation. It returns `true` if the save is successful, and `false` otherwise.


 --------


# Camera Calibration Output Explanation

This document explains each component of the camera calibration output.

## 1. Intrinsic Camera Matrix (K)

The intrinsic camera matrix, denoted by `K`, is a 3x3 matrix that describes the internal camera geometry and optical properties. It has the following format:

[fx, 0, cx;

0, fy, cy;

0, 0, 1]


- `fx` and `fy` are the focal lengths in the x and y directions, respectively, expressed in pixel units. They represent the scaling factor between the camera coordinates and the image coordinates. In your output, `fx` = `fy` = 1187.2505, meaning that the camera has the same focal length in both x and y directions. The value indicates that the camera is fairly zoomed in.

- `cx` and `cy` are the principal point coordinates, which represent the point where the optical axis intersects the image plane. In your output, `cx` = 719.5 and `cy` = 539.5. The principal point is approximately at the center of the image, as you would expect for most cameras.

## 2. Distortion Coefficients (k)

The distortion coefficients are a set of parameters that account for the radial and tangential distortion of the camera lens. In your output, you have 5 distortion coefficients represented by a vector:


[-0.231531, 0.0790088, 0, 0, 0]


- The first two coefficients, k1 = -0.231531 and k2 = 0.0790088, are radial distortion coefficients. Radial distortion causes straight lines in the world to appear curved in the image. The negative k1 value indicates that the image has a barrel distortion, causing the image to appear "bulging" outwards.

- The third and fourth coefficients, p1 = 0 and p2 = 0, are tangential distortion coefficients. Tangential distortion occurs when the lens is not perfectly aligned with the image plane, causing some areas of the image to appear shifted. In your case, these coefficients are 0, meaning that there's no significant tangential distortion.

- The fifth coefficient, k3 = 0, is an additional radial distortion coefficient that accounts for more complex distortion effects. In your case, it is set to 0, meaning that the distortion can be adequately modeled using just k1 and k2.

## 3. Frame Size

The frame size denotes the dimensions of the image captured by the camera. In your output, the frame size is [1440 x 1080], which means the image is 1440 pixels wide and 1080 pixels tall. This is a common aspect ratio for video and images, and it is slightly smaller than Full HD resolution (1920x1080).
