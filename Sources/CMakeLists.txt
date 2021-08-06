######################################
#create executable

set(MAIN_SOURCES
	main.cpp
	test.cpp
	math.cpp)

add_subdirectory(Utility)

add_executable(exe ${MAIN_SOURCES})

target_link_libraries(exe PRIVATE Utility)