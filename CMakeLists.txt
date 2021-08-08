######################################
#cmake setup

cmake_minimum_required(VERSION 3.20)


######################################
#project setup

project(BinCoeffIntegral
	LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)


######################################
#config

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


######################################
#packages

find_package(Boost 1.58 QUIET)


######################################
#process targets

add_subdirectory(Sources)