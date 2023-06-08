#include <chrono>

#include "Table.hpp"

int main() {
	auto start = std::chrono::system_clock::now();
	{
		Table<Vector2<int>(8, 8)> table;
		table.CalculatePath({7, 7});
	}
	auto now = std::chrono::system_clock::now();
	std::chrono::duration<float> elapsed_seconds = now - start;
	std::cout << elapsed_seconds.count() << "s" << std::endl;
}
