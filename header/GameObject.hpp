#pragma once

#include <vector>
#include "raylib.h"
#include <algorithm>
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
    GameObject() = default;
    GameObject(const Vector2& _position, const Vector2& size)
        : pos(_position), size(size) {}

    virtual ~GameObject() = default;

    virtual void update() = 0;

    virtual void display() = 0;

    // Xử lý khi va chạm với một object khác
    virtual void updateCollision(GameObject* other) {
    }

    // Kiểm tra va chạm giữa hai GameObject
    int checkCollision(const GameObject* other) {
        if(!CheckCollisionRecs(getBounds(), other->getBounds())) 
            return NONE;

        int penLeft = pos.x + size.x - other->pos.x,
            penRight = other->pos.x + other->size.x - pos.x, //Đo độ sâu "chèn", ngược lại để dương
            penTop = pos.y + size.y - other->pos.y,
            penBottom = other->pos.y + other->size.y - pos.y;
        
        int m = min({ abs(penLeft), abs(penRight), abs(penTop), abs(penBottom) });

        if(m == penLeft) return LEFT;
        if(m == penRight) return RIGHT;
        if(m == penTop) return HEAD;
        if(m == penBottom) return FEET;
        

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


