// Grayson Pike, 2018

#include "hardware.hpp"
#include <iostream>
#include <cstdio>
#include <ctime>

/*
	http://answers.opencv.org/question/29957/highguivideocapture-buffer-introducing-lag/post-id-38217/
	Hack to clear capture buffer
	Setting buffer size to 0 is not supported with Raspberry Pi Camera
	Clearing the buffer is also not supported with the Raspberry Pi Camera
*/
void flush_capture_buffer(cv::VideoCapture& capture) {

	// Begin measuring time
	std::clock_t start_time;
	double duration;

	// Frame buffer holds five frames, grab and dispose of them all
	for(int i = 0; i < 10; i++) {
		start_time = std::clock();
		capture.grab();
		duration = (std::clock() - start_time) / (double)CLOCKS_PER_SEC;
		i++;
	}

}

/*
	Returns an instance of the default camera as a VideoCapture object
	or exits on failure.

	Open the default camera
    If this fails, make sure you've run
    sudo modprobe bcm2835-v4l2
    ^ PLACE THIS IN YOUR ~/.bash_profile
    which creates a device for the camera at /dev/video0
*/
cv::VideoCapture get_camera() {

	cv::VideoCapture camera(0);

	if (!camera.isOpened()) {
        std::cerr << "Failed to open the camera. Have you run 'sudo modprobe bcm2835-v4l2'?" << std::endl;
        return 1;
    }

    return camera;
}