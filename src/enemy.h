#ifndef ENEMY_H
#define ENEMY_H

#include "SDL.h"
#include "snake.h"
#include <vector>

class Enemy : public Snake {
public:
  Enemy(int grid_width, int grid_height) : Snake(grid_width, grid_height) {
    atFood = false;
    points = 0;
  }

  Snake::Direction FindDirection(int foodX,
                                 int foodY); // checks which way to go

  // getters and setters
  void Autopilot(SDL_Point food); // sets the direction to the snake
  void SetSpeed(float _speed);    // set speed for enemy snake

  bool CheckFood() const; // gets if the snake is at the food location
  void SetFood(bool state);

  void KoEnemy(); // reduces the enemy snake to only head
  int GetPoints() const;
  void SetPoints(int value);

private:
  bool atFood;
  int points;
};

#endif