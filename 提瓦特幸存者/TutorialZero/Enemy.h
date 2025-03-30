#pragma once

#include <graphics.h>

#include "Animation.h"
#include "Bullet.h"
#include "Player.h"
#include "utls.h"

class Enemy {
 public:

  const int SPEED = 2;
  const int FRAME_WIDTH = 80;   // 敌人宽度
  const int FRAME_HEIGHT = 80;  // 敌人高度
  const int SHADOW_WIDTH = 48;  // 阴影宽度


  IMAGE img_shadow;
  Animation* anim_left;
  Animation* anim_right;
  POINT position = {0, 0};
  bool facing_left = false;
  bool alive = true;


  Enemy() {
    loadimage(&img_shadow, _T("img/shadow_enemy.png"));
    anim_left = new Animation(atlas_enemy_left, 45);
    anim_right = new Animation(atlas_enemy_right, 45);

    // 敌人生成边界
    enum class SpawnEdge { Up = 0, Down, Left, Right };

    // 将敌人放置在地图外边界处的随机位置
    SpawnEdge edge = (SpawnEdge)(rand() % 4);
    switch (edge) {
      case SpawnEdge::Up:
        position.x = rand() % WINDOW_WIDTH;
        position.y = -FRAME_HEIGHT;
        break;
      case SpawnEdge::Down:
        position.x = rand() % WINDOW_WIDTH;
        position.y = WINDOW_HEIGHT;
        break;
      case SpawnEdge::Left:
        position.x = -FRAME_WIDTH;
        position.y = rand() % WINDOW_HEIGHT;
        break;
      case SpawnEdge::Right:
        position.x = WINDOW_WIDTH;
        position.y = rand() % WINDOW_HEIGHT;
        break;
      default:
        break;
    }
  }

  ~Enemy() {
    delete anim_left;
    delete anim_right;
  }

  bool CheckBulletCollision(const Bullet& bullet) {
    // 将子弹等效为点，判断点是否在敌人矩形内
    bool is_overlap_x = bullet.position.x >= position.x &&
                        bullet.position.x <= position.x + FRAME_WIDTH;
    bool is_overlap_y = bullet.position.y >= position.y &&
                        bullet.position.y <= position.y + FRAME_HEIGHT;
    return is_overlap_x && is_overlap_y;
  }

  bool CheckPlayerCollision(const Player& player) {
    // 将敌人中心位置等效为点，判断点是否在玩家矩形内
    POINT check_position = {position.x + FRAME_WIDTH / 2,
                            position.y + FRAME_HEIGHT / 2};
    const POINT& player_position = player.GetPosition();
    bool is_overlap_x =
        check_position.x >= player_position.x &&
        check_position.x <= player_position.x + player.FRAME_WIDTH;
    bool is_overlap_y =
        check_position.y >= player_position.y &&
        check_position.y <= player_position.y + player.FRAME_HEIGHT;
    return is_overlap_x && is_overlap_y;
  }

  void Move(const Player& player) {
    const POINT& player_position = player.GetPosition();
    int dir_x = player_position.x - position.x;
    int dir_y = player_position.y - position.y;
    double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);
    if (len_dir != 0) {
      double normalized_x = dir_x / len_dir;
      double normalized_y = dir_y / len_dir;
      position.x += (int)(SPEED * normalized_x);
      position.y += (int)(SPEED * normalized_y);
    }

    if (dir_x < 0)
      facing_left = true;
    else if (dir_x > 0)
      facing_left = false;
  }

  void Draw(int delta) {
    int pos_shadow_x = position.x + (FRAME_WIDTH / 2 - SHADOW_WIDTH / 2);
    int pos_shadow_y = position.y + FRAME_HEIGHT - 35;
    putimage_alpha(pos_shadow_x, pos_shadow_y, &img_shadow);

    if (facing_left)
      anim_left->Play(position.x, position.y, delta);
    else
      anim_right->Play(position.x, position.y, delta);
  }

  void Hurt() { alive = false; }

  bool CheckAlive() { return alive; }
};
