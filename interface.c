#include <ncurses.h>

#include "interface.h"

const int EXIT = -1;
const int MAIN_MENU = 0;
const int TEST_INTERFACE = 1;

int main_menu() {
    int ch = 0;

    printw("0\tMain menu (this interface)\n");
    printw("1\tTest interface (single key press)\n");
    printw("2\tSnake game\n");

    mvprintw(10, 0, "Press q to exit\n");
    refresh();

    do {
        ch = getch();
        if (ch == 'q') return EXIT;
    } while (ch < '0' || ch > '2');
    return ch-'0';
}

int test_interface() {
    int ch;

    printw("Type any character to see it in bold\n");
    ch = getch();
    
    if (ch == KEY_F(1))
        printw("F1 key pressed");
    else {
        printw("The pressed key is ");
        addch(ch | A_BOLD);
    }
    refresh();
    getch();
    return MAIN_MENU;
}
