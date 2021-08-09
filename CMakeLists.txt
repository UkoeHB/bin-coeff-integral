######################################
#cmake setup

cmake_minimum_required(VERSION 3.13)


######################################
#project setup

project(BinCoeffIntegral
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)


######################################
#config

# binary directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")

# set to Release unless otherwise specified
include(SetDefaultBuildType)


######################################
#packages

find_package(Boost 1.58 QUIET)


######################################
#process targets

add_subdirectory(Sources)