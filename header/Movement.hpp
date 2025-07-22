#pragma once
#include "raylib.h"

struct Movement {
public:

    void update(Vector2 &pos, float dt);

    inline void setVelocity(const Vector2& _vec) { velocity = _vec; }
    inline void setAcceleration(const Vector2& _acc) { acceleration = _acc; }
    inline void setGround(float _num) { GroundY = _num; }

    Vector2 velocity; // Current velocity
    Vector2 acceleration = {0 , 9.8f}; // Current acceleration
    float maxSpeed; // Maximum speed limit
    float friction; // Friction to apply when no input is 

    float GroundY = 300; // Ground level Y 

};