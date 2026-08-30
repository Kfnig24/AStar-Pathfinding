#include "window.h"

using namespace std;

void Window::Draw() {
  using enum NodeState;
  ClearBackground(RAYWHITE);

  for (const vector<Node> &row : nodes) {
    for (const Node &node : row) {
      Color color = LIGHTGRAY;

      switch (node.state) {
      case WALL:
        color = DARKGRAY;
        break;
      case START:
        color = GREEN;
        break;
      case TARGET:
        color = RED;
        break;
      }

      DrawRectangle(node.x * squareSize, node.y * squareSize, squareSize,
                    squareSize, color);
    }
  }
}

void Window::Update() {}

void Window::GenerateNodes() {
  int nb_col = windowSize.x / squareSize;
  int nb_row = windowSize.y / squareSize;

  for (int i(0); i < nb_row; i++) {
    vector<Node> row;
    for (int j(0); j < nb_col; j++) {
      Node node = Node(j, i);

      if (i == 0 || i == (nb_row - 1) || j == 0 || j == (nb_col - 1))
        node.state = NodeState::WALL;

      row.push_back(node);
    }
    nodes.push_back(row);
  }
}

Window::Window(Vector2 &size, string &w_title, double &m_squareSize)
    : windowSize(size), title(w_title), squareSize(m_squareSize) {
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(windowSize.x, windowSize.y, title.c_str());
  SetTargetFPS(60);

  GenerateNodes();

  roboto = LoadFont("resources/Roboto.ttf");
}

void Window::Loop() {
  while (!WindowShouldClose()) {
    Update();

    BeginDrawing();
    Draw();
    EndDrawing();
  }
}

void Window::Close() { CloseWindow(); }