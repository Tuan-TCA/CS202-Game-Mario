#include "Player.hpp"
#include "Block.hpp"
#include <iostream>
using namespace std;

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
    float dt = GetFrameTime(); //Thời gian vẽ 1 frame (second) (dựa theo FPS) để đảm bảo vận tốc đúng px/s với mọi FPS
    handleInput(dt);
    applyPhysics(dt);
    animate();
}

// Draw the player
void Player::display() {
    DrawRectangle((int)pos.x, (int)pos.y, (int)size.x, (int)size.y, RED);
}

// Collision response
void Player::updateCollision(GameObject* other, int type) {
    if (Block* block = dynamic_cast<Block*>(other)) {
        if (block->isSolid) {
            Rectangle bound = other->getBounds();
            if(type == HEAD) {
                cout << type << endl;
                pos.y = bound.y - size.y;
                onGround = true;
                velocity.y = 0;
            }
            if(type == FEET && velocity.y < 0) {
                cout << type << endl;
                velocity.y = 0;
                pos.y = bound.y + bound.height;
            }
            if(type == LEFT) {
                cout << type << endl;
                pos.x = bound.x - size.x;
                velocity.x = 0;
            }
            if(type == RIGHT) {
                cout << type << endl;
                pos.x = bound.x + bound.width;
                velocity.x = 0;
            }            
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
