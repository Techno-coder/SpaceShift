#pragma once

#include "Filepath.hpp"

#include <vector>
#include <fstream>
#include <sstream>

template <typename T>
std::vector<std::vector<T>> tokenise(const Filepath& filePath) {
	std::vector<std::vector<T>> tokens;
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
