#ifndef DTENGINE_PATHSYSTEM_H
#define DTENGINE_PATHSYSTEM_H

#include "core/InternalSystem.hpp"

#include <string>

namespace DTEngine
{

class PathSystem : InternalSystem
{
friend class SystemRegistry;

public:
    ~PathSystem();
    PathSystem();

public:
    void SetAssetsPath(const std::string& path);
    std::string GetAssetsPath() const;

    inline std::string GetResourcesPath() const { return resourcesPath; }

    std::string GetFileContents(const std::string& path) const;
    unsigned char* GetImageContent(const std::string& path, int& outWidth, int& outHeight, int& nrChannels) const;
    void CloseImage(unsigned char* data) const;

protected:
    bool Init() override;

private:
    std::string assetsPath;
    const std::string resourcesPath = "Engine/resources/";

};

}

#endif