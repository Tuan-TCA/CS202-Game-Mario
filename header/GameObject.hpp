#pragma once

#include <vector>
#include "raylib.h"
#include <algorithm>
#include <cmath>
using namespace std;

enum CollisionType {
    NONE,
    HEAD,   // A HEAD B là A đứng trên B
    FEET,   // A nhảy lên đụng B
    LEFT,   // A ở bên trái B
    RIGHT,  // A ở bên phải B
};

//Là một hình chữ nhật, mô tả mọi Object trong Game.
class GameObject {
public:
    friend class Movement;
    GameObject() = default;
    GameObject(const Vector2& _position, const Vector2& size)
        : pos(_position), size(size) {}

    virtual ~GameObject() = default;

    virtual void update() { };

    virtual void display() {};

    // Xử lý khi va chạm với một object khác
    virtual void updateCollision(GameObject* other, int type) {
    }

    // Kiểm tra va chạm giữa hai GameObject. Return enum CollisionType là Direction
    int checkCollision(const GameObject* other) {
        //Phải thêm epsilon chỉnh bounds vì frame Raylib không chính xác
        const float epsX = -0, epsY = -0;
        Rectangle A = getBounds();
        A.x      -= epsX;  A.y      -= epsY;
        A.width  += 2*epsX; A.height += 2*epsY;

        Rectangle B = other->getBounds();
        B.x      -= epsX;  B.y      -= epsY;
        B.width  += 2*epsX; B.height += 2*epsY;

        if (!CheckCollisionRecs(A, B))
            return NONE;
            
        float penLeft   = fabsf(A.x + A.width  - B.x),
            penRight  = fabsf(B.x + B.width  - A.x), // Đo độ sâu "chèn", ngược lại để dương
            penTop    = fabsf(A.y + A.height - B.y),
            penBottom = fabsf(B.y + B.height - A.y);

        float m = min({ penLeft, penRight, penTop, penBottom }); // abs hết cho lành

        if (m == penLeft)   return LEFT;
        if (m == penRight)  return RIGHT;
        if (m == penTop)    return HEAD;
        if (m == penBottom) return FEET;

        return NONE;
    }

    const Vector2& getPosition() const { return pos; }
    void setPosition(const Vector2& _pos) { pos = _pos; }

    const Vector2& getSize() const { return size; }
    void setSize(const Vector2& s) { size = s; }

    virtual Rectangle getBounds() const {
        return {pos.x, pos.y, size.x,size.y};
    }

    const Vector2 getCenter() { return {pos.x + size.x/2 , pos.y + size.y/2 }; }
    int slice = 2;

    virtual Rectangle getFeet() const { return {pos.x, pos.y+size.y - slice, size.x, slice}; }
    virtual Rectangle getHead() const { return {pos.x, pos.y, size.x, slice}; }
    virtual Rectangle getLeft() const { return {pos.x, pos.y, slice, size.y}; }
    virtual Rectangle getRight() const { return {pos.x + size.x - slice, pos.y, slice, size.y}; }


protected:
    //Góc trái trên của Rec
    Vector2 pos;
    //Size Rectangle
    Vector2 size;
        
};

