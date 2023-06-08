#pragma once

#include "Node.hpp"
#include "Vector2.hpp"

template <Vector2<int> TABLE_SIZE>
class Table {
   public:
	Table();
	void CalculatePath(Vector2<int> const &startPos = {0, 0});

   private:
	static const std::array<std::pair<Vector2<int>, Vector2<int>>, 8> specialCases;
	bool CanMove(Node const &node, Vector2<int> const &pos);
	void PrintScreen(Node const &node);
	bool recCalculator(Node node);
};

#include "Table.cpp"
