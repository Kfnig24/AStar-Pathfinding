#include "algo.h"
#include <array>

using namespace std;

float manhattanDistance(Positionable auto *start, Positionable auto *target) {
  return abs(target->x - start->x) + abs(target->y - start->y);
}

void Algorithm::GetNeighbors(const Node *currentNode,
                             vector<Node *> &neighbors) {

  constexpr array<int, 4> dx = {1, 0, -1, 0};
  constexpr array<int, 4> dy = {0, -1, 0, 1};

  for (int i(0); i < 4; i++) {
    int nx = currentNode->x + dx[i];
    int ny = currentNode->y + dy[i];

    if (nx >= 0 && nx < nb_col && ny >= 0 && ny < nb_row) {
      Node *neighbor = &grid[ny * nb_col + nx];

      if (neighbor->state != NodeState::WALL) {
        neighbors.push_back(neighbor);
      }
    }
  }
}

void Algorithm::Algo() {
  using enum NodeState;

  if (previousNode != nullptr && previousNode->state != START)
    previousNode->state = CLOSED;

  if (openSet.empty())
    return;

  Node *node = openSet.top();
  openSet.pop();
  if (node->state == CLOSED)
    return;
  if (node == target) {
    isPathfinding = false;
    isBacktracking = true;
    return;
  }

  closedSet.push_back(node);
  if (node->state != START)
    node->state = CURRENT;

  vector<Node *> neighbors;
  neighbors.reserve(4);
  GetNeighbors(node, neighbors);

  for (Node *neighbor : neighbors) {
    if (neighbor->state == CLOSED || neighbor->state == START)
      continue;

    int g_temp = node->g + 1;
    if (neighbor->state == OPEN && neighbor->g < g_temp)
      continue;
    neighbor->g = g_temp;
    neighbor->parent = node;
    neighbor->h = manhattanDistance(neighbor, target);
    neighbor->f = g_temp + neighbor->h;
    neighbor->state = neighbor->state != TARGET ? OPEN : TARGET;
    openSet.push(neighbor);
  }
  previousNode = node;
}

void Algorithm::Backtrack() {
  using enum NodeState;
  if (pathNode == nullptr)
    pathNode = target;

  if (!(pathNode->state == TARGET || pathNode->state == START))
    pathNode->state = NodeState::PATH;
  pathNode = pathNode->parent;
}

Algorithm::Algorithm(vector<Node> &m_grid, const int &m_nb_col,
                     const int &m_nb_row, Node *startNode, Node *targetNode)
    : grid(m_grid), openSet(compare), target(targetNode), nb_col(m_nb_col),
      nb_row(m_nb_row) {
  openSet.push(startNode);
  previousNode = nullptr;
  pathNode = nullptr;
}

void Algorithm::Run() {
  using enum NodeState;
  if (!isRunning)
    return;

  if (isPathfinding && !isBacktracking)
    Algo();

  if (!isPathfinding && isBacktracking)
    Backtrack();
}