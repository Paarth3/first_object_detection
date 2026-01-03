#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

int main() {
    
    cv::VideoCapture cap(0);
    
    if (!cap.isOpened()) {
        std::cerr << "\nError: Could not open the camera!" << std::endl;
        return 1;
    }
    
    std::cout << "Camera opened! Press 'q' to quit." << std::endl;
    
    int threshold = 45;
    cv::namedWindow("Binary");
    cv::createTrackbar("Threshold", "Binary", &threshold, 255);

    while (true) {
        cv::Mat frame;
        cap >> frame;
        if(frame.empty()) break;

        cv::Mat gray_frame;
        cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);

        cv::Mat binary_frame;
        cv::threshold(gray_frame, binary_frame, threshold, 255, cv::THRESH_BINARY_INV);

        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hirarchy;

        cv::findContours(binary_frame, contours, hirarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        for (int i = 0; i < contours.size(); i++) {
            double area = cv::contourArea(contours[i]);

            if (area > 2400) {
                cv::Rect box = cv::boundingRect(contours[i]);
                cv::rectangle(frame, box, cv::Scalar(0, 255, 0), 2);
                // cv::drawContours(frame, contours, i, cv::Scalar(0, 0, 255), 2);
            }
        }

        cv::imshow("Binary", binary_frame);
        cv::imshow("Object Detection", frame);

        char key = (char)cv::waitKey(30);
        if (key == 'q' || key == 27) {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}