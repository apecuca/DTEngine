#include <PathManager.hpp>

#include "stb_image.h"

#include <fstream>
#include <sstream>

using namespace DTEngine;

std::string PathManager::GetFileContents(const std::string& path)
{
    std::string normalizedPath = "Engine/resources/" + path;

    std::string content;
    std::ifstream file;

    // ensure ifstream objects can throw exceptions
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // open files
        file.open(normalizedPath);
        std::stringstream fileStream;
        // read file's buffer contents into streams
        fileStream << file.rdbuf();
        // close file handlers
        file.close();
        // convert stream into string
        content = fileStream.str();
    }
    catch (std::ifstream::failure& e) {
        throw std::string("File read err: " + std::string(e.what()));
    }

    return content;
}

unsigned char* PathManager::GetImageContent(const std::string& path, int& outWidth, int& outHeight, int& nrChannels)
{
    std::string normalizedPath = "Engine/resources/images/" + path;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(normalizedPath.c_str(), &outWidth, &outHeight, &nrChannels, 0);

    if (!data)
        throw std::string("Failed to read image from " + normalizedPath);

    return data;
}

void PathManager::CloseImage(unsigned char* data)
{
    stbi_image_free(data);
}