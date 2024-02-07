#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
    Top,
    TopRight,
    Right,
    BottomRight,
    Bottom,
    BottomLeft,
    Left,
    TopLeft
} Direction;

struct place {
    int row, column;
    char disk;
};

struct othello_board {
    struct place places[8][8];
    char current_player;
};

struct scores {
    int white_score, black_score;
};

char input_board_lines_1[8][8] = {
    {"--------"},
    {"--------"},
    {"--------"},
    {"---WB---"},
    {"---BW---"},
    {"--------"},
    {"--------"},
    {"--------"}
};

char input_board_lines_2[8][8] = {
    {"WWWWB---"},
    {"WWWB----"},
    {"WWB-----"},
    {"WB------"},
    {"--------"},
    {"--------"},
    {"--------"},
    {"--------"}
};

void init_board(int row, int column, char input_board_lines[][column], char current_player, struct othello_board * p_board) {
    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            p_board->places[i][j].row = i + 1;
            p_board->places[i][j].column = j + 1;
            p_board->places[i][j].disk = input_board_lines[i][j];
        }
    }
    p_board->current_player = current_player;
}

void print_board(struct othello_board * p_board) {
    int i, j, row = 8, column = 8;
    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            printf("%c", p_board->places[i][j].disk);
        }
        printf("\n");
    }
    printf("%c\n", p_board->current_player);
}

int is_next_to_enemy_in_direction(Direction d, struct othello_board * p_board, struct place * p_place, char rivals_disk) {
    int result = 0;
    struct place next_to_place = {0};
    if (d == Top) {
        if (p_place->row - 1 >= 1 && p_board->places[p_place->row - 1 - 1][p_place->column - 1].disk == rivals_disk) {
            result = 1;
        }
    } else if (d == TopRight) {
        if (p_place->row - 1 >= 1 && p_place->column + 1 <= 8 && p_board->places[p_place->row - 1 - 1][p_place->column + 1 - 1].disk == rivals_disk) {
            result = 1;
        }
    } else if (d == Right) {
        if (p_place->column + 1 <= 8 && p_board->places[p_place->row - 1][p_place->column + 1 - 1].disk == rivals_disk) {
            result = 1;
        }
    } else if (d == BottomRight) {
        if (p_place->row + 1 <= 8 && p_place->column + 1 <= 8 &&p_board->places[p_place->row + 1 - 1][p_place->column + 1 - 1].disk == rivals_disk) {
            result = 1;
        }
    } else if (d == Bottom) {
        if (p_place->row + 1 <= 8 && p_board->places[p_place->row + 1 - 1][p_place->column - 1].disk == rivals_disk) {
            result = 1;
        }
    } else if (d == BottomLeft) {
        if (p_place->row + 1 <= 8 && p_place->column - 1 >= 1 && p_board->places[p_place->row + 1 - 1][p_place->column - 1 - 1].disk == rivals_disk) {
            result = 1;
        }
    } else if (d == Left) {
        if (p_place->column - 1 >= 1 && p_board->places[p_place->row - 1][p_place->column - 1 - 1].disk == rivals_disk) {
            result = 1;
        }
    } else if (d == TopLeft) {
        if (p_place->column - 1 >= 1 && p_place->row - 1 >= 1 && p_board->places[p_place->row - 1 - 1][p_place->column - 1 - 1].disk == rivals_disk) {
            result = 1;
        }
    }
    return result;
}

void get_possible_move_in_a_direction(Direction d, struct othello_board * p_board, struct place * p_place, char rivals_disk, struct place * p_possible_moves, int * p_total_count) {
    int i, j;
    if (d == Top) {
        j = p_place->column - 1;
        for (i = p_place->row - 1 - 1; i >= 1; i--) {
            if (p_board->places[i][j].disk == rivals_disk) {
                continue;
            } else if (p_board->places[i][j].disk == p_place->disk) {
                break;
            } else if (p_board->places[i][j].disk == '-') {
                p_possible_moves[*p_total_count].row = p_board->places[i][j].row;
                p_possible_moves[*p_total_count].column = p_board->places[i][j].column;
                (*p_total_count) += 1;
                break;
            }
        }
    } else if (d == TopRight) {
        for (i = p_place->row - 1 - 1, j = p_place->column + 1 - 1; i >= 1, j <= 8; i--, j++) {
            if (p_board->places[i][j].disk == rivals_disk) {
                continue;
            } else if (p_board->places[i][j].disk == p_place->disk) {
                break;
            } else {
                p_possible_moves[*p_total_count].row = p_board->places[i][j].row;
                p_possible_moves[*p_total_count].column = p_board->places[i][j].column;
                (*p_total_count) += 1;
                break;
            }
        }
    } else if (d == Right) {
        i = p_place->row - 1;
        for (j = p_place->column + 1 - 1; j <= 8; j++) {
            if (p_board->places[i][j].disk == rivals_disk) {
                continue;
            } else if (p_board->places[i][j].disk == p_place->disk) {
                break;
            } else {
                p_possible_moves[*p_total_count].row = p_board->places[i][j].row;
                p_possible_moves[*p_total_count].column = p_board->places[i][j].column;
                (*p_total_count) += 1;
                break;
            }
        }
    } else if (d == BottomRight) {
        for (i = p_place->row + 1 - 1, j = p_place->column + 1 - 1; i <= 8, j <= 8; i++, j++) {
            if (p_board->places[i][j].disk == rivals_disk) {
                continue;
            } else if (p_board->places[i][j].disk == p_place->disk) {
                break;
            } else {
                p_possible_moves[*p_total_count].row = p_board->places[i][j].row;
                p_possible_moves[*p_total_count].column = p_board->places[i][j].column;
                (*p_total_count) += 1;
                break;
            }
        }
    } else if (d == Bottom) {
        j = p_place->column - 1;
        for (i = p_place->row + 1 - 1; i <= 8; i++) {
            if (p_board->places[i][j].disk == rivals_disk) {
                continue;
            } else if (p_board->places[i][j].disk == p_place->disk) {
                break;
            } else {
                p_possible_moves[*p_total_count].row = p_board->places[i][j].row;
                p_possible_moves[*p_total_count].column = p_board->places[i][j].column;
                (*p_total_count) += 1;
                break;
            }
        }
    } else if (d == BottomLeft) {
        for (i = p_place->row + 1 - 1, j = p_place->column - 1 - 1; i <= 8, j >= 1; i++, j--) {
            if (p_board->places[i][j].disk == rivals_disk) {
                continue;
            } else if (p_board->places[i][j].disk == p_place->disk) {
                break;
            } else {
                p_possible_moves[*p_total_count].row = p_board->places[i][j].row;
                p_possible_moves[*p_total_count].column = p_board->places[i][j].column;
                (*p_total_count) += 1;
                break;
            }
        }
    } else if (d == Left) {
        i = p_place->row - 1;
        for (j = p_place->column - 1 - 1; j >= 1; j--) {
            if (p_board->places[i][j].disk == rivals_disk) {
                continue;
            } else if (p_board->places[i][j].disk == p_place->disk) {
                break;
            } else {
                p_possible_moves[*p_total_count].row = p_board->places[i][j].row;
                p_possible_moves[*p_total_count].column = p_board->places[i][j].column;
                (*p_total_count) += 1;
                break;
            }
        }
    } else if (d == TopLeft) {
        for (i = p_place->row - 1 - 1, j = p_place->column - 1 - 1; i >= 1, j >= 1; i--, j--) {
            if (p_board->places[i][j].disk == rivals_disk) {
                continue;
            } else if (p_board->places[i][j].disk == p_place->disk) {
                break;
            } else {
                p_possible_moves[*p_total_count].row = p_board->places[i][j].row;
                p_possible_moves[*p_total_count].column = p_board->places[i][j].column;
                (*p_total_count) += 1;
                break;
            }
        }
    }
}

int compare(const void *a, const void *b) {
    struct place *p_place_a = (struct place *)a;
    struct place *p_place_b = (struct place *)b;
    return (p_place_a->row == p_place_b->row ? p_place_a->column - p_place_b->column : p_place_a->row - p_place_b->row);
}

void print_possible_moves(struct place * p_possible_moves, int size) {
    qsort(p_possible_moves, size, sizeof(struct place), compare);
    int i;
    for (i = 0; i < size; i++) {
        if (p_possible_moves[i].row == 0 || p_possible_moves[i].column == 0) {
            continue;
        }
        printf("(%d, %d) ", p_possible_moves[i].row, p_possible_moves[i].column);
    }
    printf("\n");
}

char get_rivals_disk(char current_players_disk) {
    char rivals_disk = current_players_disk == 'W' ? 'B' : 'W';
    return rivals_disk;
}

void get_possible_moves_around_a_place(struct othello_board * p_board, struct place * p_place, struct place * p_possible_moves, int * p_total_count) {
    char rivals_disk = get_rivals_disk(p_place->disk);
    // top direction
    int ret1 = is_next_to_enemy_in_direction(Top, p_board, p_place, rivals_disk);
    if (ret1 == 1) {
        get_possible_move_in_a_direction(Top, p_board, p_place, rivals_disk, p_possible_moves, p_total_count);
    }
    // top right direction
    int ret2 = is_next_to_enemy_in_direction(TopRight, p_board, p_place, rivals_disk);
    if (ret2 == 1) {
        get_possible_move_in_a_direction(TopRight, p_board, p_place, rivals_disk, p_possible_moves, p_total_count);
    }
    // right direction
    int ret3 = is_next_to_enemy_in_direction(Right, p_board, p_place, rivals_disk);
    if (ret3 == 1) {
        get_possible_move_in_a_direction(Right, p_board, p_place, rivals_disk, p_possible_moves, p_total_count);
    }
    // bottom right direction
    int ret4 = is_next_to_enemy_in_direction(BottomRight, p_board, p_place, rivals_disk);
    if (ret4 == 1) {
        get_possible_move_in_a_direction(BottomRight, p_board, p_place, rivals_disk, p_possible_moves, p_total_count);
    }
    // bottom direction
    int ret5 = is_next_to_enemy_in_direction(Bottom, p_board, p_place, rivals_disk);
    if (ret5 == 1) {
        get_possible_move_in_a_direction(Bottom, p_board, p_place, rivals_disk, p_possible_moves, p_total_count);
    }
    // bottom left direction
    int ret6 = is_next_to_enemy_in_direction(BottomLeft, p_board, p_place, rivals_disk);
    if (ret6 == 1) {
        get_possible_move_in_a_direction(BottomLeft, p_board, p_place, rivals_disk, p_possible_moves, p_total_count);
    }
    // left direction
    int ret7 = is_next_to_enemy_in_direction(Left, p_board, p_place, rivals_disk);
    if (ret7 == 1) {
        get_possible_move_in_a_direction(Left, p_board, p_place, rivals_disk, p_possible_moves, p_total_count);
    }
    // top left direction
    int ret8 = is_next_to_enemy_in_direction(TopLeft, p_board, p_place, rivals_disk);
    if (ret8 == 1) {
        get_possible_move_in_a_direction(TopLeft, p_board, p_place, rivals_disk, p_possible_moves, p_total_count);
    }
}

void get_possible_moves(struct othello_board * p_board, struct place * p_possible_moves) {
    int i, j, row = 8, column = 8, p = 0, total_count = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            // get current player's disks
            if (p_board->places[i][j].disk != p_board->current_player) {
                continue;
            } else {
                // current player's disk
                get_possible_moves_around_a_place(p_board, &p_board->places[i][j], p_possible_moves, &total_count);
            }
        }
    }
}

void get_scores(struct othello_board * p_board, struct scores * p_scores) {
    int i, j, row = 8, column = 8;
    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            if (p_board->places[i][j].disk == 'W') {
                p_scores->white_score++;
            }
            if (p_board->places[i][j].disk == 'B') {
                p_scores->black_score++;
            } 
        }
    }
}

int main()
{
    struct othello_board board = {0};
    init_board(8, 8, input_board_lines_1, 'W', &board);
    print_board(&board);
    printf("L\n");
    struct place possible_moves[32];
    memset(possible_moves, 0, sizeof(possible_moves));
    get_possible_moves(&board, possible_moves);
    print_possible_moves(possible_moves, 32);
    printf("M35\n");
    board.places[3-1][5-1].disk = board.current_player;
    board.current_player = get_rivals_disk(board.current_player);
    struct scores current_scores = {0};
    get_scores(&board, &current_scores);
    printf("Black - %d White - %d\n", current_scores.black_score, current_scores.white_score);
    print_board(&board);
    printf("L\n");
    memset(possible_moves, 0, sizeof(possible_moves));
    get_possible_moves(&board, possible_moves);
    print_possible_moves(possible_moves, 32);
    
    // init_board(8, 8, input_board_lines_2, 'B', &board);
    // print_board(&board);
    
    return 0;
}
