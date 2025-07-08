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

	// display
	virtual void display() = 0;
    
	virtual ~Scene() = default;

	inline Camera2D getCamera() const {
		return cam;
	};

protected:
	Camera2D cam;
};

class Menu : public Scene {

};