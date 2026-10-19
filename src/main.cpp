#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>

int main() {
  cv::VideoCapture camera(0);

  if (!camera.isOpened()) {
    std::cerr << "error when opening the camera";
    return -1;
  }

  cv::Mat frame;
  cv::Mat grayFrame;

  while (true) {
    camera >> frame;
    if (frame.empty()) {
      break;
    }

    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

    int pixelValue = (int)grayFrame.at<uchar>(250, 250);

    std::cout << "El valor del pixel (250,250) es : " << pixelValue
              << std::endl;

    cv::circle(grayFrame, cv::Point(250, 250), 20, cv::Scalar(0, 0, 255));

    cv::imshow("Webcam en Blanco y Negro", grayFrame);

    int key = cv::waitKey(1);
    if (key == 'q') {
      break;
    }
  }
  camera.release();
  cv::destroyAllWindows();
  return 0;
}