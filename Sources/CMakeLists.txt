######################################
#create executable

set(TEST_SOURCES
    math.cpp
    test.cpp
    main.cpp)

add_subdirectory(Utility)

add_executable(test ${TEST_SOURCES})

target_link_libraries(test PRIVATE Utility)
target_include_directories(test PRIVATE ${Boost_INCLUDE_DIRS})
