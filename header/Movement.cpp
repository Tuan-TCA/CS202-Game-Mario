#include "Movement.hpp"
    
const Vector2 operator+(const Vector2 a, const Vector2 b) {
    return {a.x + b.x, a.y + b.y};
}
const Vector2 operator*(const Vector2 a, float k) {
    return {a.x*k, a.y*k};
}


void Movement::update(Vector2 &pos, float dt) {
    velocity = velocity + acceleration*dt;
    pos = pos + velocity*dt;

    if(pos.y > GroundY) 
        pos.y = GroundY;
}

