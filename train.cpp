// Grayson Pike, 2018

/*
    Program to train OpenCV facial recognition model with positive and negative
    training images. Creates a complete model (saved as an XML file) with a given name.
    

    Correct usage: ./train <model_name>
*/

#include <iostream>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/face.hpp>

#include "files.hpp"
#include "config.hpp"
#include "face_detect.hpp"


/*
    Returns model name from command line arguments or exits on failure  
*/
std::string get_model_name(int argc, char *argv[]) {

    std::string model_name;
    if (argc != 2) {
        std::cout << "Error: Correct usage: ./train <model_name>" << std::endl;
        exit(1);
    } else {
        return argv[1];
    }

}


int main(int argc, char *argv[]) {

    std::string model_name = get_model_name(argc, argv);

    // Integer labels for positive subjects (0 for negative subjects)
    std::vector<int> labels;
    // All training images to be used. Order corresponds with label vector
    std::vector<cv::Mat> training_images;

    // Load positive training images
    std::vector<std::string> directories = get_directories(std::string(TRAINING_DIR) + "positive/");
    std::cout << "Loading positive training images for subjects:" << std::endl;
    for (int i = 0; i < directories.size(); i++) {
        int right_padding = 20 - directories[i].size();
        std::cout << "\t" << "(" << i + 1 << ") " << directories[i] << std::string(right_padding, ' ') << std::flush;
        std::vector<std::string> image_files = get_files(std::string(TRAINING_DIR) + "positive/" + directories[i]);
        for (int j = 0; j < image_files.size(); j++) {
            training_images.push_back(cv::imread(std::string(TRAINING_DIR) + "positive/" + directories[i] + "/" + image_files[j], cv::IMREAD_GRAYSCALE));
            labels.push_back(i + 1);
        }
        std::cout << "[DONE]" << std::endl;
    }

    // Load negative training images
    std::cout << "Loading negative training images for subjects ... " << std::flush;
    std::vector<std::string> image_files = get_files(std::string(TRAINING_DIR) + "negative/georgia_tech");
    int total_neg = 0;
    for (int i = 0; i < image_files.size(); i++) {
	printf("Loading negative image: %d\n", i+1);
        cv::Mat temp_image = cv::imread(std::string(TRAINING_DIR) + "negative/georgia_tech/" + image_files[i], cv::IMREAD_GRAYSCALE);
        std::vector<cv::Rect> face_regions = detect_faces(temp_image);
        if (face_regions.size() == 1) {
            training_images.push_back(temp_image(face_regions[0]));
            labels.push_back(0);
            total_neg ++;
        }
       
    }
    std::cout << "Was able to use " << total_neg << " of " << image_files.size() << " negative images." << std::endl;
    std::cout << "[DONE]" << std::endl;

    // Prepare images for training
    std::cout << "Preparing images for training ... ";
    for (int i = 0; i < training_images.size(); i++) {
        // Resize images to match negative training images
        // Uses Lanczos resampling to preserve edges and features
        cv::resize(training_images[i], training_images[i], cv::Size(FACE_WIDTH, FACE_HEIGHT), 0, 0, cv::INTER_LANCZOS4);
    }
    std::cout << "[DONE]" << std::endl;

    // Train model
    std::cout << "Training model with " << training_images.size() << " faces ... " << std::flush;
    cv::Ptr<cv::face::FaceRecognizer> model = cv::face::LBPHFaceRecognizer::create();
    model->train(training_images, labels);
    std::cout << "[DONE]" << std::endl;

    // Test Prediction
    int label;
    double confidence;
    model->predict(training_images[0], label, confidence);

    // Save model
    std::string filepath = std::string(MODEL_DIR) + model_name + ".xml";
    std::cout << "Saving model to " << filepath << " ... " << std::flush;
    model->write(filepath);
    std::cout << "[DONE]" << std::endl;

}
