#pragma once

#include <string>

class FilePath {
	const std::string resourcesPath = "resources/";

	const std::string internal;
public:
	explicit FilePath(const std::string& filePath);
	operator const std::string&() const;
};

