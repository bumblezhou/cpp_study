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

    while (devident < devisor) {
        devident *= 10;
    }

    double d10 = (double)devident / (double)devisor;
    int mod = devident % devisor;
    int den = ((devident - mod) / devisor);
    arr[decimal_place-1] = den;
    double next_decimal = d10 - den;
    // = [devident / devisor - den]
    // = [devident / devisor - ((devident - mod) / devisor)]
    // = mod / devisor
    // = devident % devisor / devisor
    double next_decimal1 = (devident % devisor) / (double)devisor;
    // printf("devident:%d, devisor:%d, mod: %d, d10:%f, decimal_place:%d, den:%d, next_decimal:%f, next_decimal1:%f\n", devident, devisor, mod, d10, decimal_place, den, next_decimal, next_decimal1);
    // printf("next_devident:%d, next_devisor:%d\n", (devident % devisor), devisor);
    get_decimal_expansion(arr, (devident % devisor), devisor, (decimal_place + 1), limit);
}

#define EXPANSION_SIZE 200

int main()
{
    int decimal_expansion[EXPANSION_SIZE] = {0};
    int devident = 11, devisor = 7;
    int quotient = devident/devisor;
    get_decimal_expansion(decimal_expansion, devident, devisor, 1, EXPANSION_SIZE);
    
    printf("%d.", quotient);
    print_int_array(decimal_expansion, EXPANSION_SIZE);

    return 0;
}