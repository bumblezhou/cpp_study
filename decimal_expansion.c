#include <stdio.h>
#include <math.h>

void print_int_array(int * arr, int size) {
    int limit = size > 50 ? 50 : size;
    int i;
    for(i = 0; i < limit; i++) {
        printf("%d", arr[i]);
    }
    if (size > limit) {
        printf("...");
    }
    printf("\n");
}

void get_decimal_expansion(int *arr, int devident, int devisor, int decimal_place, int limit) {
    if (decimal_place >= limit) {
        return;
    }
    
    while (devident > devisor) {
        devident = devident % devisor;
    }
    devident = 10 * devident;

    int i = 0;
    while (devident < devisor) {
        devident *= 10;
        i++;
    }
    if (i > 0) {
        decimal_place += i;
    }

    double d10 = (double)devident / devisor;
    int mod = devident % devisor;
    int int_part = ((devident - mod) / devisor);
    arr[decimal_place-1] = int_part;
    // double next_decimal = d10 - int_part;
    // = [devident / devisor - int_part]
    // = [devident / devisor - ((devident - mod) / devisor)]
    // = mod / devisor
    // = devident % devisor / devisor
    // double next_decimal1 = (devident % devisor) / (double)devisor;
    // printf("devident:%d, devisor:%d, mod: %d, d10:%f, decimal_place:%d, int_part:%d, next_decimal:%f, next_decimal1:%f, arr[0]:%d\n", devident, devisor, mod, d10, decimal_place, int_part, next_decimal, next_decimal1, arr[0]);
    // printf("next_devident:%d, next_devisor:%d\n", (devident % devisor), devisor);
    get_decimal_expansion(arr, (devident % devisor), devisor, (decimal_place + 1), limit);
}

struct decimal_details {
    int begins_at;
    int cycle_length[25];
    int cycle_decimals[25][100];
};

void print_decimal_details(struct decimal_details * p_decimal_details) {
    printf("begins_at: %d\n", p_decimal_details->begins_at);
    int i, j;
    for(i = 0; i < 25; i++) {
        if (p_decimal_details->cycle_length[i] == 0) {
            continue;
        } else {
            printf("cycle_length: %d\n", p_decimal_details->cycle_length[i]);
            printf("cycle_decimals: ");
            for(j = 0; j < p_decimal_details->cycle_length[i]; j++) { 
                printf("%d", p_decimal_details->cycle_decimals[i][j]);
            }
            printf("\n");
        }
    }
    printf("\n");
}

int check_all_elements_equal(const int * a, int n) {   
    while(--n>0 && a[n]==a[0]);
    return n!=0;
}

void get_decimal_details(const int * p_decimal_expansion, int size, struct decimal_details * p_decimal_details) {
    int max_cycle_length = size / 2;
    int cycle_length, b, i, j, count = 0, prefix_zero_count = 0;
    int quit_all = 0, quit_begins_move = 0;
    for (cycle_length = 1; cycle_length < max_cycle_length; cycle_length++) {
        if (quit_all) {
            break;
        }
        for(b = 0; b < max_cycle_length - cycle_length; b++) {
            if (quit_all) {
                break;
            }
            if (quit_begins_move) {
                break;
            }
            if (p_decimal_expansion[b] == 0) {
                continue;
            }
            for (i = b, j = i + cycle_length; i < cycle_length + b, j < 2 * cycle_length + b; i++, j++) {
                
                if (p_decimal_expansion[i] == p_decimal_expansion[j]) {
                    int all_equals = check_all_elements_equal(&p_decimal_expansion[i], max_cycle_length - i);
                    if (all_equals == 0) {
                        // printf("cycle_length:%d, i: %d, j: %d, all equals!\n", cycle_length, i, j);
                        p_decimal_details->cycle_decimals[count][p_decimal_details->cycle_length[count]] = p_decimal_expansion[i];
                        p_decimal_details->cycle_length[count] = 1;
                        count++;
                        quit_all = 1;
                        break;
                    }
                    if (p_decimal_details->cycle_length[0] != 0 && cycle_length != p_decimal_details->cycle_length[0] && (cycle_length % p_decimal_details->cycle_length[0] == 0)) {
                        // printf("cycle_length:%d, i: %d, j: %d, the min cycle_length is:%d (1).\n", cycle_length, i, j, p_decimal_details->cycle_length[0]);
                        // quit_all = 1;
                        break;
                    }
                    if (p_decimal_expansion[i+1] != p_decimal_expansion[j+1]) {
                        // printf("cycle_length:%d, b:%d, i: %d, j: %d, invalid cycle_length:%d!\n", cycle_length, b, i, j, cycle_length);
                        break;
                    }
                    if (p_decimal_details->cycle_length[0] != 0 && b != p_decimal_details->begins_at && (cycle_length % p_decimal_details->cycle_length[0] == 0)) {
                        printf("cycle_length:%d, b: %d, i: %d, j: %d, the min cycle_length is:%d (2).\n", cycle_length, b, i, j, p_decimal_details->cycle_length[0]);
                        quit_begins_move = 1;
                        break;
                    }
                    p_decimal_details->cycle_decimals[count][i-b] = p_decimal_expansion[i];
                    p_decimal_details->cycle_length[count] = cycle_length;
                    p_decimal_details->begins_at = b;
                    printf("cycle_length:%d, b: %d, i: %d, j: %d, count:%d, first: %d, second: %d, p_decimal_details->cycle_length[0]: %d\n", cycle_length, b, i, j, count, p_decimal_expansion[i], p_decimal_expansion[j], p_decimal_details->cycle_length[0]);
                } else {
                    // printf("cycle_length:%d, b: %d, i: %d, j: %d, invalid cycle length.\n", cycle_length, b, i, j);
                    break;
                }
            }
            if (p_decimal_details->cycle_length[count] != 0) {
                count++;
            }
        }
    }
}

#define EXPANSION_SIZE 200

int main()
{
    int devident = 5, devisor = 43000;
    int quotient = devident/devisor;
    
    int decimal_expansion[EXPANSION_SIZE] = {0};
    get_decimal_expansion(decimal_expansion, devident, devisor, 1, EXPANSION_SIZE);
    
    printf("%d.", quotient);
    print_int_array(decimal_expansion, EXPANSION_SIZE);
    
    struct decimal_details dd = {0};
    get_decimal_details(decimal_expansion, EXPANSION_SIZE, &dd);
    
    // int test[10] = {0,0,1,1,1,1,1,1,1,1};
    // int result1 = check_all_elements_equal(&test[0], 8);
    // printf("equals? %d\n", result1);
    // int result2 = check_all_elements_equal(&test[2], 8);
    // printf("equals? %d\n", result2);
    
    print_decimal_details(&dd);
    return 0;
}