#pragma once

class TaskView
{
    int selection_;
    const int SHOW_COLUM = 30;
public:
    TaskView();
    int increment_selection();
    int decrement_selection();
    void draw() const;

};

