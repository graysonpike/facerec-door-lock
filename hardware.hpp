// Grayson Pike, 2018

#ifndef HARDWARE_HPP
#define HARDWARE_HPP

#include <opencv2/videoio.hpp>

void flush_capture_buffer(cv::VideoCapture& capture);
cv::VideoCapture get_camera();

#endif