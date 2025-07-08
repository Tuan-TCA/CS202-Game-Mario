#include "Game.hpp"
#include <chrono>
#include <thread>

Game::Game()
{
    mapPaths = {
		{"Map1.1", "assets/Map/Map1.1.json"},
		// Add the rest...
	};
    current_Map = "Map1.1";
    curMap.choose(mapPaths[current_Map]);

    Mario = new Player({100,0}, {16,16});
    
}

Game::~Game() {
    delete Mario;
    //curMap.clearAll();
}

void Game::update() {
    curMap.update();
    Mario->update();

    //Check Collision
    // Mario with Map
    
    for(auto &x : curMap.tileBlocks) {
        if(Mario->checkCollision(x)) {
            cout << "Collision Mario-Blocks" << endl;
            Mario->updateCollision(x);
            x->updateCollision(Mario);
            break;
        }
    }

    //Block with Block
}

void Game::display() {
    curMap.display();
    Mario->display();
    
}