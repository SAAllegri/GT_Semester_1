#include "helper.h"

int main() {

    int y_higher = 6;
    int x_higher = 1;
    int N0 = 10;

    srand(time(NULL));

    approximate_e_parallel(y_higher, x_higher, N0);

    approximate_e_serial(y_higher, x_higher, N0);

    return 1;

}