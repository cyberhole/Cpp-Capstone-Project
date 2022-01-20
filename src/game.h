#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "controller.h"
#include "enemy.h"
#include "renderer.h"
#include "snake.h"
#include <memory>
#include <random>

class Game {
public:
  Game(std::size_t grid_width, std::size_t grid_height);
  ~Game();

  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration, int highScore);
  int GetScore() const;
  int GetSize() const;
  void SetScore();

private:
  Snake snake;

  std::unique_ptr<Enemy> _enemy; // enemy snake
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void KillEnemy();
  void KilledByEnemy();

  void PlaceFood();
  void Update();
};

#endif