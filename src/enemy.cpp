#include "enemy.h"
#include <cmath>
#include <iostream>

// finds the correct direction for the snake but it doesn't consider the snake's
// body
Snake::Direction Enemy::FindDirection(int foodX, int foodY) {

  int new_x = static_cast<int>(head_x);
  int new_y = static_cast<int>(head_y);

  if (abs(new_y - foodY) > 0.1) {
    if (new_y > foodY)
      return Direction::kUp;
    else if (new_y < foodY)
      return Direction::kDown;
    else
      return direction;
  } else if (abs(new_x - foodX) > 0.1) {
    if (new_x > foodX)
      return Direction::kLeft;
    else if (new_x < foodX)
      return Direction::kRight;
    else
      return direction;
  } else {
    if (new_x == foodX && new_y == foodY) {
      SetFood(true);
      points++;
      return direction;
    } else
      return direction;
  }
}

// sets the direction of the snake to "point at the food"
void Enemy::Autopilot(SDL_Point food) {
  direction = FindDirection(food.x, food.y);
}

void Enemy::SetSpeed(float _speed) { speed = _speed; }

bool Enemy::CheckFood() const { return atFood; }

void Enemy::SetFood(bool state) { atFood = state; }

// clears the body of the enemy but keeps the head
void Enemy::KoEnemy() { body.clear(); }

int Enemy::GetPoints() const { return points; }

void Enemy::SetPoints(int value) { points = value; }