#include <iostream>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <stdio.h>
#include <vector>
/*

int main() {
  // load the models
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

  // init the camera
  cv::VideoCapture camera(0);

  if (!camera.isOpened()) {
    std::cerr << "error when opening the camera";
    return -1;
  }

  // declare types of frames we will work with
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

    // first for to locate the face
    for (size_t i = 0; i < faces.size(); i++) {
      cv::Mat faceROI = grayFrame(faces[i]);
      std::vector<cv::Rect> eyes;
      eyeCascade.detectMultiScale(faceROI, eyes, 1.1, 3);

      // second for to locate the eyes inside the face
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


// Exercise 1 locate simulated pupil (center of eye rectangle).
int main() {
  cv::CascadeClassifier facesCascade;
  cv::CascadeClassifier eyesCascade;

  if (!facesCascade.load("models/haarcascade_frontalface_default.xml")) {
    return -1;
  }

  if (!eyesCascade.load("models/haarcascade_eye.xml")) {
    return -1;
  }

  cv::VideoCapture camera(0);

  if (!camera.isOpened()) {
    return -2;
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

    facesCascade.detectMultiScale(grayFrame, faces, 1.05, 9);

    for (int i = 0; i < faces.size(); i++) {
      cv::Mat faceROI = grayFrame(faces[i]);
      std::vector<cv::Rect> eyes;
      eyesCascade.detectMultiScale(faceROI, eyes, 1.1, 3);
      for (int j = 0; j < eyes.size(); j++) {
        cv::Point point1(faces[i].x + eyes[j].x, faces[i].y + eyes[j].y);
        cv::Point point2(faces[i].x + eyes[j].x + eyes[j].width,
                         faces[i].y + eyes[j].y + eyes[j].height);

        cv::circle(frame, (point1 + point2) / 2, 5, cv::Scalar(0, 255, 0));
      }
    }

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


// exercise 2 the model should only detect anatomical features in the top half
// of the face leaving out any "eyes" located in the lower part like mouth nose
// etc errors.

int main() {
  cv::CascadeClassifier faceCascade;
  cv::CascadeClassifier eyeCascade;

  if (!faceCascade.load("models/haarcascade_frontalface_default.xml")) {
    return -1;
  }
  if (!eyeCascade.load("models/haarcascade_eye.xml")) {
    return -1;
  }

  cv::VideoCapture camera(0);

  if (!camera.isOpened()) {
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

    faceCascade.detectMultiScale(grayFrame, faces, 1.1, 3);

    for (int i = 0; i < faces.size(); i++) {
      cv::Mat facesROI = grayFrame(faces[i]);
      std::vector<cv::Rect> eyes;
      eyeCascade.detectMultiScale(facesROI, eyes, 1.1, 3);
      for (int j = 0; j < eyes.size(); j++) {
        if (eyes[j].y <= faces[i].height / 2) {
          cv::Point point1(faces[i].x + eyes[j].x, faces[i].y + eyes[j].y);
          cv::Point point2(faces[i].x + eyes[j].x + eyes[j].width,
                           faces[i].y + eyes[j].y + eyes[j].height);
          cv::circle(frame, (point1 + point2) / 2, 5, cv::Scalar(0, 255, 0));
        }
      }
    }

    cv::imshow("Webcam", frame);
    int key = cv::waitKey(1);
    if (key == 'q')
      break;
  }

  cv::destroyAllWindows();
  camera.release();
  return 0;
}

*/

// exercise 3

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
      cv::Mat faceROI = frame(faces[i]);
      cv::GaussianBlur(faceROI, faceROI, cv::Size(51, 51), 0);
      std::vector<cv::Rect> eyes;
      eyeCascade.detectMultiScale(faceROI, eyes, 1.1, 3);

      for (size_t j = 0; j < eyes.size(); j++) {
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