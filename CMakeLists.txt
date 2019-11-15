cmake_minimum_required( VERSION 2.8 )
project(TaskRaider)

file(GLOB TASKDB_SRC "src/TaskDB/*.cpp" "src/TASKDB/*.hpp")
add_library( taskdb STATIC ${TASKDB_SRC} )

file(GLOB MAIN_SRC "src/*.cpp" "src/*.hpp")
add_executable( TaskRaider ${MAIN_SRC} )
target_link_libraries(TaskRaider taskdb)

