#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>

double generate_random(int range);

double e_function(double x_rand);

void print_data(double thread_count, double N, double approx, double exact, double time);

double approximate_e_serial(int upper_y, int upper_x, int scale);

double approximate_e_parallel(int upper_y, int upper_x, int scale);

int main() {

    // Initializes starting values
    int y_higher = 6;
    int x_higher = 1;
    int N0;

    srand(time(NULL));

    // Loops through both the serial and parallel functions, changing the value of N0 to be 1, 10, and 100 respectively.
    for (int i = 1; i < 101; i = i * 10) {

        N0 = i;

        approximate_e_parallel(y_higher, x_higher, N0);

        approximate_e_serial(y_higher, x_higher, N0);

    }

    return 1;

}

// Generates a random number.
double generate_random(int range) {

    double num = (rand() % range) + ((rand() * 3.05184) / 100000.0);

    // Ensures random number is within max y-range.
    if (num > range) {

        num = generate_random(range);

    }

    return num;

}

// Acts as a function that takes an x-value as a parameter and returns the solved integrand.
double e_function(double x_rand) {

    double e_limit = 2 * x_rand * exp(x_rand * x_rand);

    return e_limit;

}

// Prints values in the form specified in Assignment 7 document.
void print_data(double thread_count, double N, double approx, double exact, double time) {

    printf("---------------------------------\n");

    printf("Thread count: %f\n", thread_count);
    printf("N0: %f\n", N);
    printf("Approximation of e: %f\n", approx);
    printf("Exact value of e: %f\n", exact);
    printf("Calculation time [s]: %f\n", time);

    printf("---------------------------------\n");

}

// Performs the Monte Carlo integration in a serial fashion.
double approximate_e_serial(int upper_y, int upper_x, int scale) {

    // Begins timer.
    double t = omp_get_wtime();

    int thread_count = omp_get_num_threads();
    double under = 0;
    double iterations = 800000 * scale;

    for (int i = 0; i < iterations; i = i + 1) {

        double rand_x = generate_random(upper_x);
        double rand_y = generate_random(upper_y);
        double calc_y = e_function(rand_x);

        if (rand_y < calc_y) {

            under = under + 1;

        }

    }

    double ratio = (under / iterations) * upper_y;

    // Ends timer.
    t = omp_get_wtime() - t;

    print_data(thread_count, scale, ratio + 1, exp(1), t);

    return ratio + 1;

}

// Performs the Monte Carlo integration in a parallel fashion.
double approximate_e_parallel(int upper_y, int upper_x, int scale) {

    // Starts timer.
    double t = omp_get_wtime();

    double under;
    double under_add = 0;
    double iterations = 800000 * scale;
    int threads;

    omp_set_num_threads(6);

    // Splits into separate threads running in parallel.
    #pragma omp parallel firstprivate(iterations) firstprivate(upper_x) firstprivate(upper_y) private(under) shared(threads) shared(under_add) default(none)
    {

        threads = omp_get_num_threads();  // Obtains total thread number.
        int thread_id = omp_get_thread_num();  // Obtains current thread number.

        for (int i = thread_id; i < iterations; i = i + threads) {

            double rand_x = generate_random(upper_x);
            double rand_y = generate_random(upper_y);
            double calc_y = e_function(rand_x);

            if (rand_y < calc_y) {

                under = under + 1;

            }

        }

        under_add = under_add + under;

    }

    double ratio = (under_add / iterations) * upper_y;

    // Ends timer.
    t = omp_get_wtime() - t;

    print_data(threads, scale, ratio + 1, exp(1), t);

    return ratio + 1;

}