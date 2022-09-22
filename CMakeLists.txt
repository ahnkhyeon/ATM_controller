cmake_minimum_required(VERSION 3.10)

project(
	ATMController
	VERSION 0.1
	DESCRIPTION "ATM Controller simulator"
	LANGUAGES CXX)


add_executable (program ATM_controller.cc account_handler.cc account.cc)

target_include_directories(program PUBLIC ${CMAKE_SOURCE_DIR}/includes)

target_compile_options(program PUBLIC -std=c++17)

target_link_libraries(program PRIVATE pthread)
