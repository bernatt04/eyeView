# eyeView

A C++ computer vision project aimed at figuring out where someone is looking inside a room using two cameras facing opposite directions. One camera faces the user to track their eyes and estimate gaze direction; the second faces outward to capture the room. By calibrating both cameras, transforming between their coordinate systems, and projecting the gaze vector onto the outward feed, the system should be able to pinpoint the gaze target in the scene.

Right now the project is in an early stage and only covers the user-facing side: face detection, eye landmarks, basic pupil localization, and a raw normalized gaze vector from a single webcam.

![eyeView demo](assets/demo.gif)

Eye ROI tracking with Dlib and in-place binary thresholding on the eye region to separate the dark pupil from the sclera.

## Architecture

The target pipeline combines two camera streams into a single gaze point on the scene:

```text
[User-facing camera]  --> face & landmarks --> pupil center & gaze vector --\
                                                                             +--> calibration & coordinate transform --> gaze point on scene
[Scene-facing camera] --> environment frame --------------------------------/
```

Only the front half of the top branch is implemented so far (face detection, eye cropping, and a basic 2D normalized offset in `src/main.cpp`). Camera calibration, coordinate transforms between cameras, and the scene-facing stream are not built yet.

## Current progress

I started with OpenCV Haar cascades to build a simple baseline (documented in [JOURNAL.md](JOURNAL.md)): face and eye detection, grayscale + `equalizeHist`, local-to-global coordinate conversion, and a simple upper-face filter to cut down false positives.

After that I moved to Dlib's HOG frontal face detector and `models/shape_predictor_68_face_landmarks.dat`. What's currently running in `src/main.cpp`:
- Extracts the 6 landmarks for one eye (indices 36-41) to compute the eye center and crop a bounded ROI around it.
- Converts the eye crop to grayscale, applies an inverse binary threshold (`cv::THRESH_BINARY_INV` at `100`), and runs `cv::moments` to estimate the pupil center of mass.
- Computes a normalized offset (`NormX`, `NormY`) between the eye center and pupil center relative to half the ROI width and height, prints it in the terminal, and draws the vector on the frame.

Earlier exercises from this phase (eye centroids, EAR blink detection, and the in-place thresholded eye crop shown in the clip above) are still in `src/main.cpp` as commented-out blocks.

What is still experimental or missing:
- Only one eye (36-41) is tracked in the active loop.
- The threshold is hardcoded to `100`, so lighting changes, shadows, and eyelashes inside the rectangular crop pull the pupil centroid off target pretty easily.
- Raw frame-to-frame coordinates have no smoothing and jitter noticeably.
- EAR blink detection isn't integrated into the gaze loop yet, so blinks produce noisy vectors.
- No camera or gaze calibration, no head-pose handling, no second camera, and no quantitative accuracy tests yet.

## Roadmap

1. Improve pupil detection and clean up the codebase. Mask the eye crop to the 6-point eye polygon instead of a rectangle so eyelashes and eyebrows don't bias `cv::moments`. Replace the fixed `100` threshold with adaptive thresholding (or Otsu) and basic contour filtering, track both eyes, wire EAR blink filtering back in, add temporal smoothing (moving average or Kalman filter), and split `src/main.cpp` into separate modules.
2. Add calibration and evaluate accuracy. Build a calibration routine to map raw eye vectors to known targets, then measure actual pixel and angular error (plus fixation jitter) across different lighting conditions and distances from the camera. Account for head pose so small head movements don't break calibration.
3. Integrate the second camera and scene projection. Capture the outward-facing room camera alongside the eye camera, calibrate intrinsics and the extrinsic transform between the two opposite-facing cameras, and project the estimated gaze ray onto the room frame.

## Technologies

- C++17
- OpenCV 4
- Dlib (HOG face detector and 68-point shape predictor)
- CMake (>= 3.16), BLAS, LAPACK

## Setup

Install CMake (3.16+), a C++17 compiler, OpenCV, and Dlib (linked with BLAS and LAPACK), then build from the repo root:

```bash
cmake -B build
cmake --build build
```

Run from the repository root so `models/shape_predictor_68_face_landmarks.dat` resolves properly:

```bash
./build/eyeView
```

Press `q` to quit.
