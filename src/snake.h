#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL2/SDL.h"

class Snake {
 public:
  // The direction that snake will travel
  enum class Direction { kUp, kDown, kLeft, kRight };

  // Snake() constructor
  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  // Method for updating the snake during each path 
  void Update();
  
  // Method to grow the body of snake once it eats food
  void GrowBody();
  bool SnakeCell(int x, int y);

  // Initial snake traveling direction
  Direction direction = Direction::kUp;

  // Snake properties defined
  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:

  // Once Update() method is called, it will call UpdatedHead() to update coordinate of head during each path loop
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif