clean:
	rm -f capture_positives.out test_opencv.out

capture_positives: capture_positives.cpp face_detect.cpp
	g++ -g capture_positives.cpp face_detect.cpp -o capture_positives.out -lopencv_core -lopencv_imgcodecs -lopencv_videoio -lopencv_imgproc -lopencv_objdetect

train: train.cpp files.cpp
	g++ -g train.cpp files.cpp -o train.out -lopencv_core -lopencv_imgcodecs

test_opencv: test_opencv.cpp
	g++ -g test_opencv.cpp -o test_opencv.out -lopencv_core

