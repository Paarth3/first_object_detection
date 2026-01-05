# Real-Time Object Tracking with OpenCV

## Project Overview

This project implements a real-time object detection and tracking system using C++ and the OpenCV library. It captures live video from a webcam, processes the visual data to isolate objects based on contrast, and draws bounding boxes around detected entities.

The application serves as a foundational exploration into computer vision, demonstrating how raw pixel data can be transformed into structured geometric information (contours and coordinates) to track physical objects.

---

## Key Learnings

Building this project provided hands-on experience with the computer vision pipeline and C++ application development:

- **Computer Vision Fundamentals:** Gained a deep understanding of image pre-processing techniques, including **grayscale conversion** and **binary thresholding** to separate regions of interest from the background.
- **Contour Analysis:** Learned how to utilize `cv::findContours` to extract structural data from binary images and `cv::boundingRect` to calculate geometry for object tracking.
- **Noise Reduction:** Implemented area-based filtering (`area > 2400`) to eliminate visual noise and ensure the system only tracks significant objects.
- **UI Integration:** Integrated OpenCV’s HighGUI module to create interactive elements (trackbars), allowing for dynamic runtime calibration of threshold values.
- **Memory Management:** Managed C++ memory resources effectively within the OpenCV matrix (`cv::Mat`) context.

---

## Technical Details

### Technology Stack

- **Language:** C++
- **Library:** OpenCV (Open Source Computer Vision Library)

### Implementation Logic

The application follows a linear processing pipeline for every frame captured:

1. **Capture:** Stream video from the default webcam (`cv::VideoCapture`).
2. **Pre-processing:** Convert the frame to grayscale to reduce computational complexity.
3. **Segmentation:** Apply an **Inverted Binary Threshold**. This isolates darker objects against lighter backgrounds. The threshold intensity is adjustable via a UI trackbar.
4. **Contour Detection:** Identify the borders of the segmented white regions.
5. **Filtering & Rendering:** Iterate through found contours, ignore those below a specific pixel area size to filter noise, and draw a bounding rectangle around valid targets.

---

## How to Run the Project

### Prerequisites & Assumptions

- **OS:** Linux (Ubuntu recommended) or macOS. _Note: Windows requires a different build configuration (Visual Studio/CMake)._
- **Hardware:** A computer with a functional webcam (default index `0`).
- **Software:**
    - C++ Compiler (e.g., `g++`)
    - OpenCV Library installed on your system.

### 1. Install Dependencies (Ubuntu/Debian)

If you do not have OpenCV installed, you can set it up via the terminal or follow the [YouTube tutorial by ProgrammingKnowledge](https://youtu.be/6pABIQl1ZP0?si=0aGEz8nX4xNEFFOb):

```Bash
sudo apt update
sudo apt install libopencv-dev
```

### 2. Compile the Code

Navigate to the directory containing `main.cpp`. You can compile the project using `g++` and `pkg-config` to automatically link the OpenCV libraries:

```Bash
g++ main.cpp -o ObjectTracker `pkg-config --cflags --libs opencv4`
```

### 3. Run the Application

Execute the compiled binary:

```Bash
./ObjectTracker
```

### 4. Usage Instructions

1. **Launch:** When the program starts, two windows will appear:
    - `Object Detection`: Shows the original video with green bounding boxes around tracked objects.
    - `Binary`: Shows the black-and-white mask being used for calculation.
2. **Calibrate:** Use the **"Threshold" trackbar** in the `Binary` window.
    - _Note:_ Since the code uses `THRESH_BINARY_INV`, the system looks for **dark objects** on a **light background**. Adjust the slider until your target object is white and the background is black in the Binary window.
3. **Exit:** Press `q` or `ESC` to close the application.
