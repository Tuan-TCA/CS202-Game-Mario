#pragma once

#include <vector>
#include "raylib.h"
#include <algorithm>
#include <cmath>
#include "Movement.hpp"
using namespace std;

enum CollisionType {
    NONE,
    HEAD,   // A HEAD B là A đứng trên B
    FEET,   // A nhảy lên đụng B
    LEFT,   // A ở bên trái B
    RIGHT,  // A ở bên phải B
};

inline float Distance(Vector2 a, Vector2 b) {
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
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

    virtual Vector2 getVelocity() const {
        return move.velocity;
    }
    // Kiểm tra va chạm giữa hai GameObject. Return enum CollisionType là Direction
    int checkCollision(const GameObject* other) {
        //Phải thêm epsilon chỉnh bounds vì frame Raylib không chính xác
        const float epsX = -0.55f, epsY = -0.55f;

        Rectangle A = getBounds();
        A.x      -= epsX;  A.y      -= epsY;
        A.width  += 2*epsX; A.height += 2*epsY;

        Rectangle B = other->getBounds();
        B.x      -= epsX;  B.y      -= epsY;
        B.width  += 2*epsX; B.height += 2*epsY;


        if (!CheckCollisionRecs(A, B) || (Distance(getCenter(), other->getCenter()) - 16*sqrt(2)) > 0.05f)
            return NONE;
            
        float penLeft   = fabsf(A.x + A.width  - B.x),
            penRight  = fabsf(B.x + B.width  - A.x), // Đo độ sâu "chèn", ngược lại để dương
            penTop    = fabsf(A.y + A.height - B.y),
            penBottom = fabsf(B.y + B.height - A.y);

        vector<float> tmp;
        tmp.push_back(INT_MAX);
        tmp.push_back(penTop);
        tmp.push_back(penBottom);
        tmp.push_back(penLeft);
        tmp.push_back(penRight);
        
        Vector2 velo = getVelocity();
        if(velo.y < 0 && (Distance(getCenter(), other->getCenter()) - 16) > 0.05f)
            return NONE;
        if(velo.y < 0) tmp[1] = INT_MAX;
        if(velo.y > 0) tmp[2] = INT_MAX;
        
        if(velo.x == 0) tmp[3] = tmp[4] = INT_MAX;
        if(velo.y == 0) tmp[1] = tmp[2] = INT_MAX;

        
        float m = INT_MAX;
        for(auto &x : tmp) m = min(m,x);

        for(int i = 0; i < tmp.size(); i++)
            if(m == tmp[i]) return i;
        
        return NONE;
    }


    const Vector2& getPosition() const { return pos; }
    void setPosition(const Vector2& _pos) { pos = _pos; }

    const Vector2& getSize() const { return size; }
    void setSize(const Vector2& s) { size = s; }

    virtual Rectangle getBounds() const {
        return {pos.x, pos.y, size.x,size.y};
    }
    Vector2 getCenter() const { return {pos.x + size.x/2 , pos.y + size.y/2 }; }
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

    Movement move;
        
};

