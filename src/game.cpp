#include "game.h"
#include <iostream>
#include "SDL.h"
#include "enemy.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  _enemy=std::make_unique<Enemy>(grid_width, grid_height);
  PlaceFood();
}

Game::~Game(){
  _enemy.reset();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration,int highScore) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();



    _enemy->SetSpeed(0.05);
    _enemy->Autopilot(food);




    renderer.Render(snake, food, *_enemy);
    Update();
    

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count,highScore);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)&&!_enemy->SnakeCell(x,y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;
  if (score>0)
  KilledByEnemy();
  KillEnemy();
  snake.Update();
  _enemy->Update();
  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);
  // Check if there's food over here
 if (_enemy->CheckFood()){
    PlaceFood();
   _enemy->SetFood(false);
   _enemy->GrowBody();
 }

  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    if (snake.speed<0.08)
    snake.speed += 0.02;
  }



}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; } // Grow snake and increase speed.
    

void Game::KillEnemy(){
if (snake.SnakeCell(_enemy->head_x,_enemy->head_y)){
SetScore();
_enemy->KoEnemy();
_enemy->SetPoints(0);}
}


void Game::SetScore(){
  score+=_enemy->GetPoints();
}

void Game::KilledByEnemy(){
if (_enemy->SnakeCell(snake.head_x,snake.head_y))
snake.alive=false;
}