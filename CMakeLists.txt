cmake_minimum_required( VERSION 2.8 )
project(TaskRaider)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STADARD_REQUIRED True)

# General Setting
include_directories("src/")

# TaskDB Library
file(GLOB TASKDB_SRC "src/TaskDB/*.cpp" "src/TASKDB/*.hpp")
add_library( taskdb STATIC ${TASKDB_SRC} )

# TUI Library
file(GLOB TUI_SRC "src/TUI/*.cpp" "src/TUI/*.hpp")
add_library( tui STATIC ${TUI_SRC} )

# TaskRaider Executables
file(GLOB MAIN_SRC "src/*.cpp" "src/*.hpp")
add_executable( TaskRaider ${MAIN_SRC} )
target_link_libraries(TaskRaider tui taskdb ncurses)

