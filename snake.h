#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

// #define _DEBUG

#define UP 0 
#define DOWN 1
#define LEFT 2
#define RIGHT 3

typedef struct _Posn_struct {
    int y;
    int x;
} Posn;

typedef struct _Board_struct {
    int top, left, bottom, right;
    int height; int width;
} Board;

static Posn snake[1000];
static int snake_len;
static int snake_dir;
static Posn food;
static Board board;

static bool eq(Posn p1, Posn p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

static bool overlaps(Posn posn, Posn list[], int len) {
    for (int i = 0; i < len; ++i) {
        if (eq(posn, list[i])) return true;
    }
    return false;
}

static Posn make_food() {
    do {
        food.y = rand() % (board.height);
        food.x = rand() % (board.width);
    } while (overlaps(food, snake, snake_len));
    return food;
}

static void paint() {
    clear();
    for (int i = 0; i < snake_len; ++i) {
        mvaddch(board.top + snake[i].y, board.left + snake[i].x, '#');
    }
    mvaddch(board.top + food.y, board.left + food.x, '@');
    mvprintw(board.top - 2, board.right - 20, "Score: %d", snake_len);

    for (int y = board.top-1; y <= board.bottom+1; ++y) {
        mvaddch(y, board.left-1, '%');
        mvaddch(y, board.right+1, '%');
    }
    for (int x = board.left-1; x <= board.right+1; ++x) {
        mvaddch(board.top-1, x, '%');
        mvaddch(board.bottom+1, x,'%');
    }

#ifdef _DEBUG
    mvprintw(LINES-4, 0, "Food: {y=%d, x=%d}", food.y, food.x);
    printw("\n");
    mvprintw(LINES-3, 0, "Snake: ");
    for (int i = 0; i < snake_len; ++i) {
        printw("{y=%d, x=%d}, ", snake[i].y, snake[i].x);
    }

#endif

    refresh();
}

void change_dir(int ch) {
    switch (ch) {
        case KEY_UP:
            if (snake_dir == LEFT || snake_dir == RIGHT) {
                snake_dir = UP;
            }
            break;
        case KEY_DOWN:
            if (snake_dir == LEFT || snake_dir == RIGHT) {
                snake_dir = DOWN;
            }
            break;
        case KEY_LEFT:
            if (snake_dir == UP || snake_dir == DOWN) {
                snake_dir = LEFT;
            }
            break;
        case KEY_RIGHT:
            if (snake_dir == UP || snake_dir == DOWN) {
                snake_dir = RIGHT;
            }
            break;
    }
}

bool collision() {
    if (snake[0].y < 0 || snake[0].x < 0) return true;
    if (snake[0].y >= board.height || snake[0].x >= board.width) return true;
    for (int i = 1; i < snake_len; ++i) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) return true;
    } return false;
}

void move_snake() {
    Posn next_posn = snake[0];
    switch (snake_dir) {
        case UP:
            --next_posn.y;
            break;
        case DOWN:
            ++next_posn.y;
            break;
        case LEFT:
            --next_posn.x;
            break;
        case RIGHT:
            ++next_posn.x;
            break;
    }
    if (eq(next_posn, food)) {
        for (int i = snake_len; i >= 0; --i) {
            snake[i+1] = snake[i];
        }
        snake[0] = next_posn;
        ++snake_len;
        make_food();
    } else {
        for (int i = snake_len-1; i >= 0; --i) {
            snake[i+1] = snake[i];
        }
        snake[0] = next_posn;
    }
}

void init_snake() {
    board.top = 5;
    board.left = 2;
    board.bottom = LINES - 8;
    board.right = COLS - 3;
    board.width = board.right - board.left + 1;
    board.height = board.bottom - board.top + 1;

    snake[0].y = LINES / 2;
    snake[0].x = COLS / 2;
    snake_dir = RIGHT;
    snake_len = 1;
    make_food();
}

int snake_game() {
    srand(time(NULL));
    timeout(100);

    init_snake();

    while (true) {
        int ch = getch();
        if (ch != ERR) change_dir(ch);

        move_snake();
        if (collision()) break;

        paint();

        // usleep(500000);
    }

    nodelay(stdscr, FALSE);

    return MAIN_MENU;
}
