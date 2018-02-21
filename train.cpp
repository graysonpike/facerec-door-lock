// Grayson Pike, 2018

// Program to train OpenCV facial recognition model with positive and negative training images

#include <iostream>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/face.hpp>

#include "files.hpp"
#include "config.hpp"

#define TRAINING_DIR "training/"
#define MODEL_DIR "complete_models/"

// Size (in pixels) to resize images for training and prediction
// Don't change this unless you also change the size of the training images
#define FACE_WIDTH  92
#define FACE_HEIGHT 112


int main(int argc, char *argv[]) {

	// Accpet command line argument for model name
	std::string model_name;
	if (argc != 2) {
		std::cout << "Error: Correct usage: ./train <model_name>" << std::endl;
		return 1;
	} else {
		model_name = argv[1];
	}

	// Integer labels for positive subjects (0 for negative subjects)
	std::vector<int> labels;
	// All training images to be used. Order corresponds with label vector
	std::vector<cv::Mat> training_images;

	// Load positive training images
	std::vector<std::string> directories = get_directories(std::string(TRAINING_DIR) + "positive/");
	std::cout << "Loading positive training images for subjects:" << std::endl;
	for (int i = 0; i < directories.size(); i++) {
		std::cout << "\t" << directories[i] << " subject (" << i + 1 << ") ... ";
		std::vector<std::string> image_files = get_files(std::string(TRAINING_DIR) + "positive/" + directories[i]);
		for (int j = 0; j < image_files.size(); j++) {
			training_images.push_back(cv::imread(std::string(TRAINING_DIR) + "positive/" + directories[i] + "/" + image_files[j], cv::IMREAD_GRAYSCALE));
			labels.push_back(i + 1);
		}
		std::cout << "[DONE]" << std::endl;
	}

	// Load negative training images
	std::cout << "Loading negative training images for subjects ... ";
	directories = get_directories(std::string(TRAINING_DIR) + "negative/");
	for (int i = 0; i < directories.size(); i++) {
		std::vector<std::string> image_files = get_files(std::string(TRAINING_DIR) + "negative/" + directories[i]);
		for (int j = 0; j < image_files.size(); j++) {
			training_images.push_back(cv::imread(std::string(TRAINING_DIR) + "negative/" + directories[i] + "/" + image_files[j], cv::IMREAD_GRAYSCALE));
			labels.push_back(0);
		}
	}
	std::cout << "[DONE]" << std::endl;

	// Prepare images for training
	std::cout << "Preparing images for training... ";
	for (int i = 0; i < training_images.size(); i++) {
		// Resize images to match negative training images
		// Uses Lanczos resampling to preserve edges and features
		cv::resize(training_images[i], training_images[i], cv::Size(FACE_WIDTH, FACE_HEIGHT), 0, 0, cv::INTER_LANCZOS4);
	}
	std::cout << "[DONE]" << std::endl;

	// Train model
	std::cout << "Training model with " << training_images.size() << " faces ..." << std::flush;
	cv::Ptr<cv::face::FaceRecognizer> model = cv::face::LBPHFaceRecognizer::create();
	model->train(training_images, labels);
	std::cout << "[DONE]" << std::endl;

	// Test Prediction
	int label;
	double confidence;
	model->predict(training_images[0], label, confidence);
	std::cout << "Results: " << label << ", " << confidence << std::endl;

	// Save model
	model->write(std::string(MODEL_DIR) + model_name + ".xml");

}