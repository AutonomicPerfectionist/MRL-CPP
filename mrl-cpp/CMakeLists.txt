# Specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8)
project(mrl-cpp)
# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}/include")


add_executable(mrl-cpp ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_sources(mrl-cpp
	PRIVATE
		"${PROJECT_SOURCE_DIR}/src/MCommand.cpp"
)
target_link_libraries(mrl-cpp
	PRIVATE	
		"pthread"
)
