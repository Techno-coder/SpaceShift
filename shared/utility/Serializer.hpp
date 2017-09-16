#pragma once

#include "MatrixVector.hpp"

#include <string>
#include <sstream>

template <typename T>
std::string serialize(const MatrixVector<T>& matrixVector) {
	std::string str;
	for (const auto& line : matrixVector) {
		for (auto value : line) {
			str += std::to_string(value) + " ";
		}
		str.push_back('\n');
	}
	return str;
}
