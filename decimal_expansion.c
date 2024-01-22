#include <stdio.h>
#include <math.h>

void print_int_array(int * arr, int size) {
    int i;
    for(i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void get_decimal_expansion(int *arr, double d, int n, int limit) {
    if (n >= limit) {
        return;
    }
    double d10 = 10 * d;
    double dn =  d10 - floor(d10);
    int den = (int)(d10 - dn);
    arr[n-1] = den;
    // printf("d:%f, n: %d, d10:%f, dn:%f, den:%d\n", d, n, d10, dn, den);
    get_decimal_expansion(arr, (d10 - den), (n + 1), limit);
}

int main()
{
    int decimal_expansion[100] = {0};
    
    double d = (5.0 / 7.0);
    get_decimal_expansion(decimal_expansion, d, 1, 100);
    
    print_int_array(decimal_expansion, 100);

    return 0;
}
