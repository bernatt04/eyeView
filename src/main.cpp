#include <dlib/geometry/rectangle.h>
#include <dlib/image_processing/shape_predictor.h>
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