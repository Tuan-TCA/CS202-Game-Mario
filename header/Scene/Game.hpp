#pragma once
#include "Scene.hpp"
#include "Player.hpp"
#include "MyMap.hpp"
#include "Particle.hpp"
#include <vector>
using namespace std;
class Game : public Scene {
public:
    Game();
	void Collision();
	~Game();

	static vector<Particle> particles;

private:
	Player* Mario;

	unordered_map<string, string> mapPaths;
    string current_Map;
    MyMap curMap;

	float prePosX = 0;
	void update() override;
	void display() override;
};