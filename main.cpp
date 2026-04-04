#include <iostream>

#include "Engine.hpp"
#include "Game/Game.hpp"

int main(int, char**){
    std::cout << "Hello, from DTEngine!\n";
    
    try {
        DTEngine::Engine engine("C:/Users/marco/Documents/Dev/Projects/DesktopGameEngine_v1/Game/Assets");
        Game game;
        engine.Run();
    } catch (std::string err) {
        std::cout << "Err: " << err << std::endl;
    }
}
