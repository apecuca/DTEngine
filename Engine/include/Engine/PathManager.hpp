#ifndef DTENGINE_PATHMANAGER_H
#define DTENGINE_PATHMANAGER_H

#include <string>

namespace DTEngine
{

class PathManager final
{
public:
    static std::string GetFileContents(const std::string& path);
    static unsigned char* GetImageContent(const std::string& path, int& outWidth, int& outHeight, int& nrChannels);
    static void CloseImage(unsigned char* data);
    
private:
    ~PathManager() = default;
    PathManager() = default;

};

}

#endif