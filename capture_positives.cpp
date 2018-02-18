// Command line utility to capture positive training images using the Camera Module
// Press the space bar to take a picture, or any other key to quit

#include <iostream>
// Note: OpenCV 3 uses headers labled as 'opencv2'. It's just the way it is.
// https://docs.opencv.org/master/db/dfa/tutorial_transition_guide.html#gsc.tab=0
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "face_detect.hpp"


// Directory in which to store training images
#define DIRECTORY "training/positive/"
// Prefix on image filenames
#define FILENAME_PREFIX "positive_"


int main() {

	// Matrix for holding the image
	cv::Mat image;

	// Open the default camera
	// If this fails, make sure you've run
	// sudo modprobe bcm2835-v4l2
	// which creates a device for the camera at /dev/video0
	cv::VideoCapture capture(0);
	if(!capture.isOpened()) {
		std::cout << "Failed to open the camera." << std::endl;
		return -1;
	}

	// Capture an image
	capture >> image;

	// Convert image to greyscale
	cv::cvtColor(image, image, cv::COLOR_RGB2GRAY);

	// Detect coordinates of a face, if any
	detect_single_face(image);

	// Save the image to a file
	try {
        cv::imwrite("test.pgm", image);
    }
    catch (std::runtime_error& ex) {
        fprintf(stderr, "Exception saving image to PGM format: %s\n", ex.what());
        return 1;
    }

}