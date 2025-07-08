#pragma once
#include "Scene.hpp"
#include "Player.hpp"
#include "MyMap.hpp"

class Game : public Scene {
public:
    Game();
	void Collision();
    ~Game();

private:
	Player* Mario;

	unordered_map<string, string> mapPaths;
    string current_Map;
    MyMap curMap;

	void update() override;
	void display() override;
};