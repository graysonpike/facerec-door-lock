// Command line utility to capture positive training images using the Camera Module
// Press the space bar to take a picture, or any other key to quit.
// Grayson Pike, 2018

// Correct usage: ./capture_positives <subject_name>
// Positive images for this subject are stored in DIRECTORY/<subject_name>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <sys/stat.h>
#include <cstdio>
#include <ctime>
// Note: OpenCV 3 uses headers labled as 'opencv2'. It's just the way it is.
// https://docs.opencv.org/master/db/dfa/tutorial_transition_guide.html#gsc.tab=0
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "face_detect.hpp"


// Directory in which to store training images
#define DIRECTORY "training/positive/"
// Prefix on image filenames. Image number is appended before saving
#define FILENAME_PREFIX "positive_"


// http://answers.opencv.org/question/29957/highguivideocapture-buffer-introducing-lag/post-id-38217/
// Hack to clear capture buffer. Setting buffer size is not supported with Raspberry Pi Camera
void flush_capture_buffer(cv::VideoCapture& capture) {

	// Begin measuring time
    std::clock_t start_time;
    double duration;

    int i = 0;
    while (i < 15) {
        start_time = std::clock();
        capture.grab();                      
        duration = (std::clock() - start_time) / (double)CLOCKS_PER_SEC;        
        std::cout << "Duration: " << duration << std::endl;
        i++;
    }

}


int main(int argc, char *argv[]) {

	// Accpet command line argument for subject name
	std::string subject_name;
	if(argc != 2) {
		std::cout << "Error: Correct usage: ./capture_positives <subject_name>" << std::endl;
		return 1;
	} else {
		subject_name = argv[1];
	}

	// Matrix for holding the image
	cv::Mat image;

	// Open the default camera
	// If this fails, make sure you've run
	// sudo modprobe bcm2835-v4l2
	// which creates a device for the camera at /dev/video0
	cv::VideoCapture capture(0);
	if(!capture.isOpened()) {
		std::cout << "Failed to open the camera." << std::endl;
		return 1;
	}

	// Create a directory to hold positive images if it doesn't already exist
	if (mkdir((DIRECTORY + subject_name).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) {
	    std::cout << "Error creating directory '" << DIRECTORY << subject_name << "'. Does it already exist?" << std::endl;
	    return(1);
	}

	bool loop = true;
	int image_number = 1;
	while(loop) {

		// Capture an image
		capture >> image;


		// Convert image to greyscale
		cv::cvtColor(image, image, cv::COLOR_RGB2GRAY);

		// Detect coordinates of a face, if any
		std::vector<cv::Rect> face_regions = detect_faces(image);
		if(face_regions.size() != 1) {
			std::cout << "Error: Detected " << face_regions.size() << " faces." << std::endl;
		} else {

			std::cout << "Successfuly found a face. Saving positive image... ";

			// Crop image to only face
			image = image(face_regions[0]);
			// Save cropped image to file
			try {
				// Pad image number with leading zeros
				std::stringstream ss;
				ss << std::setfill('0') << std::setw(3) << image_number;
		        cv::imwrite(DIRECTORY + subject_name + "/" + FILENAME_PREFIX + ss.str() +".pgm", image);
		    }
		    catch (std::runtime_error& ex) {
		    	std::cout << "[FAILED]" << std::endl;
		        fprintf(stderr, "Exception saving image to PGM format: %s\n", ex.what());
		        return 1;
		    }
		    std::cout << "[DONE]" << std::endl;
		    image_number ++;
		}

		std::string input;
		std::cout << "Enter 'q' to quit, or any other key to take another picture: " << std::endl;
		std::cin >> input;
		if(input == "q" || input == "Q") {
			loop = false;
		}
		flush_capture_buffer(capture);
	}

}