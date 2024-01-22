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
    
    devident = 10 * devident;

    int i;
    while (devident < devisor) {
        devident *= 10;
        arr[i] = 0;
        i++;
    }
    decimal_place += i;

    double d10 = (double)devident / devisor;
    int mod = devident % devisor;
    int int_part = ((devident - mod) / devisor);
    arr[decimal_place-1] = int_part;
    double next_decimal = d10 - int_part;
    // = [devident / devisor - int_part]
    // = [devident / devisor - ((devident - mod) / devisor)]
    // = mod / devisor
    // = devident % devisor / devisor
    double next_decimal1 = (devident % devisor) / (double)devisor;
    printf("devident:%d, devisor:%d, mod: %d, d10:%f, decimal_place:%d, int_part:%d, next_decimal:%f, next_decimal1:%f\n", devident, devisor, mod, d10, decimal_place, int_part, next_decimal, next_decimal1);
    printf("next_devident:%d, next_devisor:%d\n", (devident % devisor), devisor);
    get_decimal_expansion(arr, (devident % devisor), devisor, (decimal_place + 1), limit);
}

#define EXPANSION_SIZE 200

int main()
{
    int devident = 1, devisor = 3000;
    int quotient = devident/devisor;
    
    int decimal_expansion[EXPANSION_SIZE] = {0};
    get_decimal_expansion(decimal_expansion, devident, devisor, 1, 100);
    
    printf("%d.", quotient);
    print_int_array(decimal_expansion, EXPANSION_SIZE);

    return 0;
}