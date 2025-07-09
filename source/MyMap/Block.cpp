// Block.cpp
#include "Block.hpp"
#include "Player.hpp"
#include <iostream>
using namespace std;

Block::Block(int _gid, Vector2 _pos, Vector2 _size,
             Texture2D _tex, Rectangle _src)
    : GameObject(_pos, _size)
    , gid(_gid)
    , texture(_tex)
    , srcRec(_src)
{}

Block::Block(tson::Object &obj, Vector2 _pos, Vector2 _size,
             Texture2D _tex, Rectangle _src)
    : GameObject(_pos, _size)
    , gid(obj.getGid())
    , texture(_tex)
    , srcRec(_src)
{
    isSolid        = obj.get<bool>("isSolid");
    isBreakable    = obj.get<bool>("isBreakable");
    isQuestion     = obj.get<bool>("isQuestion");
    isInvisible    = obj.get<bool>("isInvisible");
    isUsed         = obj.get<bool>("isUsed");

    // containsItem trong Tiled lưu dưới dạng int
    int iv = obj.get<int>("containsItem");
    contains = static_cast<Contains>(iv);

    isPipeEntrance = obj.get<bool>("isPipeEntrance");
    isFlagPole     = obj.get<bool>("isFlagPole");
}

void Block::update() {
    // (nothing to do)
}

void Block::display() {
    if (isInvisible && !isUsed) return;
    DrawTextureRec(texture, srcRec, getPosition(), color);
}

void Block::updateCollision(GameObject* other) {
    Player* player = dynamic_cast<Player*>(other);
    if (!player) return;

    if (isSolid) {
        
    }
}
