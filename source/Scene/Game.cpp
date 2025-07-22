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

    cout << curMap.StartingPoint.x << " " << curMap.StartingPoint.y << endl;

    Mario = new Player{{curMap.StartingPoint}, {16,16}};
    prePosX = Mario->getPosition().x;
    
    cam.offset = { 0 , 0};
    cam.target = {0, 0};
    cam.zoom = (float) screenHeight / WorldHeight;
    cam.rotation = 0;
}

Game::~Game() {
    delete Mario;
    //curMap.clearAll();
}

void Game::update() {
    Mario->update();
    //UpdateCamera 
    // cout << GetWorldToScreen2D(Mario->getPosition(), cam).x << " " << GetWorldToScreen2D(Mario->getPosition(), cam).y << endl;
    // if(GetWorldToScreen2D(Mario->getPosition(), cam).x > 400.f)

    float delta = Mario->getPosition().x - prePosX;
    if(GetWorldToScreen2D(Mario->getPosition(),cam).x > 0.8*screenWidth)
        cam.target.x += (delta > 1) ? delta : 0;
    if(GetWorldToScreen2D(Mario->getPosition(),cam).x < 0.2*screenWidth)
        cam.target.x += (delta < -1) ? delta : 0;


    if(IsKeyDown(KEY_Q))
        cout << Mario->getPosition().x << " " << Mario->getPosition().y << endl;
    
        
        if(IsKeyDown(KEY_A))
            cam.target = Mario->getPosition();

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

    prePosX = Mario->getPosition().x;
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