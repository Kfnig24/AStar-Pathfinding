#pragma once
#include <array>
#include <concepts>
#include <iostream>
#include <queue>
#include <vector>

#define PRINT_DEBUG(fmt, ...)                                                  \
  std::cout << "[DEBUG] " << std::format(fmt, ##__VA_ARGS__) << endl

enum class NodeState { EMPTY, WALL, START, TARGET, OPEN, CLOSED, CURRENT, PATH, BLOCKED };

struct Node {
  int x;
  int y;
  double f = 0.0f;
  double g = 0.0f;
  double h = 0.0f;

  NodeState state;
  Node *parent;

  Node(int x, int y, NodeState state = NodeState::EMPTY)
      : x(x), y(y), state(state) {}
};

template <typename T>
concept Positionable = requires(T a) {
  { a.x } -> std::convertible_to<float>;
  { a.y } -> std::convertible_to<float>;
};

float manhattanDistance(Positionable auto *start, Positionable auto *target);

auto compare = [](const Node *a, const Node *b) { 
    if (abs(a->f - b->f) < 0.001f) return a->h > b->h;
    return a->f > b->f; 
};

using OpenSet =
    std::priority_queue<Node *, std::vector<Node *>, decltype(compare)>;

class Algorithm {
private:
  std::vector<Node> &grid;
  OpenSet openSet;
  std::vector<Node *> closedSet;

  Node *target;
  Node *previousNode;
  Node* pathNode;

  bool isRunning = true;
  bool isPathfinding = true;
  bool isBacktracking = false;
  bool won = false;
  const int &nb_col;
  const int &nb_row;

  void GetNeighbors(const Node *currentNode, std::vector<Node *> &neighbors);

  void Algo();
  void Backtrack();

public:
  Algorithm(std::vector<Node> &m_grid, const int &m_nb_col, const int &m_nb_row,
            Node *startNode, Node *targetNode);
  void Run();
};