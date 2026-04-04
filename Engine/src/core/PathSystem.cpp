#include "core/PathSystem.hpp"

#include "stb_image.h"

#include <fstream>
#include <sstream>

using namespace DTEngine;

PathSystem::~PathSystem()
{
    //
}

PathSystem::PathSystem()
{
    //
}

bool PathSystem::Init()
{
    return true;
}

void PathSystem::SetAssetsPath(const std::string& path)
{
    assetsPath = path;
    if (*assetsPath.end() != '/')
        assetsPath += "/";
}

std::string PathSystem::GetAssetsPath() const
{
    return assetsPath;
}

std::string PathSystem::GetFileContents(const std::string& path) const
{
    std::string content;
    std::ifstream file;

    // ensure ifstream objects can throw exceptions
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // open files
        file.open(path);
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

unsigned char* PathSystem::GetImageContent(const std::string& path, int& outWidth, int& outHeight, int& nrChannels) const
{
    //std::string normalizedPath = "Engine/resources/images/" + path;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &outWidth, &outHeight, &nrChannels, 0);

    if (!data)
        throw std::string("Failed to read image from " + path);

    return data;
}

void PathSystem::CloseImage(unsigned char* data) const
{
    stbi_image_free(data);
}