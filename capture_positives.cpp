// Copyright 2018 Grayson Pike

/*
    Command line utility to capture positive training images for a given
    subject using the Camera Module. When running, enter any key to take
    a picture or 'q' to quit. Positive images for this subject are stored
    in DIRECTORY/<subject_name>

    Correct usage: ./capture_positives <subject_name>
*/

#include <iostream>
#include <iomanip>
#include <sstream>

// Note: OpenCV 3 uses headers labled as 'opencv2'. It's just the way it is.
// https://docs.opencv.org/master/db/dfa/tutorial_transition_guide.html#gsc.tab=0
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "face_detect.hpp"
#include "hardware.hpp"
#include "files.hpp"
#include "config.hpp"


/*
    Returns subject name from command line arguments or exits on failure  
*/
std::string get_subject_name(int argc, char *argv[]) {

    std::string model_name;
    if (argc != 2) {
        std::cout << "Error: Correct usage: ./capture_positives <subject_name>" << std::endl;
        exit(1);
    } else {
        return argv[1];
    }

}


int main(int argc, char *argv[]) {

    std::string subject_name = get_subject_name(argc, argv);

    cv::VideoCapture camera = get_camera();

    // Create a directory to hold positive images if it doesn't already exist
    if (!create_directory(TRAINING_IMAGES_DIR + subject_name)) {
        // Failed to create directory, exit
        exit(1);
    }

    cv::Mat image;
    bool loop = true;
    int image_number = 1;

    while (loop) {
        
        // Capture an image
        flush_capture_buffer(camera);
        camera >> image;

        // Convert image to grayscale
        cv::cvtColor(image, image, cv::COLOR_RGB2GRAY);

        // Detect coordinates of a face, if any
        std::vector<cv::Rect> face_regions = detect_faces(image);

        // If only one face was found, perform recognition on it
        if (face_regions.size() != 1) {

            std::cout << "Error: Detected " << face_regions.size() << " faces." << std::endl;

        } else {

            std::cout << "Successfuly found a face. Saving positive image... " << std::flush;

            // Crop image to only face
            image = image(face_regions[0]);

            // Pad image number with leading zeros (for the filename)
            std::stringstream ss;
            ss << std::setfill('0') << std::setw(3) << image_number;
            if(!save_pgm_image(image, TRAINING_IMAGES_DIR + subject_name + "/" + TRAINING_FILENAME_PREFIX + ss.str() + ".pgm")) {
                exit(1);
            }

            std::cout << "[DONE]" << std::endl;
            image_number ++;

        }

        std::string input;
        std::cout << "Enter 'q' to quit, or any other key to take another picture: " << std::endl;
        std::cin >> input;
        if (input == "q" || input == "Q") {
            loop = false;
        }

    }
}
