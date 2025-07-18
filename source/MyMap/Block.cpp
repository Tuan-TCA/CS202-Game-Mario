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
    , prePos(_pos)
{}

Block::Block(tson::Object &obj, Vector2 _pos, Vector2 _size,
             Texture2D _tex, Rectangle _src)
    : GameObject(_pos, _size)
    , gid(obj.getGid())
    , texture(_tex)
    , srcRec(_src)
    , prePos(_pos)
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

Block::Block(tson::Tile* inforTile, Vector2 _pos, Vector2 _size,
             Texture2D _tex, Rectangle _src, const TSInfo* tsi)
    : GameObject(_pos, _size)
    , gid(inforTile->getGid())
    , texture(_tex)
    , srcRec(_src)
    , prePos(_pos)
{
// trong Block::Block(...):
    behavior = unique_ptr<IBlockBehavior>(
    FactoryIBlockBehavior::create(inforTile->getType(), this));

    tson::Animation animation = inforTile->getAnimation();

    if(animation.any()) {
        auto frames = animation.getFrames();
        
        duration= frames[0].getDuration();
        Rectangle tmpRec = srcRec;
        cout << frames.size() << endl;
        for(int i=0; i< frames.size(); ++i) {
            srcRecs.push_back({
                tmpRec.x + i*(tsi->tileSize.x + tsi->spacing),
                tmpRec.y,
                tmpRec.width,
                tmpRec.height
            });
        }
        // cout << tsi->tileSize.x << ' ' <<tsi->spacing << endl;
        // cout << srcRec.x << " " << srcRec.y <<" " << srcRec.width << " " << srcRec.height << endl;
        // for(auto x : srcRecs) {
        //     cout << x.x << " " << x.y <<" " << x.width << " " << x.height << endl;
        // }

    }

    isSolid        = inforTile->get<bool>("isSolid");
    isBreakable    = inforTile->get<bool>("isBreakable");
    isQuestion     = inforTile->get<bool>("isQuestion");
    isInvisible    = inforTile->get<bool>("isInvisible");
    isUsed         = inforTile->get<bool>("isUsed");

    int iv = inforTile->get<int>("containsItem");
    contains = static_cast<Contains>(iv);

    isPipeEntrance = inforTile->get<bool>("isPipeEntrance");
    isFlagPole     = inforTile->get<bool>("isFlagPole");


}


void Block::update() {
    float dt = GetFrameTime();
    
    //physics.update(dt);
    //behavior->updateFrame(this, dt);

    if(isJumping) {
        handleInput(dt);
        applyPhysics(dt);
    }
}

void Block::display() {
    //if (isInvisible && !isUsed) return;

    //Animation Display
    if(srcRecs.size() == 0) 
        DrawTextureRec(texture, srcRec, getPosition(), color);
    else {        
        aniTimer += GetFrameTime()*1000; //đổi qua mili giây vì duration ms
        if(aniTimer > duration) {
            aniIndex = (aniIndex+1) % srcRecs.size();
            aniTimer = 0;
        }
        DrawTextureRec(texture, srcRecs[aniIndex], getPosition(), color);
        // cout << aniTimer << endl;
    }

    //behavior->onDraw(this);
}

void Block::updateCollision(GameObject* other, int type) {
    Player* player = dynamic_cast<Player*>(other);
    if (!player) return;

    behavior->reactToCollision(player, type);
    
    // if(isBreakable && type == FEET) {
    //     isJumping = true;
    // }

    // if(isQuestion) cout <<"Question!!!";
}








//Physics Components
void Block::handleInput(float dt) {
    if (onGround && isJumping) {
        velocity.y = -jumpForce;
        onGround = false;
    }
}

// Apply gravity and vertical movement
void Block::applyPhysics(float dt) {
    velocity.y += gravity * dt;
    pos.y += velocity.y * dt;

    // Ground collision
    if (pos.y > prePos.y) {
        pos.y = prePos.y;
        velocity.y = 0;
        onGround = true;
        isJumping = false;
    }

    if (pos.y < prePos.y + maxHeight) {
        pos.y = prePos.y + maxHeight;
        velocity.y = 0;
    }

}
