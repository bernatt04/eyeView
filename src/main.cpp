#include <dlib/geometry/rectangle.h>
#include <dlib/image_processing/full_object_detection.h>
#include <dlib/image_processing/shape_predictor.h>
#include <dlib/opencv/cv_image.h>
#include <dlib/pixel.h>
#include <dlib/serialize.h>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/opencv.h>
#include <opencv2/videoio.hpp>
#include <vector>
/*
int main() {
  dlib::frontal_face_detector face_detector = dlib::get_frontal_face_detector();
  dlib::shape_predictor facePredictor;

  try {
    dlib::deserialize("models/shape_predictor_68_face_landmarks.dat") >>
        facePredictor;
  } catch (const dlib::serialization_error &e) {
    std::cerr << "error when opening the model";
    return -1;
  }

  cv::VideoCapture camera(0);

  if (!camera.isOpened()) {
    return -1;
  }

  cv::Mat frame;

  while (true) {
    camera >> frame;

    if (frame.empty()) {
      break;
    }
    // make the opencv legible for dlib
    dlib::cv_image<dlib::bgr_pixel> dlibFrame(frame);

    std::vector<dlib::rectangle> faces = face_detector(dlibFrame);

    for (size_t i = 0; i < faces.size(); i++) {
      dlib::full_object_detection shape = facePredictor(dlibFrame, faces[i]);

      for (unsigned long k = 0; k < shape.num_parts(); k++) {
        cv::Point p(shape.part(k).x(), shape.part(k).y());
        cv::circle(frame, p, 2, cv::Scalar(0, 255, 0), -1);
      }
    }
    cv::imshow("webcam", frame);
    int key = cv::waitKey(1);
    if (key == 'q') {
      break;
    }
  }

  camera.release();
  cv::destroyAllWindows();
  return 0;
}

*/
/*
int main() {
  dlib::frontal_face_detector face_detector = dlib::get_frontal_face_detector();
  dlib::shape_predictor facePredictor;

  try {
    dlib::deserialize("models/shape_predictor_68_face_landmarks.dat") >>
        facePredictor;
  } catch (const dlib::serialization_error se) {
    return -1;
  }

  cv::VideoCapture camera(0);

  if (!camera.isOpened()) {
    return -1;
  }

  cv::Mat frame;

  while (true) {
    camera >> frame;

    if (frame.empty()) {
      break;
    }

    dlib::cv_image<dlib::bgr_pixel> dlibFrame(frame);
    std::vector<dlib::rectangle> faces = face_detector(dlibFrame);

    for (int i = 0; i < faces.size(); i++) {
      dlib::full_object_detection shape = facePredictor(dlibFrame, faces[i]);

      for (int j = 0; j < shape.num_parts(); j++) {
        cv::Point p(shape.part(j).x(), shape.part(j).y());
        cv::circle(frame, p, 3, cv::Scalar(0, 255, 0));
      }
    }
    cv::imshow("Webcam", frame);
    int key = cv::waitKey(1);
    if (key == 'q') {
      break;
    }
  }
  cv::destroyAllWindows();
  camera.release();
  return 0;
}


*/

// exercise 1: Biometric Centroids (The Sniper): Calculate the centroid (average
// X and Y) of the 6 points for the left eye (indices 36-41) and right eye
// (indices 42-47). Draw a single red dot at both calculated centers.
int main() {
  dlib::frontal_face_detector faceDetector = dlib::get_frontal_face_detector();
  dlib::shape_predictor face_predictor;

  try {
    dlib::deserialize("models/shape_predictor_68_face_landmarks.dat") >>
        face_predictor;
  } catch (const dlib::serialization_error se) {
    return -1;
  }

  cv::VideoCapture camera(0);
  if (!camera.isOpened()) {
    return -1;
  }

  cv::Mat frame;

  while (true) {
    camera >> frame;

    if (frame.empty()) {
      break;
    }

    dlib::cv_image<dlib::bgr_pixel> dlibFrame(frame);
    std::vector<dlib::rectangle> faces = faceDetector(dlibFrame);

    for (int i = 0; i < faces.size(); i++) {
      dlib::full_object_detection shape = face_predictor(dlibFrame, faces[i]);

      for (int j = 0; j < shape.num_parts(); j++) {
        if (j >= 36 && j <= 41 || j >= 42 && j <= 47) {
          cv::Point p(shape.part(j).x(), shape.part(j).y());
          cv::circle(frame, p, 3, cv::Scalar(0, 255, 0));
        }
      }
    }
    cv::imshow("Webcam", frame);
    int key = cv::waitKey(1);
    if (key == 'q') {
      break;
    }
  }
  cv::destroyAllWindows();
  camera.release();
  return 0;
}