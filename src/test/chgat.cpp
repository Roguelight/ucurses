#include <ncurses.h>
#include <string>

using namespace std;
int main(int argc, char* argv[])
{
    string str("Just a string");           /* message to be appeared on the screen */
    int row,col;                           /* to store the number of rows and *
                                            * the number of colums of the screen */
    initscr();                             /* start the curses mode */
    start_color();
    init_pair(1,COLOR_CYAN, COLOR_BLACK);

    getmaxyx(stdscr,row,col);              /* get the number of rows and columns */
    printw(str.c_str());
    mvchgat(0,0,-1, A_BLINK, 1, NULL);
    
    refresh();
    getch();
    endwin();
    return 0;
}
