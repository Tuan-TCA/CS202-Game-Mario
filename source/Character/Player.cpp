
// Player.cpp
#include "Player.hpp"
#include "Block.hpp"       // Full definition for dynamic_cast
#include <iostream>
// Constructors
Player::Player()
    : GameObject({0,0}, {0,0})
    , velocity{0,0}
    , onGround(true)
{}

Player::Player(Vector2 _pos, Vector2 _size)
    : GameObject(_pos, _size)
    , velocity{0,0}
    , onGround(true)
{}

// Update per frame
void Player::update() {
    float dt = GetFrameTime();
    handleInput(dt);
    applyPhysics(dt);
    animate();
}

// Draw the player
void Player::display() {
    DrawRectangle((int)pos.x, (int)pos.y, (int)size.x, (int)size.y, RED);
}

// Collision response
void Player::updateCollision(GameObject* other) {
    if (Block* block = dynamic_cast<Block*>(other)) {
        if (block->isSolid) {
            // Push player up until just above block head
            // if (pos.y + size.y > block->getPosition().y) {
            //     pos.y = block->getPosition().y - size.y;
            //     //std::cout << "@@@@@@@@@@@\n";
            //     velocity.y = 0;
            //     onGround = true;
            // }
            // else
            // if(pos.y > block->getPosition().y + block->getSize().y  ) {
            //     pos.y = block->getPosition().y + block->getSize().y;
            //     //std::cout << "##########\n";
            // }
        }
    }
}

// Handle keyboard input
void Player::handleInput(float dt) {
    velocity.x = 0;
    if (IsKeyDown(KEY_LEFT))  velocity.x = -speed;
    if (IsKeyDown(KEY_RIGHT)) velocity.x =  speed;
    pos.x += velocity.x * dt;

    if (onGround && IsKeyPressed(KEY_UP)) {
        velocity.y = -jumpForce;
        onGround = false;
    }
}

// Apply gravity and vertical movement
void Player::applyPhysics(float dt) {
    velocity.y += gravity * dt;
    pos.y += velocity.y * dt;

    // Ground collision
    if (pos.y > GroundY) {
        pos.y = GroundY;
        velocity.y = 0;
        onGround = true;
    }
}

// Placeholder for animations
void Player::animate() {
    // TODO: implement animation logic
}
