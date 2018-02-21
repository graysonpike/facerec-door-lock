// Grayson Pike, 2018

#include "files.hpp"

#include <iostream>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>


/*
    Returns a vector of strings representing the directories within a given path
    Strings are directory names, not full paths
*/
std::vector<std::string> get_directories(std::string path) {

    std::vector<std::string> result;

    DIR *dir = opendir(path.c_str());
    struct dirent *entry = readdir(dir);
    while (entry != NULL)
    {
        // Only add directories to list, not files
        // Ignore . and .. as directory listings
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            result.push_back(entry->d_name);
        }
        entry = readdir(dir);
    }
    closedir(dir);

    return result;

}


/*
    Returns a vector of strings representing the files within a given path
    Strings are filenames, not full paths
*/
std::vector<std::string> get_files(std::string path) {

    std::vector<std::string> result;

    DIR *dir = opendir(path.c_str());
    struct dirent *entry = readdir(dir);
    while (entry != NULL)
    {
        // Only add directories to list, not files
        // Ignore . and .. as directory listings
        if (entry->d_type == DT_REG && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            result.push_back(entry->d_name);
        }
        entry = readdir(dir);
    }
    closedir(dir);

    return result;

}

/*
    Create a directory if it doesn't already exist
    Doesn't create intermediate directories, nested directories will need to be created one at a time
    Returns true on success, false otherwise.
*/
bool create_directory(std::string path) {

    if (mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) {
        std::cerr << "Error creating directory '" << path << "'. Does it already exist?" << std::endl;
        return false;
    }
    return true;

}


/*
    Save an image in PGM format with a given path/filename
    Returns true on success, false otherwise
*/
bool save_pgm_image(cv::Mat image, std::string filepath) {
    // Save cropped image to file
    try {    
        cv::imwrite(filepath, image);
    }
    catch (std::runtime_error& ex) {
        std::cerr << "Exception saving image to PGM format: " << ex.what() << std::endl;
        return false;
    }
    return true;
}