#include <ncurses.h>
#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25

int randomizer(int *next);
void generation_from_payload(int beforeLifeCells[WIDTH][HEIGHT]);
void generation_random(int beforeLifeCells[WIDTH][HEIGHT], int *next);
void generation_copy(int lifeCells[WIDTH][HEIGHT], int beforeLifeCells[WIDTH][HEIGHT]);
void generation_display(int lifeCells[WIDTH][HEIGHT]);
void display(int generation_count, int speed);

int check_neighbours(int x, int y, int lifeCells[WIDTH][HEIGHT]);
void update_cell(int lifeCells[WIDTH][HEIGHT], int beforeLifeCells[WIDTH][HEIGHT]);
void user_input(int ch, int *running_flag, int *speed, int beforeLifeCells[WIDTH][HEIGHT], int *next,
                int *generation_count, int *generation_flag);
void clear_board(int beforeLifeCells[WIDTH][HEIGHT]);

int main() {
    int next = 1;
    int generation_count = 0;
    int generation_flag = 1;
    int running_flag = 1;
    int speed = 100;
    int lifeCells[WIDTH][HEIGHT];
    int beforeLifeCells[WIDTH][HEIGHT];
    generation_from_payload(beforeLifeCells);
    // if (freopen("/dev/tty", "r", stdin) == NULL) running_flag = 0;
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    timeout(100);
    keypad(stdscr, TRUE);
    while (running_flag) {
        generation_copy(lifeCells, beforeLifeCells);
        generation_display(lifeCells);
        display(generation_count, speed);

        update_cell(lifeCells, beforeLifeCells);
        user_input(getch(), &running_flag, &speed, beforeLifeCells, &next, &generation_count,
                   &generation_flag);

        if (generation_flag) generation_count += 1;
        napms(speed);
    }
    endwin();
    return 0;
}

void generation_random(int beforeLifeCells[WIDTH][HEIGHT], int *next) {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            beforeLifeCells[x][y] = (randomizer(next) % 5 == 0) ? 1 : 0;
        }
    }
}

void generation_from_payload(int beforeLifeCells[WIDTH][HEIGHT]) {
    char c;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (scanf(" %c", &c) == 1) {
                beforeLifeCells[x][y] = (c == '1') ? 1 : 0;
            }
        }
    }
}

void generation_copy(int lifeCells[WIDTH][HEIGHT], int beforeLifeCells[WIDTH][HEIGHT]) {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            lifeCells[x][y] = beforeLifeCells[x][y];
        }
    }
}

void user_input(int ch, int *running_flag, int *speed, int beforeLifeCells[WIDTH][HEIGHT], int *next,
                int *generation_count, int *generation_flag) {
    switch (ch) {
        case 'r':
            generation_random(beforeLifeCells, next);
            *generation_count = 0;
            *generation_flag = 1;
            break;
        case 'c':
            clear_board(beforeLifeCells);
            *generation_count = 0;
            *generation_flag = 0;
            break;
        case 'q':
            *running_flag = 0;
            break;
        case '+':
            if (*speed + 20 < 321 && *speed - 20 > 1) {
                *speed -= 20;
            }
            break;
        case '-':
            if (*speed + 20 < 301 && *speed - 20 > -21) {
                *speed += 20;
            }
            break;
        default:
            break;
    }
}

void clear_board(int beforeLifeCells[WIDTH][HEIGHT]) {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            beforeLifeCells[x][y] = 0;
        }
    }
}

int check_neighbours(int x, int y, int lifeCells[WIDTH][HEIGHT]) {
    int alive = 0;
    alive += lifeCells[(x + WIDTH - 1) % WIDTH][(y + HEIGHT - 1) % HEIGHT];
    alive += lifeCells[(x + WIDTH) % WIDTH][(y + HEIGHT - 1) % HEIGHT];
    alive += lifeCells[(x + WIDTH + 1) % WIDTH][(y + HEIGHT - 1) % HEIGHT];
    alive += lifeCells[(x + WIDTH - 1) % WIDTH][(y + HEIGHT) % HEIGHT];
    alive += lifeCells[(x + WIDTH + 1) % WIDTH][(y + HEIGHT) % HEIGHT];
    alive += lifeCells[(x + WIDTH - 1) % WIDTH][(y + HEIGHT + 1) % HEIGHT];
    alive += lifeCells[(x + WIDTH) % WIDTH][(y + HEIGHT + 1) % HEIGHT];
    alive += lifeCells[(x + WIDTH + 1) % WIDTH][(y + HEIGHT + 1) % HEIGHT];
    return alive;
}

void generation_display(int lifeCells[WIDTH][HEIGHT]) {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            if (lifeCells[x][y] == 1) {
                mvprintw(y, x, "*");
            } else {
                mvprintw(y, x, " ");
            }
        }
    }
    refresh();
}

void display(int generation_count, int speed) {
    printw("\n-------------------------------------------------------------------------------");
    printw("\nGeneration: %d\nSpeed: %d\n", generation_count, (320 - speed) / 20);
    printw(
        "Usage:\n 'r' Random generation\n 'c' Clear board\n 'q' Exit the game\n '-' Speed desrease\n '+' "
        "Speed increase");
}

void update_cell(int lifeCells[WIDTH][HEIGHT], int beforeLifeCells[WIDTH][HEIGHT]) {
    int alive;
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            alive = check_neighbours(x, y, lifeCells);
            if (alive == 3) {
                beforeLifeCells[x][y] = 1;
            } else if (alive == 2 && lifeCells[x][y] == 1) {
                beforeLifeCells[x][y] = 1;
            } else {
                beforeLifeCells[x][y] = 0;
            }
        }
    }
}

int randomizer(int *next) {
    *next = *next * 1103515245;
    return (unsigned int)(*next / 65536) * 2768;
}