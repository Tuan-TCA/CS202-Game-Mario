// Player.hpp
#pragma once

#include "GameObject.hpp"
#include "raylib.h"

class Player : public GameObject {
public:
    // Constructors
    Player();
    Player(Vector2 _pos, Vector2 _size);

    // Override lifecycle methods
    void update() override;
    void display() override;
    void updateCollision(GameObject* other, int type) override;

private:
    // Physics & movement state
    Vector2 velocity;
    static constexpr float speed     = 200.0f;  // pixels per second
    static constexpr float jumpForce = 350.0f;  // initial jump velocity
    static constexpr float gravity   = 900.0f;  // gravity acceleration
    bool onGround;
    static constexpr int GroundY = 240;

    // Helpers
    void handleInput(float dt);
    void applyPhysics(float dt);
    void animate();
};