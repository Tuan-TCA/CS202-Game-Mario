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
        // bật jumping để block bật lên
        block->isJumping = true;
        // đánh dấu để xóa nếu muốn
        block->needDeletion = true;
        std::cout << "[Breakable] block broken\n";
    }
}

void BreakableBehavior::updateFrame(Block* self, float dt) {
    // ví dụ fade out hoặc chờ xóa, bỏ trống nếu không cần
}

void BreakableBehavior::onDraw(const Block* self) {
    // vẽ bình thường, hoặc override nếu muốn hiệu ứng
    DrawTextureRec(self->texture, self->srcRec, self->getPosition(), self->color);
}

// --- QuestionBehavior ----------------------------------------------------

// bạn có thể override updateFrame/onDraw nếu cần bump animation vẽ khác

// --- GroundBehavior ------------------------------------------------------

void GroundBehavior::reactToCollision(GameObject* p, int type) {
    // Ground block không làm gì khi bị chạm
    (void)p;
    (void)type;
}

// GroundBehavior không cần updateFrame hoặc onDraw đặc biệt
