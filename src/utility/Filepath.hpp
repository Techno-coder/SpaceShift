#pragma once

#include <string>

class Filepath {
	const std::string resourcesPath = "resources/";

	const std::string internal;
public:
	explicit Filepath(const std::string& filePath);
	operator const std::string&() const;
};

