#ifndef DTENGINE_PATHSYSTEM_H
#define DTENGINE_PATHSYSTEM_H

#include "core/InternalWork.hpp"

#include <string>

namespace DTEngine
{

class PathSystem : InternalWork
{
friend class InternalWorksManager;

public:
    ~PathSystem();
    PathSystem();

public:
    std::string GetFileContents(const std::string& path);
    unsigned char* GetImageContent(const std::string& path, int& outWidth, int& outHeight, int& nrChannels);
    void CloseImage(unsigned char* data);

protected:
    bool Init() override;

};

}

#endif