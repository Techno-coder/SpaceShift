#include "FilePath.hpp"

FilePath::FilePath(const std::string& filePath) : internal(resourcesPath + filePath) {}

FilePath::operator const std::string&() const {
	return internal;
}
