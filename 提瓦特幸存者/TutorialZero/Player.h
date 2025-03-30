#pragma once

#include <graphics.h>

#include <cmath>

#include "Animation.h"
#include "utls.h"

class Player {
 public:
  const int FRAME_WIDTH = 80;   // 玩家宽度
  const int FRAME_HEIGHT = 80;  // 玩家高度

  const int SPEED = 3;
  const int SHADOW_WIDTH = 32;  // 阴影宽度

  IMAGE img_shadow;
  Animation* anim_left;
  Animation* anim_right;
  POINT position = {500, 500};
  bool is_move_up = false;
  bool is_move_down = false;
  bool is_move_left = false;
  bool is_move_right = false;

 public:
  Player() {
    loadimage(&img_shadow, _T("img/shadow_player.png"));
    anim_left = new Animation(atlas_player_left, 45);
    anim_right = new Animation(atlas_player_right, 45);
  }

  ~Player() {
    delete anim_left;
    delete anim_right;
  }

  void ProcessEvent(const ExMessage& msg) {
    switch (msg.message) {
      case WM_KEYDOWN:
        switch (msg.vkcode) {
          case VK_UP:
            is_move_up = true;
            break;
          case VK_DOWN:
            is_move_down = true;
            break;
          case VK_LEFT:
            is_move_left = true;
            break;
          case VK_RIGHT:
            is_move_right = true;
            break;
        }
        break;

      case WM_KEYUP:
        switch (msg.vkcode) {
          case VK_UP:
            is_move_up = false;
            break;
          case VK_DOWN:
            is_move_down = false;
            break;
          case VK_LEFT:
            is_move_left = false;
            break;
          case VK_RIGHT:
            is_move_right = false;
            break;
        }
        break;
    }
  }

  void Move() {
    int dir_x = is_move_right - is_move_left;
    int dir_y = is_move_down - is_move_up;
    double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);
    if (len_dir != 0) {
      double normalized_x = dir_x / len_dir;
      double normalized_y = dir_y / len_dir;
      position.x += (int)(SPEED * normalized_x);
      position.y += (int)(SPEED * normalized_y);
    }

    if (position.x < 0) position.x = 0;
    if (position.y < 0) position.y = 0;
    if (position.x + FRAME_WIDTH > WINDOW_WIDTH)
      position.x = WINDOW_WIDTH - FRAME_WIDTH;
    if (position.y + FRAME_HEIGHT > WINDOW_HEIGHT)
      position.y = WINDOW_HEIGHT - FRAME_HEIGHT;
  }

  void Draw(int delta) {
    int pos_shadow_x = position.x + (FRAME_WIDTH / 2 - SHADOW_WIDTH / 2);
    int pos_shadow_y = position.y + FRAME_HEIGHT - 8;
    putimage_alpha(pos_shadow_x, pos_shadow_y, &img_shadow);

    static bool facing_left = false;
    int dir_x = is_move_right - is_move_left;
    if (dir_x < 0)
      facing_left = true;
    else if (dir_x > 0)
      facing_left = false;

    if (facing_left)
      anim_left->Play(position.x, position.y, delta);
    else
      anim_right->Play(position.x, position.y, delta);
  }

  const POINT& GetPosition() const { return position; }
};
