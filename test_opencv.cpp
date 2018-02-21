// Grayson Pike, 2018

// This program should output the version of OpenCV if it's installed correctly.

#include <iostream>
// Note: OpenCV 3 uses headers labled as 'opencv2'. It's just the way it is.
// https://docs.opencv.org/master/db/dfa/tutorial_transition_guide.html#gsc.tab=0
#include <opencv2/core.hpp>

using namespace std;

int main(int argc, char *argv[]) {

    cout << "Version: " << CV_VERSION << endl;

}
