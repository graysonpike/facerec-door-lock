// Grayson Pike, 2018

#include "files.hpp"

#include <dirent.h>
#include <stdio.h>
#include <string.h>


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