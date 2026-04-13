#include "system/PathSystem.hpp"

#include "stb_image.h"

#include <fstream>
#include <sstream>
#include <algorithm>

using namespace DTEngine;

//
// IMAGE DATA
//

ImageData::~ImageData()
{
    if (data)
    {
        stbi_image_free(data);
        data = nullptr;
    }
}

ImageData::ImageData(ImageData&& other) noexcept
{
    data = other.data;
    width = other.width;
    height = other.height;
    channels = other.channels;

    other.data = nullptr;
    other.width = 0;
    other.height = 0;
    other.channels = 0;
}

ImageData& ImageData::operator=(ImageData&& other) noexcept
{
    if (this != &other)
    {
        if (data)
            stbi_image_free(data);

        data = other.data;
        width = other.width;
        height = other.height;
        channels = other.channels;

        other.data = nullptr;
        other.width = 0;
        other.height = 0;
        other.channels = 0;
    }

    return *this;
}

//
// PATH SYSTEM
//

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

ImageData PathSystem::GetImageContent(const std::string& path) const
{
    stbi_set_flip_vertically_on_load(true);

    ImageData img;
    img.data = stbi_load(path.c_str(), &img.width, &img.height, &img.channels, 0);

    if (!img.data)
        throw std::string("Failed to read image from " + path);

    return img;
}