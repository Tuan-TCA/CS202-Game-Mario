#pragma once

#include "GameObject.hpp"
#include "tileson.hpp"

#include "Player.hpp"
#include <iostream>
using namespace std;

struct TSInfo { int firstgid, columns, margin, spacing; Vector2 tileSize; };

// Enum chứa loại item mà Question Block có thể chứa
enum class Contains { None = 0, Coin, Mushroom, FireFlower, Star, OneUp };

class Block : public GameObject {
public:
      int       gid;        // Global tile ID
      Texture2D texture;    // Texture trong sprite
      Rectangle srcRec;     // Khu vực cắt trong sprite

      vector<Rectangle> srcRecs; //Load srcRec
      float duration = 0.0f;
      float aniTimer = 0.0f;
      int aniIndex = 0;

      bool      isSolid        = false;    //Có thể đi xuyên k (Mario đứng lên, va chạm)
      bool      isBreakable    = false;   //Có thể phá vỡ được (bricks, question block)
      bool      isQuestion     = false;   //Là ô dấu hỏi? hay ko
      bool      isInvisible    = false;   //true thì không vẽ (ví dụ Coin đã ăn rồi thì bật true)
      bool      isUsed         = false;   //Đã chạm vào chưa (Coin)
      Contains  contains       = Contains::None;  //Trong ô question chứa những thứ gì (Coin, Mushroom, Star,..)
      bool      isPipeEntrance = false;   //Đánh dấu nếu ống nước có đường bí mật
      bool      isFlagPole     = false;   //Đánh dấu cây cờ

      Color color = WHITE;

      Block(int _gid, Vector2 _pos, Vector2 _size,
            Texture2D _tex, Rectangle _src);

      Block(tson::Tile* inforTile, Vector2 _pos, Vector2 _size,
                  Texture2D _tex, Rectangle _src, const TSInfo* tsi);

      Block(tson::Object &obj,
            Vector2 _pos, Vector2 _size,
            Texture2D _tex, Rectangle _src);

      void update() override;

      // Vẽ block
      void display() override;

      void updateCollision(GameObject* other, int type);

private:

      //Moving Block. Cần nghĩ cách xử lý khác cho những GameObject có Movement.
      void handleInput(float dt);
      void applyPhysics(float dt);
            // Physics & movement state
      Vector2 velocity;
      //static constexpr float speed     = 200.0f;  // pixels per second
      static constexpr float jumpForce = 200.0f;  // initial jump velocity
      static constexpr float gravity   = 900.0f;  // gravity acceleration
      static constexpr float maxHeight   = -8.0f;  
      bool onGround = true;
      //static constexpr int GroundY = 240;

      bool isJumping = false;
      const Vector2 prePos;
};