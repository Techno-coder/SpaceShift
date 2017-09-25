#pragma once

#ifdef __APPLE__
#include <mach-o/dyld.h>
#include <sys/param.h>
#include <cassert>
#elif _WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>
#include <cstdio>
#include <algorithm>
#endif

#include <string>

inline std::string getExecutablePath() {
#ifdef __APPLE__
	char exe_path[MAXPATHLEN];
	char link_path[MAXPATHLEN];
	uint32_t size = sizeof(exe_path);
	if (_NSGetExecutablePath(exe_path, &size) != 0) static_assert("Path not found", "");
	if (realpath(exe_path, link_path) == nullptr) static_assert("Path not found", "");
	return std::string(link_path);
#elif _WIN32
	char pBuf[MAX_PATH];
	int bytes = GetModuleFileName(NULL, pBuf, MAX_PATH);
	if(bytes == 0) static_assert("Path not found", "");
	else return std::string(pBuf);
#elif __linux__
	char pBuf[4096];
	char szTmp[32];
	sprintf(szTmp, "/proc/%d/exe", getpid());
	int bytes = std::min(readlink(szTmp, pBuf, 4096), (long int) 4096 - 1);
	if(bytes >= 0) pBuf[bytes] = '\0';
	return std::string(pBuf);
#endif
}