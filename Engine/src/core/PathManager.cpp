#include <PathManager.hpp>

#include <fstream>
#include <sstream>

using namespace DTEngine;

std::string PathManager::GetFileContents(const std::string& path)
{
    std::string normalizedPath = "Engine/assets/" + path;

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

    /*
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // ensure ifstream objects can throw exceptions
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        throw std::string("Shader files err: " + std::string(e.what()));
    }
    */
}