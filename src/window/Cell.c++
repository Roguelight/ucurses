#include <ucurses/ucurses.hpp>

using namespace ucurses;

int main()
{
    Cell cell;
    cell.write_form(std::cout);
    return 0;
}


