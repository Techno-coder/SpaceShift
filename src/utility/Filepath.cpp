#include "Filepath.hpp"

Filepath::Filepath(const std::string& filePath) : internal(resourcesPath + filePath) {}

Filepath::operator const std::string&() {
	return internal;
}
