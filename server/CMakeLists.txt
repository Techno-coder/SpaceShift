cmake_minimum_required(VERSION 3.6)
project(SpaceShiftServer)

set(CMAKE_CXX_STANDARD 14)

FILE(GLOB_RECURSE SOURCE_FILES
		src/*.hpp
		src/*.cpp)

FILE(GLOB_RECURSE SHARED_FILES
		../shared/*.hpp
		../shared/*.cpp)

if (APPLE)
	set(CMAKE_CXX_COMPILER_ID AppleClang)
endif ()

if (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/conan.cmake")
	message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
	file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
			"${CMAKE_CURRENT_BINARY_DIR}/conan.cmake")
endif ()

include(${CMAKE_CURRENT_BINARY_DIR}/conan.cmake)

conan_cmake_run(CONANFILE conanfile.txt BASIC_SETUP ${PROJECT_NAME} BUILD missing)
set(CMAKE_SKIP_RPATH OFF)

include_directories(../shared)
include_directories(${CONAN_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${SHARED_FILES})

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
