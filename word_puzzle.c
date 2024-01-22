#include <stdio.h>
#include <stdlib.h>

char word_puzzle[13][22] = {
    {"----------------------"},
    {"|1 |2 |3 |* |4 |5 |6 |"},
    {"----------------------"},
    {"|* |7 |  |* |8 |  |  |"},
    {"----------------------"},
    {"|9 |  |  |10|* |11|  |"},
    {"----------------------"},
    {"|12|  |* |13|14|  |  |"},
    {"----------------------"},
    {"|* |15|16|* |17|  |* |"},
    {"----------------------"},
    {"|18|  |  |* |19|  |20|"},
    {"----------------------"},
};

void print_char_line(char * arr, int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%c", arr[i]);
    }
    printf("\n");
}

void print_word_puzzle() {
    int column = sizeof(word_puzzle[0]);
    int row = sizeof(word_puzzle)/sizeof(word_puzzle[0]);
    int i;
    for (i = 0; i < row; i++) {
        print_char_line(word_puzzle[i], column);
    }
}

struct h_result_words {
  char result[6][44];
};

void print_horizonal_result(struct h_result_words *rw) {
    int column = sizeof(rw->result[0]);
    int row = sizeof(rw->result)/sizeof(rw->result[0]);
    // printf("column=%d, row=%d\n", column, row);
    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            printf("%c", rw->result[i][j]);
        }
    }
    printf("\n");
}

void find_horizonal_words(struct h_result_words *p_hrw) {

    int column = sizeof(word_puzzle[0]);
    int row = sizeof(word_puzzle)/sizeof(word_puzzle[0]);
    
    int i, j;
    for (i = 1; i < row; i += 2) {
        int result_row = ((i + 1)/2 - 1);
        for (j = 1; j < column; j += 3) {
            if (word_puzzle[i][j] != '*') {
                p_hrw->result[result_row][j] = word_puzzle[i][j];
                p_hrw->result[result_row][j+1] = word_puzzle[i][j+1];
            } else {
                p_hrw->result[result_row][j] = ',';
            }
        }
    }
}

struct v_result_words {
  char result[7][32];
};

void print_vertical_result(struct v_result_words *rw) {
    int column = sizeof(rw->result[0]);
    int row = sizeof(rw->result)/sizeof(rw->result[0]);
    // printf("column=%d, row=%d\n", column, row);
    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            printf("%c", rw->result[i][j]);
        }
    }
    printf("\n");
}

void find_vertical_words(struct v_result_words *p_vrw) {
    int column = sizeof(word_puzzle[0]);
    int row = sizeof(word_puzzle)/sizeof(word_puzzle[0]);
    
    int i, j;
    for (j = 1; j < column; j += 3) {
        int target_row = ((j + 2)/3 - 1);
        int target_col = 0;
        for (i = 1; i < row; i += 2) {
            if (word_puzzle[i][j] != '*') {
                // printf("column:%d, row:%d, target_row:%d, target_col:%d, char:%c%c\n", j, i, target_row, target_col, word_puzzle[i][j], word_puzzle[i][j+1]);
                p_vrw->result[target_row][target_col] = word_puzzle[i][j];
                target_col++;
                p_vrw->result[target_row][target_col+1] = word_puzzle[i][j+1];
                target_col++;
            } else {
                // printf(",\n");
                p_vrw->result[target_row][target_col] = ',';
                target_col++;
            }
        }
    }
}

int main()
{
    printf("The word puzzle:\n");
    print_word_puzzle();
    
    printf("The horizonal words:\n");
    struct h_result_words hrw = {'\0'};
    find_horizonal_words(&hrw);
    print_horizonal_result(&hrw);
    
    printf("The vertical words:\n");
    struct v_result_words vrw = {'\0'};
    find_vertical_words(&vrw);
    print_vertical_result(&vrw);

    return 0;
}