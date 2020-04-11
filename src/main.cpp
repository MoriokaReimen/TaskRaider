#include <cstdlib>
#include <iostream>
#include <GUI/GUI.hpp>
#include <TaskDB/TaskDB.hpp>
#include <memory>

int main()
{
    std::cout << "Hello World" << std::endl;
    auto task_db = std::make_shared<TaskDB::TaskDB>();
    GUI::GUI gui(task_db);
    gui.loop();
    return EXIT_SUCCESS;
}