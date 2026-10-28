#include <dlib/geometry/rectangle.h>
#include <dlib/image_processing/full_object_detection.h>
#include <dlib/image_processing/shape_predictor.h>
#include <dlib/misc_api/misc_api_kernel_1.h>
#include <dlib/opencv/cv_image.h>
#include <dlib/pixel.h>
#include <dlib/serialize.h>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
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
/*
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

*/

// Blink Detector (EAR Formula): Implement the Eye Aspect Ratio (EAR) using
// Euclidean distances between the eye landmarks. Print "BLINK" to the console
// when the value drops below a certain threshold.

// EAR = (|p2-p6|+ |p3-p5|)/2.0*|p1-p4|
/*
int main() {
  dlib::frontal_face_detector faceDetector = dlib::get_frontal_face_detector();
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
    std::vector<dlib::rectangle> faces = faceDetector(dlibFrame);
    for (int i = 0; i < faces.size(); i++) {
      dlib::full_object_detection shape = facePredictor(dlibFrame, faces[i]);
      for (int j = 0; j < shape.num_parts(); j++) {
        if (j >= 36 && j <= 41 || j >= 42 && j <= 47) {
          cv::Point p(shape.part(j).x(), shape.part(j).y());
          cv::circle(frame, p, 3, cv::Scalar(0, 255, 0));
        }
      }
      if ((abs(shape.part(37).y() - shape.part(41).y()) +
           abs(shape.part(38).y() - shape.part(40).y())) /
              (2.0 * abs(shape.part(36).x() - shape.part(39).x())) <
          0.2) {
        std::cout << "Blink RIGHT\n";
      }
      if ((abs(shape.part(43).y() - shape.part(47).y()) +
           abs(shape.part(44).y() - shape.part(46).y())) /
              (2.0 * abs(shape.part(42).x() - shape.part(45).x())) <
          0.2) {
        std::cout << "Blink LEFT\n";
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

// Dynamic ROI Extraction (The Surgeon): Find the minimum and maximum X and Y
// coordinates of the right eye to define a cv::Rect. Extract this region and
// display it in a separate cv::imshow window.
/*
int main() {
  dlib::frontal_face_detector faceDetector = dlib::get_frontal_face_detector();
  dlib::shape_predictor shapePredictor;

  try {
    dlib::deserialize("models/shape_predictor_68_face_landmarks.dat") >>
        shapePredictor;
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
      dlib::full_object_detection shape = shapePredictor(dlibFrame, faces[i]);

      for (int j = 0; j < shape.num_parts(); j++) {
        cv::Point p(shape.part(j).x(), shape.part(j).y());
        cv::circle(frame, p, 3, cv::Scalar(0, 255, 0));
      }

      int Xmin = shape.part(36).x();
      int Ymin = shape.part(36).y();
      int Xmax = shape.part(36).x();
      int Ymax = shape.part(36).y();
      for (int k = 37; k < 42; k++) {
        if (Xmin > shape.part(k).x()) {
          Xmin = shape.part(k).x();
        }
        if (Ymin > shape.part(k).y()) {
          Ymin = shape.part(k).y();
        }
        if (Xmax < shape.part(k).x()) {
          Xmax = shape.part(k).x();
        }
        if (Ymax < shape.part(k).y()) {
          Ymax = shape.part(k).y();
        }
      }
      cv::Rect r(Xmin, Ymin, (Xmax - Xmin), (Ymax - Ymin));
      cv::rectangle(frame, r, cv::Scalar(0, 255, 0), 1);
      cv::Mat ojo = frame(r);
      cv::imshow("Ojo Aislado", ojo);
      cv::imshow("webcam", frame);
    }

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
// Memory Pointers (The Cyborg): Convert the extracted eye ROI to grayscale and
// apply a strict binary threshold (cv::threshold) to make the pupil solid black
// and the sclera solid white. Overwrite the original color frame so your right
// eye appears as a high-contrast robot eye in the main webcam feed.
/*
int main() {
  dlib::frontal_face_detector faceDetector = dlib::get_frontal_face_detector();
  dlib::shape_predictor shape_predictor;

  try {
    dlib::deserialize("models/shape_predictor_68_face_landmarks.dat") >>
        shape_predictor;
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
      dlib::full_object_detection shape = shape_predictor(dlibFrame, faces[i]);

      int minX = shape.part(36).x();
      int minY = shape.part(36).y();
      int maxX = shape.part(36).x();
      int maxY = shape.part(36).y();
      for (int j = 37; j < 42; j++) {
        if (minX > shape.part(j).x()) {
          minX = shape.part(j).x();
        }
        if (minY > shape.part(j).y()) {
          minY = shape.part(j).y();
        }
        if (maxX < shape.part(j).x()) {
          maxX = shape.part(j).x();
        }
        if (maxY < shape.part(j).y()) {
          maxY = shape.part(j).y();
        }
      }

      cv::Rect r(minX, minY, (maxX - minX), (maxY - minY));
      cv::rectangle(frame, r, cv::Scalar(0, 255, 0), 1);
      cv::Mat ojo = frame(r);
      cv::threshold(ojo, ojo, 100, 255, 0);

      cv::imshow("eye", ojo);
      cv::imshow("webcam", frame);
    }
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

// Gaze Tracking Vector: Use cv::moments on the thresholded ROI to locate the
// exact center of the black pupil mass. Draw a cv::line in the main frame from
// the anatomical center of the eye (from Challenge 1) to the dynamic pupil
// center to track the gaze direction.

int main() {
  dlib::frontal_face_detector faceDetector = dlib::get_frontal_face_detector();
  dlib::shape_predictor shapePredictor;

  try {
    dlib::deserialize("models/shape_predictor_68_face_landmarks.dat") >>
        shapePredictor;
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
      dlib::full_object_detection shape = shapePredictor(dlibFrame, faces[i]);

      int minX = shape.part(36).x();
      int minY = shape.part(36).y();
      int maxX = shape.part(36).x();
      int maxY = shape.part(36).y();

      int sumaX = shape.part(36).x();
      int sumaY = shape.part(36).y();

      for (int j = 37; j < 42; j++) {
        if (minX > shape.part(j).x()) {
          minX = shape.part(j).x();
        }
        if (minY > shape.part(j).y()) {
          minY = shape.part(j).y();
        }
        if (maxX < shape.part(j).x()) {
          maxX = shape.part(j).x();
        }
        if (maxY < shape.part(j).y()) {
          maxY = shape.part(j).y();
        }

        sumaX += shape.part(j).x();
        sumaY += shape.part(j).y();
      }

      cv::Point centroOjo(sumaX / 6, sumaY / 6);

      if (minX < 0 || minY < 0 || maxX >= frame.cols || maxY >= frame.rows ||
          maxX <= minX || maxY <= minY) {
        continue;
      }

      cv::Rect r(minX, minY, maxX - minX, maxY - minY);
      cv::Mat ojo = frame(r);

      cv::Mat gris;
      cv::cvtColor(ojo, gris, cv::COLOR_BGR2GRAY);

      cv::threshold(gris, gris, 100, 255, cv::THRESH_BINARY_INV);

      cv::Moments m = cv::moments(gris, true);

      if (m.m00 > 0) {
        int pupilX = m.m10 / m.m00;
        int pupilY = m.m01 / m.m00;

        cv::Point centroPupila(pupilX + minX, pupilY + minY);

        float normX = centroOjo.x - centroPupila.x;
        float normY = centroOjo.y - centroPupila.y;

        normX = normX / (static_cast<float>(r.width) / 2);
        normY = normY / (static_cast<float>(r.height) / 2);

        std::cout << "\rNormX: " << std::fixed << std::setprecision(3) << normX
                  << " | NormY: " << normY << "    " << std::flush;

        cv::circle(frame, centroOjo, 3, cv::Scalar(255, 0, 0), -1);
        cv::circle(frame, centroPupila, 3, cv::Scalar(0, 0, 255), -1);

        cv::line(frame, centroOjo, centroPupila, cv::Scalar(0, 255, 0), 2);
      }

      cv::rectangle(frame, r, cv::Scalar(0, 255, 0), 1);
      cv::imshow("Ojo", gris);
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
