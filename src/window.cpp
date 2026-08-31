#include "window.h"

using namespace std;

Node *Window::getNodeFromWorldPos(float x, float y) {
  int gridX = static_cast<int>(x / squareSize);
  int gridY = static_cast<int>(y / squareSize);

  if (gridX >= 0 && gridX < nb_col && gridY >= 0 && gridY < nb_row)
    return &nodes[gridY * nb_col + gridX];
  return nullptr;
}

void Window::Draw() {
  using enum NodeState;
  ClearBackground(RAYWHITE);

  for (const Node &node : nodes) {
    Color color = WHITE;

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
    case EMPTY:
      color = LIGHTGRAY;
      break;
    case OPEN:
      color = BLUE;
      break;
    case CLOSED:
      color = YELLOW;
      break;
    case CURRENT:
      color = PURPLE;
      break;
    }

    DrawRectangle(node.x * squareSize, node.y * squareSize, squareSize,
                  squareSize, color);
  }
}

void Window::Update() {
  HandleInput();

  if (alg.has_value()) {
    alg->Run();
  }
}

void Window::HandleInput() {
  using enum NodeState;
  Vector2 mousePos = GetMousePosition();

  //   -- KEYBOARD --
  if (IsKeyPressed(KEY_R)) {
    GenerateNodes();
    startNode = nullptr;
    targetNode = nullptr;
  }

  if (IsKeyPressed(KEY_S) && startNode != nullptr && targetNode != nullptr &&
      !alg.has_value()) {
    alg.emplace(nodes, nb_col, nb_row, startNode, targetNode);
  }

  // -- MOUSE --
  if (startNode == nullptr || targetNode == nullptr) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      Node *node = getNodeFromWorldPos(mousePos.x, mousePos.y);
      if (node == nullptr)
        return;
      node->state = startNode == nullptr ? START : TARGET;
      if (startNode == nullptr)
        startNode = node;
      else
        targetNode = node;
    }
    return;
  }

  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    Node *node = getNodeFromWorldPos(mousePos.x, mousePos.y);
    if (node == nullptr)
      return;
    if (node->state == START || node->state == TARGET)
      return;
    node->state = WALL;
  }
}

void Window::GenerateNodes() {
  startNode = nullptr;
  targetNode = nullptr;

  alg.reset();
  nodes.clear();

  for (int i(0); i < nb_col * nb_row; i++) {
    NodeState state = NodeState::EMPTY;
    int x = i % nb_col;
    int y = i / nb_col;
    if (x == 0 || x == (nb_col - 1) || y == 0 || y == (nb_row - 1))
      state = NodeState::WALL;
    nodes.emplace_back(x, y, state);
  }
}

Window::Window(Vector2 &size, string &w_title, double &m_squareSize)
    : windowSize(size), title(w_title), squareSize(m_squareSize) {
  nb_col = windowSize.x / squareSize;
  nb_row = windowSize.y / squareSize;
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(windowSize.x, windowSize.y, title.c_str());
  SetTargetFPS(60);

  nodes.reserve(nb_col * nb_row);
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