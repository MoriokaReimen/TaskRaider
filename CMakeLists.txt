cmake_minimum_required( VERSION 2.8 )
project(TaskRaider)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STADARD_REQUIRED True)

# building gtest
add_subdirectory(external/googletest)

# building toml
set(toml11_BUILD_TEST OFF)
add_subdirectory(external/toml)

# building SFML
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(external/SFML)

# building imgui-sfml
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_DIR "${CMAKE_CURRENT_LIST_DIR}/external/imgui/")
set(SFML_DIR "external/SFML/")
add_subdirectory(external/imgui-sfml)

# TaskDB Library
file(GLOB TASKDB_SRC "src/TaskDB/*.cpp" "src/TASKDB/*.hpp")
add_library( taskdb STATIC ${TASKDB_SRC})
target_link_libraries(taskdb toml11)
target_include_directories(taskdb PUBLIC "src/TaskDB/")

# GUI Library
file(GLOB GUI_SRC "src/GUI/*.cpp" "src/GUI/*.hpp")
add_library(gui STATIC ${GUI_SRC})
target_include_directories(gui PUBLIC "src/GUI/" "src/")
target_link_libraries(gui PUBLIC sfml-graphics sfml-window sfml-system)

# App Main
file(GLOB MAIN_SRC "src/*.cpp" "src/*.hpp")
add_executable(TaskRaider ${MAIN_SRC})
target_link_libraries(TaskRaider taskdb gui ImGui-SFML::ImGui-SFML)
target_include_directories(TaskRaider PRIVATE src/)
