#include <cstdlib>
#include <iostream>
#include <GUI/GUI.hpp>
#include <TaskDB/TaskDB.hpp>

int main()
{
    std::cout << "Hello World" << std::endl;
    TaskDB::TaskDB task_db;
    GUI::GUI gui(task_db);
    gui.loop();
    return EXIT_SUCCESS;
}