#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct point {
    int x, y;
};

struct matrix {
    int square_width;
    struct point **points;
};

struct segment {
    struct point from;
    struct point to;
};

void init_matrix_points(struct matrix * p_mtrx) {
    int i, j;
    for (i = 0; i < p_mtrx->square_width; i++) {
        for (j = 0; j < p_mtrx->square_width; j++) {
            p_mtrx->points[i][j].x = (i + 1);
            p_mtrx->points[i][j].y = (j + 1);
        }
    }
}

void print_matrix_points(struct matrix * p_mtrx) {
    int i, j;
    for (i = 0; i < p_mtrx->square_width; i++) {
        for (j = 0; j < p_mtrx->square_width; j++) {
            printf("(%d,%d) ", p_mtrx->points[i][j].x, p_mtrx->points[i][j].y);
        }
        printf("\n");
    }
}

int main()
{   int square_width = 0;
    int line_segment_count = 0;
    printf("Please square width and line segment count:\n");
    scanf( "%d\n%d", &square_width, &line_segment_count);
    // printf("square_width:%d, line_segment_count:%d\n", square_width, line_segment_count);
    struct matrix mtrx;
    mtrx.square_width = square_width;
    
    struct point** points = (struct point**)malloc(square_width * sizeof(struct point*));
    int i;
    for (i = 0; i < square_width; i++)
        points[i] = (struct point*)malloc(square_width * sizeof(struct point));
    
    mtrx.points = points;
    
    init_matrix_points(&mtrx);
    print_matrix_points(&mtrx);
    
    struct segment segments[line_segment_count];
    memset(segments, 0, sizeof(segments));
    printf("Please square width and line segment count:\n");
    // H 1 1
    // H 1 3
    // H 2 1
    // H 2 2
    // H 2 3
    // H 3 2
    // H 4 2
    // H 4 3
    // V 1 1
    // V 2 1
    // V 2 2
    // V 2 3
    // V 3 2
    // V 4 1
    // V 4 2
    // V 4 3 

    // int i;
    // for(i = 0; i < line_segment_count; i++) {
    //     char direction = '';
    //     int x, y;
    //     scanf("%c %d %d", &direction, &x, &y);
    // }
    
    for (i = 0; i < square_width; i++)
        free(points[i]);
    free(points);
    return 0;
}
