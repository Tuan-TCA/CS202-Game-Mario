#include "IBlockBehavior.hpp"

#include "GameObject.hpp"
#include "raylib.h"
#include "IBlockBehavior.hpp"  
#include "Player.hpp"
#include "Block.hpp"


void QuestionBehavior::reactToCollision(GameObject* p, int type) {
    Player* player = dynamic_cast<Player*>(p);
    if (!player) return;

    if(type == FEET) {
        block->isJumping = true;
    }
}


void BreakableBehavior::reactToCollision(GameObject* p, int type) {
    // chỉ phản ứng khi va chạm với Player từ dưới lên
    Player* player = dynamic_cast<Player*>(p);
    if (!player) return;

    // FEET = đụng từ dưới
    if (type == FEET) {
        block->isJumping = true;
        block->needDeletion = true;

    }
}


void GroundBehavior::reactToCollision(GameObject* p, int type) {

}
