// Grayson Pike, 2018

#include "face_detect.hpp"

#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>


/*
	Utility function to detect faces in an image
	Returns a vector of Rects with regions of detected faces in a given image
*/
std::vector<cv::Rect> detect_faces(cv::Mat image) {

	// Create a Haar Cascade Classifier configured for frontal faces
	cv::CascadeClassifier haar_faces_classifier(HAAR_FACES_FILE);

	// Identify all the regions with faces in the image
	std::vector<cv::Rect> face_regions;
	haar_faces_classifier.detectMultiScale(
			image,
			face_regions,
			HAAR_SCALE_FACTOR,
			HAAR_MIN_NEIGHBORS,
			cv::CASCADE_SCALE_IMAGE,
			cv::Size(HAAR_MIN_SIZE_X, HAAR_MIN_SIZE_Y)
		);

	return face_regions;

}