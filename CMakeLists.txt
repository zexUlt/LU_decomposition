cmake_minimum_required(VERSION 3.10)
project(diffeq_practice2020_task2 C)

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME} main_lss_17_09.c lss_17_09.c lss_17_09.h)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME exe)