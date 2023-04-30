To obtain the exact relative position of the cameras during the calibration process, you can perform stereo calibration using a known calibration pattern, such as a chessboard or a circle grid pattern. Stereo calibration estimates the intrinsic parameters for each camera as well as the extrinsic parameters (relative rotation and translation) between the cameras. Here's how you can perform stereo calibration:

1. **Prepare a calibration pattern**: Print a chessboard or circle grid pattern on a flat surface. Ensure that the pattern has a sufficient number of inner corners or circle centers (e.g., 9x6 for chessboard, 4x11 for circle grid) to provide a good distribution of feature points.

2. **Capture stereo calibration images**: Place the calibration pattern in front of the stereo camera setup at various orientations and distances. Make sure to cover a wide range of camera poses to improve the accuracy of the calibration. Capture at least 10-20 pairs of stereo images with the pattern visible in both cameras.

3. **Detect feature points**: For each stereo image pair, detect the feature points (inner corners for chessboard, circle centers for circle grid) using OpenCV functions like cv::findChessboardCorners or cv::findCirclesGrid. Ensure that the detected feature points are accurate and consistent across all image pairs.

Perform stereo calibration: Use the cv::stereoCalibrate function in OpenCV to perform stereo calibration. Provide the detected feature points, object points (3D coordinates of the pattern points in the world coordinate system), and the image size as input. The function returns the intrinsic parameters (camera matrices and distortion coefficients) for both cameras as well as the extrinsic parameters (rotation and translation matrices) between the cameras.

```cpp
#include <opencv2/calib3d.hpp>

cv::Mat cameraMatrix1, cameraMatrix2, distCoeffs1, distCoeffs2, R, T, E, F;
double rms = cv::stereoCalibrate(objectPoints, imagePoints1, imagePoints2,
                                 cameraMatrix1, distCoeffs1,
                                 cameraMatrix2, distCoeffs2,
                                 imageSize, R, T, E, F,
                                 cv::CALIB_FIX_INTRINSIC,
                                 cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 100, 1e-5));
```

After stereo calibration, the extrinsic parameters (R and T) represent the exact relative position of the cameras with respect to each other. The rotation matrix (R) describes the relative orientation, and the translation vector (T) represents the relative position or the baseline distance between the camera centers.

Make sure to use a sufficient number of stereo calibration images and accurate feature points to obtain reliable extrinsic parameters. Additionally, ensure that the cameras remain fixed in their positions after calibration to maintain accurate 3D reconstruction during object tracking.
