# Phase 1: Haar Cascades & Basics

Finished the initial phase of the project using OpenCV with classic Haar Cascades before moving on to Dlib and facial landmarks.

Key things implemented and learned:

1. Face & Eye Detection:
Used frontalface and eye haar cascades. Frames are converted to grayscale and equalized with equalizeHist so lighting changes don't mess up the detection. Instead of scanning the entire frame for eyes, we first detect the face and only search for eyes inside that face ROI.

2. Coordinate Systems (Local to Global):
Since eyes are detected inside the face crop, their coordinates are relative to the top-left of the face rectangle (0,0). To draw the rectangles or pupil points on the actual window, we have to translate them back to global coordinates by adding the face offset (face.x + eye.x, face.y + eye.y).

3. Filtering False Positives:
Haar cascades are pretty noisy and often confuse nostrils or mouth corners with eyes. Solved this with a simple anatomical filter: anything detected below the top half of the face (y > face.height / 2) is discarded.

4. In-place Memory with ROIs:
In OpenCV, creating a sub-matrix like frame(faceRect) doesn't copy pixel data, it just points to the same memory buffer. Applying cv::GaussianBlur to this ROI censors the face directly on the original frame in real time without any extra memory allocations.
