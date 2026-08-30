#pragma once
#include <string>
#include "raylib.h"
#include <vector>
#include "algo.h"

class Window {
private:
  Vector2 windowSize;
  std::string title;
  double squareSize;
  std::vector<std::vector<Node>> nodes;

  Font roboto;

  void Draw();
  void Update();

  void GenerateNodes();
public:
  Window(Vector2 &size, std::string &w_title, double &m_squareSize); 
  void Loop();
  void Close();
};