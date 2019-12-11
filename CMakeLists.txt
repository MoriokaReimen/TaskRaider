cmake_minimum_required( VERSION 2.8 )
project(TaskRaider)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STADARD_REQUIRED True)

# building nana
add_subdirectory(external/nana)

# General Setting
include_directories("src/" "${PROJECT_SOURCE_DIR}/external/nana/include/")

# TaskDB Library
file(GLOB TASKDB_SRC "src/TaskDB/*.cpp" "src/TASKDB/*.hpp")
add_library( taskdb STATIC ${TASKDB_SRC} )

# TUI Library
file(GLOB TUI_SRC "src/TUI/*.cpp" "src/TUI/*.hpp")
add_library( tui STATIC ${TUI_SRC} )

# TaskRaider TUI Executables
file(GLOB TUI_MAIN_SRC "src/TUI_MAIN/*.cpp" "src/TUI_MAIN/*.hpp")
add_executable( tTaskRaider ${TUI_MAIN_SRC} )
target_link_libraries(tTaskRaider tui taskdb ncursesw)
target_include_directories(tTaskRaider PRIVATE "src/TUI_MAIN/")

# TaskRaider GUI Executables
file(GLOB GUI_MAIN_SRC "src/GUI/*.cpp" "src/GUI/*.hpp")
add_executable( gTaskRaider ${GUI_MAIN_SRC} )
target_link_libraries(gTaskRaider nana taskdb)
target_include_directories(gTaskRaider PRIVATE "src/GUI/")
