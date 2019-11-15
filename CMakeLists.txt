cmake_minimum_required( VERSION 2.8 )

project(TaskRaider)
file(GLOB MAIN_SRC "src/*.cpp" "src/*.hpp")
add_executable( TaskRaider ${MAIN_SRC} )

