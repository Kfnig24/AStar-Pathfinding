#include "window.h"
#include <raylib.h>

using namespace std;

void Window::Draw() {
  ClearBackground(RAYWHITE);

  Vector2 textSize = MeasureTextEx(roboto, title.c_str(), 25, 0.2);
  Vector2 textPos = Vector2((windowSize.x - textSize.x) / 2.0f,
                            (windowSize.y - textSize.y) / 2.0f);
  DrawTextEx(roboto, title.c_str(), textPos, 25, 0.2f, DARKBLUE);
}

void Window::Update() {}

Window::Window(Vector2 &size, string &w_title)
    : windowSize(size), title(w_title) {
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(windowSize.x, windowSize.y, title.c_str());
  SetTargetFPS(60);

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