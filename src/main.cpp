#include <iostream>
#include <memory>
#include <string>
#include "window.h"

using namespace std;

Vector2 WINDOW_SIZE = Vector2(800.0, 600.0);
string TITLE = "A* Pathfinder";
double SQUARE_SIZE = 10.0;

int main() {
    Window win = Window(WINDOW_SIZE, TITLE, SQUARE_SIZE);
    win.Loop();
    win.Close();
    return 0;
}