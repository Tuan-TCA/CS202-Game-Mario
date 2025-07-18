#pragma once
#include "raylib.h"
#include "GameObject.hpp"
#include <iostream>

class Block;
class Player;

struct IBlockBehavior {
    IBlockBehavior(Block* block) : block(block) {}

    virtual ~IBlockBehavior() { delete block; block = nullptr; };
    virtual void reactToCollision(GameObject* p, int type) {

    };
    virtual void updateFrame(Block* self, float dt) {}
    virtual void onDraw(const Block* self) {}

    virtual void printType() const {

    }

    Block* block = nullptr; // Reference to the Block instance
};

class BreakableBehavior : public IBlockBehavior {
public:
    BreakableBehavior(Block* block) : IBlockBehavior(block) {}
    void printType() const override {

    }
    void reactToCollision(GameObject* p, int type) override;
    //void updateFrame(Block* self, float dt) override;
    //void onDraw(const Block* self) override;
};


class QuestionBehavior : public IBlockBehavior {
public:
    QuestionBehavior(Block* block) : IBlockBehavior(block) {}
    void printType() const override {

    }
    void reactToCollision(GameObject* p, int type) override;
    //void updateFrame(Block* self, float dt) override;
    //void onDraw(const Block* self) override;
};


class GroundBehavior : public IBlockBehavior {
public:
    GroundBehavior(Block* block) : IBlockBehavior(block) {}
    void printType() const override {

    }
    void reactToCollision(GameObject* p, int type) override;
    //void updateFrame(Block* self, float dt) override;
    //void onDraw(const Block* self) override;
};

struct FactoryIBlockBehavior {
    static IBlockBehavior* create(const std::string& type, Block* block) {
        if (type == "BreakableBlock") return new BreakableBehavior(block);
        if (type == "QuestionBlock") return new QuestionBehavior(block);
        if (type == "GroundBlock") return new GroundBehavior(block);
        // Add more behaviors as needed
        return new IBlockBehavior(block); // Default behavior
    }
};
