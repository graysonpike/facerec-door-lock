#ifndef FACE_DETECT_HPP
#define FACE_DETECT_HPP

#include <opencv2/core.hpp>

std::vector<cv::Rect> detect_faces(cv::Mat image);

#endif