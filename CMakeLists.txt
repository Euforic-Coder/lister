cmake_minimum_required (VERSION 2.8.11)
project (lister)

add_subdirectory(uforia)
add_executable(lister main.cpp)

target_link_libraries(lister uforia)
