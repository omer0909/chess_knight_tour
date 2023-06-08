#pragma once
#include <iostream>

template <typename T>
class Vector2 {
   public:
	constexpr inline Vector2(int x_, int y_) : x(x_), y(y_) {}
	int x;
	int y;

	inline bool operator<(Vector2 const &other) const {
		return x * y < other.x * other.y;
	}

	inline bool operator==(Vector2 const &other) const {
		return x == other.x && y == other.y;
	}

	inline bool operator!=(Vector2 const &other) const {
		return x != other.x || y != other.y;
	}

	friend std::ostream &operator<<(std::ostream &out, Vector2 const &value) {
		out << "{" << value.x << ", " << value.y << "}";
		return out;
	}
};
