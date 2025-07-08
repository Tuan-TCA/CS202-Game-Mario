#pragma once
#include <unordered_map>
#include "Global.hpp"
#include "Player.hpp"
#include "MyMap.hpp"

class Scene {
public:
	SceneMode CurrentScene;

	Scene() = default;
	// update
	virtual void update() = 0;
	//virtual void updateSceneInCamera(Camera2D cam) = 0;

	// display
	virtual void display() = 0;
	//virtual void displaySceneInCamera() = 0;
    
	virtual ~Scene() = default;
};

class Menu : public Scene {

};