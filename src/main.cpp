#include <iostream>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>

int main() {
  cv::CascadeClassifier faceCascade;
  cv::CascadeClassifier eyeCascade;

  if (!faceCascade.load("models/haarcascade_frontalface_default.xml")) {
    std::cerr << "error al cargar el modelo";
    return -1;
  }

  if (!eyeCascade.load("models/haarcascade_eye.xml")) {
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
      cv::Mat faceROI = grayFrame(faces[i]);
      std::vector<cv::Rect> eyes;
      eyeCascade.detectMultiScale(faceROI, eyes, 1.1, 3);

      for (size_t j = 0; j < eyes.size(); j++) {
        // point1 will be top left corner of the eye which will be in the faces
        // ROI so we have to calculate the position of the eye inside the
        // position of the face.
        // then we do the same for the bottom right corner.
        cv::Point Point1(faces[i].x + eyes[j].x, faces[i].y + eyes[j].y);
        cv::Point Point2(faces[i].x + eyes[j].x + eyes[j].width,
                         faces[i].y + eyes[j].y + eyes[j].height);
        cv::rectangle(frame, Point1, Point2, cv::Scalar(0, 255, 0));
      }
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