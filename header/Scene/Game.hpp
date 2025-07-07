#pragma once
#include "Player.hpp"
#include "MyMap.hpp"
#include "Scene.hpp"
#include "raylib-tileson.h"

class Game : public Scene {
protected:
    Player* Mario;
    
    std::unordered_map<std::string, std::string> mapPaths;
    string current_Map;
    MyMap curMap;
public:
    
    // initialize
    Game();

    // update
    void updateScene() override ;

	virtual void updateSceneInCamera(Camera2D cam) { };
    // display
    void displayScene() override;
	virtual void displaySceneInCamera() { };

    
    ~Game() = default;

};

