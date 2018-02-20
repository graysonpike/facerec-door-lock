clean:
	rm -f capture_positives.out test_opencv.out train.out lock.out

capture_positives: capture_positives.cpp face_detect.cpp hardware.cpp
	g++ -g capture_positives.cpp face_detect.cpp hardware.cpp -o capture_positives.out -lopencv_core -lopencv_imgcodecs -lopencv_videoio -lopencv_imgproc -lopencv_objdetect

train: train.cpp files.cpp
	g++ -g train.cpp files.cpp -o train.out -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_face

lock: lock.cpp face_detect.cpp hardware.cpp
	g++ -g lock.cpp face_detect.cpp hardware.cpp -o lock.out -lopencv_core -lopencv_face -lopencv_videoio -lopencv_objdetect -lopencv_imgproc -lopencv_imgcodecs

test_opencv: test_opencv.cpp
	g++ -g test_opencv.cpp -o test_opencv.out -lopencv_core

