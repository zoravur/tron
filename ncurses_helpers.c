#include <ncurses.h>

void ncurses_init() {
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
}

void ncurses_exit() {
    endwin();
}
