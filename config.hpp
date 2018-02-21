// Grayson Pike, 2018

// For training images
#define TRAINING_DIR "training/"
// For XML files representing the saved states of trained models
#define MODEL_DIR "complete_models/"
// Prefix on image filenames. Image number is appended before saving
#define TRAINING_FILENAME_PREFIX "positive_"

// Constants for Haar Cascade face detection
#define HAAR_FACES_FILE "cascades/haarcascade_frontalface_alt.xml"
#define HAAR_SCALE_FACTOR  1.1
#define HAAR_MIN_NEIGHBORS 4
#define HAAR_FLAGS 0
#define HAAR_MIN_SIZE_X 30
#define HAAR_MIN_SIZE_Y 30


// Directory for completed (trained) model states to be stored in
#define MODEL_DIR "complete_models/"

// Threshold for a recognized face before it's considered a positive match.
// Lower value -> closer match to allowed face
// Lower value for stricter recognition, raise value for more strict recognition
#define POSITIVE_THRESHOLD 80.0

// Size (in pixels) to resize images for training and prediction
// Don't change this unless you also change the size of the training images
// #define FACE_WIDTH  92
// #define FACE_HEIGHT 112
#define FACE_WIDTH  200
#define FACE_HEIGHT 200
