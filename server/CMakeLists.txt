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

conan_cmake_run(REQUIRES sfml/2.4.0@diego_stamigni/stable BASIC_SETUP BUILD missing)

include_directories(../shared)
include_directories(${CONAN_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${SHARED_FILES})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-network sfml-system Threads::Threads)
