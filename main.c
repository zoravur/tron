#include <ncurses.h>

#include "interface.h"
#include "ncurses_helpers.h"
#include "snake.h"


Interface interfaces[] = {
    {"main_menu", main_menu},
    {"test_interface", test_interface},
    {"snake_game", snake_game}
};

int main(int argc, char *argv[]) {
    ncurses_init();

    int next = 0;
    while (next != -1) {
        clear();
        next = interfaces[next].interface_fn();
    }

    ncurses_exit();
}
