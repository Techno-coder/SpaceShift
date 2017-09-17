#pragma once

#include "../../../shared/utility/MatrixVector.hpp"

MatrixVector<int> getSquareMap(int width, int height) {
	MatrixVector<int> map;
	for (int y = 0; y < height; ++y) {
		std::vector<int> row;
		for (int x = 0; x < width; ++x) {
			if (x == 0 && y == 0) row.push_back(1);
			else if (x == 0 && y == height - 1) row.push_back(7);
			else if (x == 0) row.push_back(8);
			else if (x == width - 1 && y == 0) row.push_back(3);
			else if (x == width - 1 && y == height - 1) row.push_back(5);
			else if (x == width - 1) row.push_back(4);
			else if (y == 0) row.push_back(2);
			else if (y == height - 1) row.push_back(6);
			else row.push_back(0);
		}
		map.push_back(row);
	}
	return map;
}
