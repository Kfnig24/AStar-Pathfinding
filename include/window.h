#pragma once
#include <string>
#include <iostream>
#include <optional>
#include "raylib.h"
#include <vector>
#include <format>
#include "algo.h"

#define PRINT_DEBUG(fmt, ...) std::cout << "[DEBUG] " << std::format(fmt, ##__VA_ARGS__) << endl

class Window {
private:
  Vector2 windowSize;
  int nb_col;
  int nb_row;
  std::string title;
  double squareSize;
  std::vector<Node> nodes;

  std::optional<Algorithm> alg;

  Node* startNode;
  Node* targetNode;

  Node* getNodeFromWorldPos(float x, float y);

  void Draw();
  void Update();

  void HandleInput();

  void GenerateNodes();
public:
  Window() = default;
  Window(Vector2 &size, std::string &w_title, double &m_squareSize); 
  void Loop();
  void Close();
};