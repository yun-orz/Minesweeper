#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 9
#define COLS 9
#define MINES 10

#define HIDDEN 0
#define OPENED 1

int board[ROWS][COLS];
int state[ROWS][COLS];

int in_bounds(int row, int col) {
    return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

void clear_board(void) {
    int row, col;

    for (row = 0; row < ROWS; row++) {
        for (col = 0; col < COLS; col++) {
            board[row][col] = 0;
            state[row][col] = HIDDEN;
        }
    }
}

void place_mines(int safe_row, int safe_col) {
    int placed = 0;

    while (placed < MINES) {
        int row = rand() % ROWS;
        int col = rand() % COLS;

        if (board[row][col] == -1) {
            continue;
        }

        /* The first opened cell is always safe. */
        if (row == safe_row && col == safe_col) {
            continue;
        }

        board[row][col] = -1;
        placed++;
    }
}

void calculate_numbers(void) {
    int row, col, dr, dc;

    for (row = 0; row < ROWS; row++) {
        for (col = 0; col < COLS; col++) {
            int count = 0;

            if (board[row][col] == -1) {
                continue;
            }

            for (dr = -1; dr <= 1; dr++) {
                for (dc = -1; dc <= 1; dc++) {
                    int nr = row + dr;
                    int nc = col + dc;

                    if (in_bounds(nr, nc) && board[nr][nc] == -1) {
                        count++;
                    }
                }
            }

            board[row][col] = count;
        }
    }
}

void print_board(int reveal_mines) {
    int row, col;

    printf("\n    ");
    for (col = 0; col < COLS; col++) {
        printf("%2d ", col + 1);
    }
    printf("\n");

    printf("   +");
    for (col = 0; col < COLS; col++) {
        printf("---");
    }
    printf("+\n");

    for (row = 0; row < ROWS; row++) {
        printf("%2d |", row + 1);

        for (col = 0; col < COLS; col++) {
            if (reveal_mines && board[row][col] == -1) {
                printf(" * ");
            } else if (state[row][col] == HIDDEN) {
                printf(" # ");
            } else if (board[row][col] == 0) {
                printf(" . ");
            } else {
                printf(" %d ", board[row][col]);
            }
        }

        printf("|\n");
    }

    printf("   +");
    for (col = 0; col < COLS; col++) {
        printf("---");
    }
    printf("+\n");
}

void open_cell(int row, int col) {
    int dr, dc;

    if (!in_bounds(row, col) || state[row][col] == OPENED) {
        return;
    }

    state[row][col] = OPENED;

    if (board[row][col] != 0) {
        return;
    }

    for (dr = -1; dr <= 1; dr++) {
        for (dc = -1; dc <= 1; dc++) {
            int nr = row + dr;
            int nc = col + dc;

            if (in_bounds(nr, nc) && board[nr][nc] != -1) {
                open_cell(nr, nc);
            }
        }
    }
}

int has_won(void) {
    int row, col;

    for (row = 0; row < ROWS; row++) {
        for (col = 0; col < COLS; col++) {
            if (board[row][col] != -1 && state[row][col] == HIDDEN) {
                return 0;
            }
        }
    }

    return 1;
}

void clear_input_line(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* Discard invalid input. */
    }
}

int main(void) {
    int first_move = 1;
    int game_over = 0;

    srand((unsigned int)time(NULL));
    clear_board();

    printf("=============================\n");
    printf("        MINESWEEPER (C)       \n");
    printf("=============================\n");
    printf("Board: %d x %d, Mines: %d\n", ROWS, COLS, MINES);
    printf("Enter a row and column, for example: 3 5\n");
    printf("# = hidden, . = empty, * = mine\n");

    while (!game_over) {
        int row, col;

        print_board(0);
        printf("\nOpen cell (row column): ");

        if (scanf("%d %d", &row, &col) != 2) {
            printf("Invalid input. Please enter two numbers.\n");
            clear_input_line();
            continue;
        }

        row--;
        col--;

        if (!in_bounds(row, col)) {
            printf("Out of range. Row and column must be 1-%d.\n", ROWS);
            continue;
        }

        if (state[row][col] == OPENED) {
            printf("That cell is already open.\n");
            continue;
        }

        if (first_move) {
            place_mines(row, col);
            calculate_numbers();
            first_move = 0;
        }

        if (board[row][col] == -1) {
            print_board(1);
            printf("\nBoom! You hit a mine. Game over.\n");
            game_over = 1;
            continue;
        }

        open_cell(row, col);

        if (has_won()) {
            print_board(1);
            printf("\nCongratulations! You cleared all safe cells!\n");
            game_over = 1;
        }
    }

    return 0;
}
