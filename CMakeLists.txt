# Main CMakeLists file

cmake_minimum_required(VERSION 2.8)

project(libholdem)
add_subdirectory(src)
add_subdirectory(test)
enable_testing()
