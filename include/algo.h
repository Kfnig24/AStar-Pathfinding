#pragma once
#include <array>
#include <queue>
#include <vector>
#include <concepts>

enum class NodeState { EMPTY, WALL, START, TARGET, OPEN, CLOSED };

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

float manhattanDistance(Positionable auto* start, Positionable auto* target);

auto compare = [](const Node *a, const Node *b) { return a->f > b->f; };

using OpenSet =
    std::priority_queue<Node *, std::vector<Node *>, decltype(compare)>;

class Algorithm {
private:
  std::vector<Node> &grid;
  OpenSet openSet;
  std::vector<Node *> closedSet;

  const Node *target;

  bool isRunning = true;
  const int &nb_col;
  const int &nb_row;

  void GetNeighbors(const Node *currentNode, std::vector<Node*>& neighbors);

public:
  Algorithm(std::vector<Node> &m_grid, const int &m_nb_col, const int &m_nb_row, Node *startNode,
            Node *targetNode);
  void Run();
};