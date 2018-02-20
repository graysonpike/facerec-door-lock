#include "hardware.hpp"
#include <iostream>
#include <cstdio>
#include <ctime>


// http://answers.opencv.org/question/29957/highguivideocapture-buffer-introducing-lag/post-id-38217/
// Hack to clear capture buffer
// Setting buffer size to 0 is not supported with Raspberry Pi Camera
// Clearing the buffer is also not supported with the Raspberry Pi Camera
void flush_capture_buffer(cv::VideoCapture& capture) {

	// Begin measuring time
    std::clock_t start_time;
    double duration;

    int i = 0;
    while (i < 5) {
        start_time = std::clock();
        capture.grab();                      
        duration = (std::clock() - start_time) / (double)CLOCKS_PER_SEC;        
        std::cout << "Duration: " << duration << std::endl;
        i++;
    }

}