#include <iostream>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>

int main() {
  cv::CascadeClassifier faceCascade;

  if (!faceCascade.load("models/haarcascade_frontalface_default.xml")) {
    std::cerr << "error al cargar el modelo";
    return -1;
  }

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

    cv::equalizeHist(grayFrame, grayFrame);

    std::vector<cv::Rect> faces;

    faceCascade.detectMultiScale(grayFrame, faces, 1.1, 4);

    for (size_t i = 0; i < faces.size(); i++) {
      cv::rectangle(frame, faces[i], cv::Scalar(0, 255, 0));
    }

    cv::imshow("Face detection", frame);

    int key = cv::waitKey(1);
    if (key == 'q') {
      break;
    }
  }
  camera.release();
  cv::destroyAllWindows();
  return 0;
}