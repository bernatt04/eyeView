#include "opencv2/core/types.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/opencv.hpp>
#include <stdio.h>

int main() {
  cv::VideoCapture camera(0);

  if (!camera.isOpened()) {
    std::cerr << "error when opening the camera";
    return -1;
  }
  cv::Mat frame;
  while (true) {
    camera >> frame;

    if (frame.empty()) {
      std::cerr << "error empty frame";
      break;
    }

    cv::circle(frame, cv::Point(250, 250), 20, cv::Scalar(0, 0, 255));

    cv::imshow("Webcam", frame);

    int key = cv::waitKey(1);
    if (key == 'q') {
      break;
    }
  }

  camera.release();
  cv::destroyAllWindows();
  return 0;
}