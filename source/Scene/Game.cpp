#include "Game.hpp"
#include <chrono>
#include <thread>

std::vector<Particle> Game::particles = {};    

Game::Game()
{
    mapPaths = {
		{"Map1.1", "assets/Map/Map1.1.json"},
		// Add the rest...
	};
    current_Map = "Map1.1";
    curMap.choose(mapPaths[current_Map]);

    Mario = new Player({100,0}, {16,16});
    
    cam.offset = { screenWidth/2, screenHeight/2};
    cam.target = { 150, 150};
    cam.zoom = 2.1f;
    cam.rotation = 0;
}

Game::~Game() {
    delete Mario;
    //curMap.clearAll();
}

void Game::update() {
    Mario->update();
    if(IsKeyDown(KEY_A)) cam.target = Mario->getCenter();

    if(IsKeyDown(KEY_Q))
        cout << Mario->getPosition().x << " " << Mario->getPosition().y << endl;

    // //Check Collision
    // Mario with Map
    GameObject* M = Mario;

    for(int i = 0; i < (int)curMap.tileBlocks.size(); ++i) {
        Block* x = curMap.tileBlocks[i];
        if(x->needDeletion) {
            //delete x;
            curMap.tileBlocks.erase(curMap.tileBlocks.begin() + i);
            --i; 
            continue;
        }
        int type = M->checkCollision(x);
        if(type) {
            M->updateCollision(x,type);
            x->updateCollision(M,type);
        }
    }

    
    curMap.update();
    for(auto &x : particles)
        x.update();
    //Block with Block
}

void Game::display() {
    float dt = GetFrameTime();
    curMap.display();
    Mario->display();
    for(auto &x : particles)
    {
        x.display(dt);
    }
}