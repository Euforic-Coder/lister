cmake_minimum_required (VERSION 2.8.11)
project (uforia)

add_executable(test main.cpp)

add_library(colored colored.h)
add_library(from from.h)
add_library(has has.h)
add_library(messages messages.h)
add_library(random random.h)
add_library(strings strings.h)
add_library(helpmaker helpmaker.h)
add_library(uforia uforia.h)

foreach(target IN ITEMS colored from has messages random strings helpmaker uforia)
	set_target_properties(${target} PROPERTIES LINKER_LANGUAGE CXX)
endforeach()

target_link_libraries(test uforia)
