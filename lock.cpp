// Grayson Pike, 2018

// Facial Recognition Lock Software (Main program)


#include <iostream>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/face.hpp>
#include <opencv2/imgcodecs.hpp>

#include "face_detect.hpp"
#include "hardware.hpp"
#include "config.hpp"


int main(int argc, char *argv[]) {

	// Accpet command line argument for model name
	std::string model_name;
	if (argc != 2) {
		std::cout << "Error: Correct usage: ./lock <model_name>" << std::endl;
		return 1;
	} else {
		model_name = argv[1];
	}

	// Load model
	std::cout << "Loading model..." << std::flush;
	cv::Ptr<cv::face::FaceRecognizer> model = cv::face::LBPHFaceRecognizer::create();
	model->read(std::string(MODEL_DIR) + model_name + ".xml");
	std::cout << "[DONE]" << std::endl;

	// Open the default camera
	// If this fails, make sure you've run
	// sudo modprobe bcm2835-v4l2
	// which creates a device for the camera at /dev/video0
	cv::VideoCapture capture(0);
	if (!capture.isOpened()) {
		std::cout << "Failed to open the camera." << std::endl;
		return 1;
	}

	// Loop to detect faces
	bool loop = true;
	while (loop) {

		cv::Mat image;

		// Capture an image
		flush_capture_buffer(capture);
		capture >> image;

		// Convert image to greyscale
		cv::cvtColor(image, image, cv::COLOR_RGB2GRAY);

		// Detect coordinates of a face, if any
		std::vector<cv::Rect> face_regions = detect_faces(image);
		std::cout << "Deteced " << face_regions.size() << " faces." << std::endl;

		// TODO: Make this work with more than one face in the picture
		if (face_regions.size() == 1) {

			// Crop image to face, then resize
			image = image(face_regions[0]);
			cv::resize(image, image, cv::Size(FACE_WIDTH, FACE_HEIGHT), 0, 0, cv::INTER_LANCZOS4);

			// Determine if face is allowed
			int label;
			double confidence;
			model->predict(image, label, confidence);

			std::cout << "Results: " << label << ", " << confidence << std::endl;

			if (label != 0 && confidence <= POSITIVE_THRESHOLD) {
				std::cout << "******   Detected allowed face with label: " << label << std::endl;
			}

		}

		std::string input;
		std::cout << "Enter 'q' to quit, or any other key to take another picture: " << std::endl;
		std::cin >> input;
		if (input == "q" || input == "Q") {
			loop = false;
		}

	}

}