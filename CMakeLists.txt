cmake_minimum_required( VERSION 2.8 )
project(TaskRaider)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STADARD_REQUIRED True)

# building gtest
add_subdirectory(external/googletest)

# building toml
set(toml11_BUILD_TEST OFF)
add_subdirectory(external/toml)

# TaskDB Library
file(GLOB TASKDB_SRC "src/TaskDB/*.cpp" "src/TASKDB/*.hpp")
add_library( taskdb STATIC ${TASKDB_SRC})
target_link_libraries(taskdb toml11)
target_include_directories(taskdb PUBLIC "src/TaskDB/")

# App Main
file(GLOB MAIN_SRC "src/*.cpp" "src/*.hpp")
add_executable(TaskRaider ${MAIN_SRC})
target_link_libraries(TaskRaider taskdb)
target_include_directories(TaskRaider PRIVATE src/)