// Grayson Pike, 2018

#ifndef HARDWARE_HPP
#define HARDWARE_HPP

#include <opencv2/videoio.hpp>

void flush_capture_buffer(cv::VideoCapture& capture);
cv::VideoCapture get_camera();

class GPIO {

public:

	// Create a GPIO object to control pin GPIO<pin>
	// Exports the pin
	GPIO(std::string pin, std::string dir);
	// Unexports pin
	~GPIO();

	void set_dir(std::string dir);
	void set_value(std::string value);
	int read_value();

private:

	std::string pin;

	void export_pin();
	void unexport_pin();

};

#endif