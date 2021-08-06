add_library(Utility STATIC exception_assert.cpp string_utils.cpp)

target_include_directories(Utility PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})