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
const std::array<std::pair<Vector2<int>, Vector2<int>>, 8> Table<TABLE_SIZE>::specialCases{{
    {{1, 2}, {0, 0}},
    {{2, 1}, {0, 0}},
    {{1, TABLE_SIZE.y - 3}, {0, TABLE_SIZE.y - 1}},
    {{2, TABLE_SIZE.y - 2}, {0, TABLE_SIZE.y - 1}},
    {{TABLE_SIZE.x - 2, TABLE_SIZE.y - 3}, {TABLE_SIZE.x - 1, TABLE_SIZE.y - 1}},
    {{TABLE_SIZE.x - 3, TABLE_SIZE.y - 2}, {TABLE_SIZE.x - 1, TABLE_SIZE.y - 1}},
    {{TABLE_SIZE.x - 2, 2}, {TABLE_SIZE.x - 1, 0}},
    {{TABLE_SIZE.x - 3, 1}, {TABLE_SIZE.x - 1, 0}},
}};

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

template <Vector2<int> TABLE_SIZE>
bool Table<TABLE_SIZE>::recCalculator(Node node) {
	if (node.step >= TABLE_SIZE.x * TABLE_SIZE.y - 1) {
		PrintScreen(node);
		return true;
	}

	std::size_t foundIndex = 0;
	for (; foundIndex < specialCases.size(); foundIndex++)
		if (specialCases[foundIndex].first == node.pos) {
			if (CanMove(node, specialCases[foundIndex].second))
				return recCalculator({&node, specialCases[foundIndex].second, node.step + 1});
			break;
		}

	for (auto &addPos : Node::movableArea) {
		Vector2<int> pos{node.pos.x + addPos.x, node.pos.y + addPos.y};
		if (CanMove(node, pos) && recCalculator({&node, pos, node.step + 1}))
			return true;
	}
	return false;
}
