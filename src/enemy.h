#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include "SDL.h"
#include "snake.h"

class Enemy:public Snake {
 public:
 Enemy(int grid_width,int grid_height):Snake(grid_width,grid_height){}

 private:

};

#endif