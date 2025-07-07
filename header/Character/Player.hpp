#pragma once
#include "GameObject.hpp"
#include "raylib.h"

class Player : public GameObject {
public:
    Player() = default;
    Player(Vector2 _pos, Vector2 _size) : GameObject(_pos,_size) { }

    void update() override { 
        float dt = GetFrameTime();
        handleInput(dt);
        applyPhysics(dt);
        animate();
    }

    void display() override {
        DrawRectangle((int)pos.x, (int)pos.y, (int)size.x, (int)size.y, RED);
    }

private:
    Vector2 velocity   = { 0, 0 };
    const float speed     = 200.0f;  // pixels per second
    const float jumpForce = 350.0f;  // initial jump velocity
    const float gravity   = 900.0f;  // gravity acceleration
    bool onGround         = true;

    static constexpr int GroundY = 250;

    // Xử lý input: set velocity.x và khởi tạo jump
    void handleInput(float dt) {
        // Di chuyển ngang
        velocity.x = 0;
        if (IsKeyDown(KEY_LEFT))  velocity.x = -speed;
        if (IsKeyDown(KEY_RIGHT)) velocity.x = +speed;
        pos.x += velocity.x * dt;

        // Nhảy
        if (onGround && IsKeyPressed(KEY_UP)) {
            velocity.y = -jumpForce;
            onGround = false;
        }
    }

    // Áp dụng gravity, cập nhật vị trí dọc và va chạm sàn
    void applyPhysics(float dt) {
        // Gravity
        velocity.y += gravity * dt;
        pos.y += velocity.y * dt;

        // Va chạm với sàn
        if (pos.y > GroundY) {
            pos.y = GroundY;
            velocity.y = 0;
            onGround = true;
        }
    }

    void animate() { /* giữ nguyên nếu không thay đổi */ }
};
