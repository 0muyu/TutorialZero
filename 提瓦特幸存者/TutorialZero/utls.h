#pragma once

#include <graphics.h>
#include "Atlas.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

const int BUTTON_WIDTH = 192;
const int BUTTON_HEIGHT = 75;

        
inline void putimage_alpha(int x, int y, IMAGE* img) {
  int w = img->getwidth();
  int h = img->getheight();
  AlphaBlend(GetImageHDC(NULL), x, y, w, h, GetImageHDC(img), 0, 0, w, h,
             {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA});
}



Atlas* atlas_player_left; 
Atlas* atlas_player_right; 
Atlas* atlas_enemy_left; 
Atlas* atlas_enemy_right; 


bool running = true;
bool is_game_started = false;

