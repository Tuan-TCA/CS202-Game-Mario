#pragma once

#include "GameObject.hpp"
#include "tileson.hpp"

#include "Player.hpp"

// Enum chứa loại item mà Question Block có thể chứa
enum class Contains { None = 0, Coin, Mushroom, FireFlower, Star, OneUp };

class Block : public GameObject {
public:
    int       gid;        // Global tile ID
    Texture2D texture;    // Texture trong sprite
    Rectangle srcRec;     // Khu vực cắt trong sprite

    bool      isSolid        = true;    //Có thể đi xuyên k (Mario đứng lên, va chạm)
    bool      isBreakable    = false;   //Có thể phá vỡ được (bricks, question block)
    bool      isQuestion     = false;   //Là ô dấu hỏi? hay ko
    bool      isInvisible    = false;   //true thì không vẽ (ví dụ Coin đã ăn rồi thì bật true)
    bool      isUsed         = false;   //Đã chạm vào chưa (Coin)
    Contains  contains       = Contains::None;  //Trong ô question chứa những thứ gì (Coin, Mushroom, Star,..)
    bool      isPipeEntrance = false;   //Đánh dấu nếu ống nước có đường bí mật
    bool      isFlagPole     = false;   //Đánh dấu cây cờ

    Block(int _gid, Vector2 _pos, Vector2 _size,
          Texture2D _tex, Rectangle _src)
      : GameObject(_pos, _size)
      , gid(_gid)
      , texture(_tex)
      , srcRec(_src)
    {}

    // Constructor tự động đọc tất cả property từ tson::Object
    Block(tson::Object &obj,
          Vector2 _pos, Vector2 _size,
          Texture2D _tex, Rectangle _src)
      : GameObject(_pos, _size)
      , gid(obj.getGid())
      , texture(_tex)
      , srcRec(_src)
    {
        // Dùng obj.get<T>(name, default) từ Tileson
        isSolid        = obj.get<bool>("isSolid");
        isBreakable    = obj.get<bool>("isBreakable");
        isQuestion     = obj.get<bool>("isQuestion");
        isInvisible    = obj.get<bool>("isInvisible");
        isUsed         = obj.get<bool>("isUsed");

        // containsItem trong Tiled lưu dưới dạng int
        {
            int iv = obj.get<int>("containsItem");
            contains = static_cast<Contains>(iv);
        }

        isPipeEntrance = obj.get<bool>("isPipeEntrance");
        isFlagPole     = obj.get<bool>("isFlagPole");
    }
    
    void update() override {
        
    }

    // Vẽ block
    void display() override {
        if (isInvisible && !isUsed) return;
        DrawTextureRec(texture, srcRec, getPosition(), WHITE);
    }

    void updateCollision(GameObject* other) override {
        // Character* character = dynamic_cast<Character*>(other);
        // if (!character) return;

        // if(other->getPosition().y > this->getFeet().y) {
        //     cout << "Feet\n";
        //     pos.y++;
        // }
    }
};
