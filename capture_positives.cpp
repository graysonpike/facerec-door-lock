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


int main(int argc, char *argv[]) {

    // Accept command line argument for subject name
    std::string subject_name;
    if (argc != 2) {
        std::cout << "Error: Correct usage: ./capture_positives <subject_name>"
                  << std::endl;
        return 1;
    } else {
        subject_name = argv[1];
    }

    // Open the default camera
    // If this fails, make sure you've run
    // sudo modprobe bcm2835-v4l2
    // ^ PLACE THIS IN YOUR ~/.bash_profile
    // which creates a device for the camera at /dev/video0
    cv::VideoCapture capture(0);
    if (!capture.isOpened()) {
        std::cout << "Failed to open the camera." << std::endl;
        return 1;
    }

    // Create a directory to hold positive images if it doesn't already exist
    if (!create_directory(DIRECTORY + subject_name)) {
        // Failed to create directory, exit
        return 1;
    }

    cv::Mat image;
    bool loop = true;
    int image_number = 1;

    while (loop) {
        
        // Capture an image
        flush_capture_buffer(capture);
        capture >> image;

        // Convert image to grayscale
        cv::cvtColor(image, image, cv::COLOR_RGB2GRAY);

        // Detect coordinates of a face, if any
        std::vector<cv::Rect> face_regions = detect_faces(image);

        // If only one face was found, perform recognition on it
        if (face_regions.size() != 1) {

            std::cout << "Error: Detected " << face_regions.size() << " faces."
                      << std::endl;

        } else {

            std::cout << "Successfuly found a face. Saving positive image... "
                      << std::flush;

            // Crop image to only face
            image = image(face_regions[0]);

            // Save cropped image to file
            try {
                // Pad image number with leading zeros (for the filename)
                std::stringstream ss;
                ss << std::setfill('0') << std::setw(3) << image_number;
                cv::imwrite(DIRECTORY + subject_name + "/" + FILENAME_PREFIX + ss.str() + ".pgm", image);
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
        if (input == "q" || input == "Q") {
            loop = false;
        }

    }
}
