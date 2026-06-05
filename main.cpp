#include <iostream>

#include <DTEngine/Engine.hpp>
#include "Game/Game.hpp"

#include <stdexcept>

int main(int, char**){
    std::cout << "Hello, from DTEngine!\n";
    
    try {
        DTEngine::Engine engine("../../Game/Assets", "resources");
        Game game;
        engine.Run();
    } catch (const std::string& e) {
        std::cout << "Err: " << e << std::endl;
    }
}
