#ifndef DTENGINE_PATHMANAGER_H
#define DTENGINE_PATHMANAGER_H

#include <string>

namespace DTEngine
{

class PathManager final
{
public:
    static std::string GetFileContents(const std::string& path);
    
private:
    ~PathManager() = default;
    PathManager() = default;

};

}

#endif