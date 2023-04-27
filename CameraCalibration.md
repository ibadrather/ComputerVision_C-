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

The frame size denotes the dimensions of the image captured by the camera. In your output, the frame size is [1440 x 1080], which means the image is 1440 pixels wide and 1080 pixels tall. This is a common aspect ratio for video and images, and it is slightly larger than Full HD resolution (1920x1080).
