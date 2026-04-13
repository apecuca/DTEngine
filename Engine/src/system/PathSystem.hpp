#ifndef DTENGINE_PATHSYSTEM_H
#define DTENGINE_PATHSYSTEM_H

#include "system/InternalSystem.hpp"

#include <string>

namespace DTEngine
{

struct ImageData
{
public:
    ~ImageData();
    ImageData() = default;

    ImageData(const ImageData&) = delete;
    ImageData& operator=(const ImageData&) = delete;

    ImageData(ImageData&& other) noexcept;

    ImageData& operator=(ImageData&& other) noexcept;

public:
    unsigned char* data = nullptr;
    int width = 0;
    int height = 0;
    int channels = 0;
};

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
    ImageData GetImageContent(const std::string& path) const;

protected:
    bool Init() override;

private:
    std::string assetsPath;
    const std::string resourcesPath = "Engine/resources/";

};

}

#endif