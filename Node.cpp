#include "Node.hpp"

const std::array<Vector2<int>, 8> Node::movableArea{
    {{2, 1}, {1, 2}, {-2, 1}, {-1, 2}, {2, -1}, {1, -2}, {-2, -1}, {-1, -2}}};