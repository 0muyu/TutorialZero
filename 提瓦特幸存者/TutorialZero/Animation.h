#pragma once

#include <easyx.h>

#include "Atlas.h"
#include "utls.h"

class Animation {
 private:
  int timer = 0;
  int idx_frame = 0;
  int interval_ms = 0;
  Atlas* anim_atlas;

 public:
  Animation(Atlas* atlas, int interval):anim_atlas(atlas),interval_ms(interval) {
    
  }

  ~Animation() = default;

  void Play(int x, int y, int delta) {
    timer += delta;
    if (timer >= interval_ms) {
      idx_frame = (idx_frame + 1) % anim_atlas->frame_list.size();
      timer = 0;
    }

    putimage_alpha(x, y, anim_atlas->frame_list[idx_frame]);
  }
};
