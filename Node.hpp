#pragma once
#include <array>

#include "Vector2.hpp"

class Node {
 public:
  Node *parent;
  Vector2<int> pos;
  int step;
  static const std::array<Vector2<int>, 8> movableArea;
};
