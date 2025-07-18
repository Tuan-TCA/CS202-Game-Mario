#pragma once
#include "raylib.h"
#include "GameObject.hpp"
#include <iostream>

class Block;
class Player;

struct IBlockBehavior {
    virtual ~IBlockBehavior() = default;
    virtual void reactToCollision(GameObject* p, int type) = 0;
    virtual void updateFrame(Block* self, float dt) {}
    virtual void onDraw(const Block* self) {}
    IBlockBehavior(Block* block) : block(block) {}

    Block* block; // Reference to the Block instance
};

class BreakableBehavior : public IBlockBehavior {
public:
    BreakableBehavior(Block* block) : IBlockBehavior(block) {}

    void reactToCollision(GameObject* p, int type) override;
    void updateFrame(Block* self, float dt) override;
    void onDraw(const Block* self) override;
};


class QuestionBehavior : public IBlockBehavior {
public:
    QuestionBehavior(Block* block) : IBlockBehavior(block) {}
    void reactToCollision(GameObject* p, int type) override;
    //void updateFrame(Block* self, float dt) override;
    //void onDraw(const Block* self) override;
};


class GroundBehavior : public IBlockBehavior {
public:
    GroundBehavior(Block* block) : IBlockBehavior(block) {}
    void reactToCollision(GameObject* p, int type) override;
    //void updateFrame(Block* self, float dt) override;
    //void onDraw(const Block* self) override;
};

struct FactoryIBlockBehavior {
    static IBlockBehavior* create(const std::string& type, Block* block) {
        if (type == "Breakable") return new BreakableBehavior(block);
        if (type == "Question") return new QuestionBehavior(block);
        if (type == "Ground") return new GroundBehavior(block);
        // Add more behaviors as needed
        return nullptr;
    }
};
