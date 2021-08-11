######################################
#subdirectory as target

add_library(Utility OBJECT exception_assert.cpp string_utils.cpp)

target_include_directories(Utility PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
