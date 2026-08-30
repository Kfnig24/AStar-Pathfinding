#pragma once
#include <string>
#include "raylib.h"

class Window {
private:
  Vector2 windowSize;
  std::string title;

  Font roboto;

  void Draw();
  void Update();

public:
  Window(Vector2 &size, std::string &w_title); 
  void Loop();
  void Close();
};