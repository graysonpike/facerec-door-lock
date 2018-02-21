// Grayson Pike, 2018

#ifndef FILES_HPP
#define FILES_HPP

#include <vector>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>


std::vector<std::string> get_directories(std::string path);
std::vector<std::string> get_files(std::string path);
bool create_directory(std::string path);
bool save_pgm_image(cv::Mat image, std::string filepath);

#endif