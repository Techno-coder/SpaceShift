#pragma once

#include "FilePath.hpp"

#include <vector>
#include <fstream>
#include <sstream>

template <typename T>
using MatrixVector = std::vector<std::vector<T>>;

template <typename T>
MatrixVector<T> tokenize(const FilePath& filePath) {
	MatrixVector<T> tokens;
	std::ifstream in(filePath);
	if (!in.good()) return tokens;
	std::string lineString;
	while (std::getline(in, lineString)) {
		std::istringstream line(lineString);
		std::vector<T> lineTokens;
		T token;
		while (line >> token) {
			lineTokens.emplace_back(token);
		}
		tokens.push_back(lineTokens);
	}
	return tokens;
}
