#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>

// Avoid using "using namespace" in the global scope, to prevent naming conflicts and ambiguity.
// Instead, use fully qualified names or bring names into scope within a function or class.

class ImageProcessor {
public:
    explicit ImageProcessor(const std::string& imagePath) : m_imagePath(imagePath) {}

    bool loadImage() {
        m_image = cv::imread(m_imagePath, cv::IMREAD_COLOR);
        return !m_image.empty();
    }

    void displayImage() const {
        if (!m_image.empty()) {
            cv::imshow("Image", m_image);
            cv::waitKey(0);
        }
        else {
            std::cerr << "Error: Cannot display an empty image." << std::endl;
        }
    }

private:
    std::string m_imagePath;
    cv::Mat m_image;
};

int main() {
    const std::string path = "C:/Users/ibadr/OneDrive/Pictures/ibad_rather.png";
    ImageProcessor processor(path);

    if (processor.loadImage()) {
        processor.displayImage();
    }
    else {
        std::cerr << "Error: Failed to load image." << std::endl;
    }

    return 0;
}
