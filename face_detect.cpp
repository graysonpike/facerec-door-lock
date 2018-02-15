#include "face_detect.hpp"

#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>

#define HAAR_FACES_FILE "cascades/haarcascade_frontalface_alt.xml"
#define HAAR_SCALE_FACTOR  1.1L
#define HAAR_MIN_NEIGHBORS 4
#define HAAR_MIN_SIZE_X 30
#define HAAR_MIN_SIZE_Y 30

void detect_single_face(cv::Mat image) {

	// Create a Haar Cascade Classifier configured for frontal faces
	cv::CascadeClassifier haar_faces_classifier(HAAR_FACES_FILE);

	// Identify all the regions with faces in the image
	std::vector face_regions;
	haar_faces_classifier.detectMultiScale(
			image,
			&face_regions,

		)

}