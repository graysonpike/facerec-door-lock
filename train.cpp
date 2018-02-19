// Program to train OpenCV facial recognition model with positive and negative training images
// Grayson Pike, 2018

#include <iostream>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include "files.hpp"

#define TRAINING_DIR "training/"


void prepare_image(cv::Mat &image) {

}


int main() {

	// Load positive training images
	std::vector<cv::Mat> positive_images;
	std::vector<std::string> directories = get_directories(std::string(TRAINING_DIR) + "positive/");
	std::cout << "Loading positive training images for subjects:" << std::endl;
	for(int i = 0; i < directories.size(); i++) {
		std::cout << "\t" << directories[i] << " ... ";
		std::vector<std::string> image_files = get_files(std::string(TRAINING_DIR) + "positive/" + directories[i]);
		for(int j = 0; j < image_files.size(); j++) {
			positive_images.push_back(cv::imread(std::string(TRAINING_DIR) + "positive/" + directories[i] + "/" + image_files[j]));
		}
		std::cout << "[DONE]" << std::endl;
	}

	// Load negative training images
	std::vector<cv::Mat> negative_images;
	std::cout << "Loading negative training images for subjects ... ";
	std::vector<std::string> image_files = get_files(std::string(TRAINING_DIR) + "positive");
	for(int j = 0; j < image_files.size(); j++) {
		negative_images.push_back(cv::imread(std::string(TRAINING_DIR) + "negative/" + image_files[j]));
	}
	std::cout << "[DONE]" << std::endl;



}