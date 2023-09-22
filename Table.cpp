#include "Table.hpp"

#include <iostream>

// template class Table<Vector2<int>(7, 7)>;

template <Vector2<int> TABLE_SIZE>
Table<TABLE_SIZE>::Table() {}

template <Vector2<int> TABLE_SIZE>
void Table<TABLE_SIZE>::CalculatePath(Vector2<int> const &startPos) {
  recCalculator({nullptr, startPos, 0});
}

template <Vector2<int> TABLE_SIZE>
bool Table<TABLE_SIZE>::CanMove(Node const &node, Vector2<int> const &pos) {
  if (pos.x < 0 || pos.x >= TABLE_SIZE.x || pos.y < 0 || pos.y >= TABLE_SIZE.y)
    return false;

  Node const *it = node.parent;
  while (it != nullptr) {
    if (it->pos.x == pos.x && it->pos.y == pos.y)
      return false;
    it = it->parent;
  }
  return true;
}

template <Vector2<int> TABLE_SIZE>
void Table<TABLE_SIZE>::PrintScreen(Node const &node) {
  int table[TABLE_SIZE.x][TABLE_SIZE.y];

  Node const *it = &node;
  while (it != nullptr) {
    table[it->pos.x][it->pos.y] = it->step;
    it = it->parent;
  }

  int lineSize = TABLE_SIZE.x * 5 + 1;
  std::cout << std::string(lineSize, '-') << std::endl;
  for (int y = 0; y < TABLE_SIZE.y; y++) {
    for (int x = 0; x < TABLE_SIZE.x; x++)
      std::cout << "| " << table[x][y] << (table[x][y] < 10 ? "  " : " ");
    std::cout << "|" << std::endl
              << std::string(lineSize, '-') << std::endl;
  }
}

static float DistanceToCenter(Vector2<int> size, Vector2<int> pos) {
  Vector2<float> center{size.x * 0.5f, size.y * 0.5f};
  Vector2<float> diff{pos.x - center.x, pos.y - center.y};
  return diff.x * diff.x + diff.y * diff.y;
}

template <Vector2<int> TABLE_SIZE>
bool Table<TABLE_SIZE>::recCalculator(Node node) {
  if (node.step >= TABLE_SIZE.x * TABLE_SIZE.y - 1) {
    PrintScreen(node);
    return true;
  }

  std::array<bool, Node::movableArea.size()> selectedList;
  std::array<Vector2<int>, Node::movableArea.size()> poses;
  std::array<float, Node::movableArea.size()> distances;

  for (size_t i = 0; i < Node::movableArea.size(); i++) {
    poses[i] = {node.pos.x + Node::movableArea[i].x, node.pos.y + Node::movableArea[i].y};
    distances[i] = DistanceToCenter(TABLE_SIZE, poses[i]);
    selectedList[i] = !CanMove(node, poses[i]);
  }

  while (true) {
    float max = 0;
    int selected = -1;
    for (size_t j = 0; j < Node::movableArea.size(); j++) {
      if (!selectedList[j] && distances[j] >= max) {
        selected = j;
        max = distances[j];
      }
    }
    selectedList[selected] = true;
    if (selected == -1)
      return false;
    if (recCalculator({&node, poses[selected], node.step + 1}))
      return true;
  }
  return false;
}
