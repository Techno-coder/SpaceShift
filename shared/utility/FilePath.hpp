#pragma once

#include "ExecutablePath.hpp"

class FilePath {
#ifdef __APPLE__
	const std::string resourcesPath = getExecutablePath().erase(getExecutablePath().find_last_of('/') - 5) + "Resources/";
#else
	const std::string resourcesPath = "Resources/";
#endif
	const std::string internal;
public:
	explicit FilePath(const std::string& filePath);
	operator const std::string&() const;
};

