#include "Game.hpp"
#include "UI.hpp"
#include <chrono>
#include <thread>

Game::Game()
{
    mapPaths = {
		{"Map1.1", "assets/Map/Map1.1.json"},
		// Add the rest...
	};
    init();

}
void Game::init() {

    current_Map = "Map1.1";
    curMap.choose(mapPaths[current_Map]);


}

void Game::updateScene() {
    // Mario.update();
    // Goomba.update();
    curMap.update();

    //Check Collision
    //Mario with Map
    // for(auto &x : curMap.tileBlocks) {
    //     if(Mario.checkCollision(x)) {
    //         cout << "Collision Mario-Blocks" << endl;
    //         Mario.updateCollision(x);
    //         x->updateCollision(&Mario);
    //         break;
    //     }
    // }

    //Block with Block



}
void Game::displaySceneInCamera() {
    curMap.display();
    // Mario.display();
    // Goomba.display();
}
void Game::displayScene() {
}
