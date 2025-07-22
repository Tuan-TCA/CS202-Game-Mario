#include "IBlockBehavior.hpp"
#include "raylib.h"
#include "Player.hpp"
#include "Block.hpp"
#include "Particle.hpp"
#include "Game.hpp"

void QuestionBehavior::reactToCollision(GameObject* p, int type) {
    Player* player = dynamic_cast<Player*>(p);
    if (!player) return;

    if(type == FEET) {
        cout << "Question Block hit!" << endl;
        block->isJumping = true;
    }
}

void QuestionBehavior::updateFrame(float dt) {
    if(block->isJumping) {
        block->handleInput(dt);
        block->applyPhysics(dt);
    }
}

void BrickBehavior::reactToCollision(GameObject* p, int type) {

    Player* player = dynamic_cast<Player*>(p);
    if (!player) return;

    if (type == FEET) {
        block->needDeletion = true;
        Particle::spawnParticles(*block, Game::particles);
    }
}

void BrickBehavior::updateFrame(float dt) {

}

void BrickBehavior::onDraw(float dt) {
}

void GroundBehavior::reactToCollision(GameObject* p, int type) {

}
