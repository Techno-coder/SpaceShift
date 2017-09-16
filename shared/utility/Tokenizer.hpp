#pragma once

#include "FilePath.hpp"
#include "MatrixVector.hpp"

#include <fstream>
#include <sstream>

template <typename T>
MatrixVector<T> tokenize(std::basic_istream<char>& str) {
	MatrixVector<T> tokens;
	std::string lineString;
	while (std::getline(str, lineString)) {
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

template <typename T>
MatrixVector<T> tokenize(const std::string& str) {
	std::istringstream all(str);
	return tokenize<T>(all);
}

template <typename T>
MatrixVector<T> tokenize(const FilePath& filePath) {
	MatrixVector<T> tokens;
	std::ifstream in(filePath);
	if (!in.good()) return tokens;
	return tokenize<T>(in);
}
