#pragma once

enum class NodeState { EMPTY, WALL, START, TARGET };

struct Node {
  int x;
  int y;

  NodeState state = NodeState::EMPTY;
};