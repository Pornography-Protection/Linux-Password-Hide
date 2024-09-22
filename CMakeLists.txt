cmake_minimum_required(VERSION 3.0)

project(key_gen_normal LANGUAGES CXX)
add_executable(key_gen_normal key_gen_normal.cpp
                              utils.hpp
                              utils.cpp)
target_link_libraries(key_gen_normal)

add_executable(key_gen_timed key_gen_timed.cpp
                             utils.hpp
                             utils.cpp)
target_link_libraries(key_gen_timed)
