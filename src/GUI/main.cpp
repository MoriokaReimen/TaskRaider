#include  <nana/gui.hpp>
#include  <nana/gui/widgets/label.hpp>
#include "Director.hpp"

int main()
{
    Director director;
    auto fm = director.construct();
    fm->show();
    nana::exec();
    return 0;
}
