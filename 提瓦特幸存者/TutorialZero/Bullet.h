#pragma once

#include <graphics.h>

class Bullet {
 public:
  const int RADIUS = 10;
  POINT position = {0, 0};

 public:
  Bullet() = default;
  ~Bullet() = default;

  void Draw() const {
    setlinecolor(RGB(255, 155, 50));
    setfillcolor(RGB(200, 75, 10));
    fillcircle(position.x, position.y, RADIUS);
  }
};
