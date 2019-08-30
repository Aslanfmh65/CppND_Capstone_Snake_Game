#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {

  // Capture the head coordinate cell before updating
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  

  UpdateHead();

  // Capture the head's cell after updating.
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

// In SDL the origin is located at upper left corner. So when snake goes Up and Left,
// the coordinate is aheading down; when snake goes Down and Right, the coordinates
// is aheading up

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen
  // fmod(numer, denom), return the floating-point remainder
  // If the head x/y coordinate is bigger than grip, fmod returns the remainder
  head_x = fmod(head_x + grid_width, grid_width); 
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  // vector.push_back(element): add element at the end of vector
  body.push_back(prev_head_cell);

  // Add previous head to vector and remove the tail from vector is how we see
  // snake is moving

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    // If snake hit itself, it dies
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}