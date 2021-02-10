#include <stdio.h>
#include <math.h>

int main() {

    double body_mass_raw[19] = {4.22*pow(10, -4), 4.50*pow(10, -4), 3.90*pow(10, -4), 0.0138, 5.22*pow(10, -6),
                                6.86*pow(10, -6), 1.30*pow(10, -6), 1.76*pow(10, -7), 7.47*pow(10, -7), 7.89*pow(10, -8),
                                2.05*pow(10, -7), 9.00*pow(10, -5), 1.70*pow(10, -4), 0.0015, 4.73*pow(10, -5), 0.002,
                                0.002, 6.52*pow(10, -5), 1.01*pow(10, -4)}; // body mass in [kg]

    double max_speed_raw[19] = {36, 27, 25.92, 36, 6.48, 4.8, 3.6, 3.24, 6.84, 3.06, 4.32, 36, 36, 25.56, 6, 19.08,
                                18,10.8, 23.76}; // max speed in [km/h]

    double body_mass[19] = {}; // ln of body mass (storage)

    double max_speed[19] = {}; // ln of max speed (storage)

    // Initializing variables (matrices) --> matrices are sized as M[row][column]
    double M_matrix[2][2];
    double b_matrix[2][1];
    double M_inverse[2][2];
    double k[2][1];
    double kT[1][2];

    // Initializing variables
    int z;
    int m11 = 0;
    double m12 = 0;
    double m21;
    double m22 = 0;
    double b1 = 0;
    double b2 = 0;
    double determinant;
    double a;
    double c;

    // Take the ln() of 'x' data
    for(z = 0; z <=18; z = z + 1){

        body_mass[z] = log(body_mass_raw[z]);

    }

    // Take the ln() of 'y' data
    for(z = 0; z <=18; z = z + 1){

        max_speed[z] = log(max_speed_raw[z]);

    }

    // Calculates m11
    for(z = 0; z <= 18; z = z + 1){

        m11 = m11 + 1;

    }

    // Calculates m12
    for(z = 0; z <= 18; z = z + 1){

        m12 = m12 + body_mass[z];

    }

    m21 = m12; // This is somewhat redundant as m21 and m12 will always be equal- I include it for convenience later on.

    // Calculates m22
    for(z = 0; z <= 18; z = z + 1){

        m22 = m22 + (body_mass[z] * body_mass[z]);

    }

    // Puts values into M
    M_matrix[0][0] = m11;
    M_matrix[0][1] = m12;
    M_matrix[1][0] = m21;
    M_matrix[1][1] = m22;

    // Calculates b1
    for(z = 0; z <= 18; z = z + 1){

        b1 = b1 + max_speed[z];

    }

    // Calculates b2
    for(z = 0; z <= 18; z = z + 1){

        b2 = b2 + (max_speed[z] * body_mass[z]);

    }

    // Puts values into b
    b_matrix[0][0] = b1;
    b_matrix[1][0] = b2;

    determinant = 1/((m11 * m22) - (m12 * m21)); // Calculates determinant

    // Calculates M^-1
    M_inverse[0][0] = determinant * m22;
    M_inverse[0][1] = determinant * -m12;
    M_inverse[1][0] = determinant * -m21;
    M_inverse[1][1] = determinant * m11;

    // Calculates k
    k[0][0] = (M_inverse[0][0] * b_matrix[0][0]) + (M_inverse[0][1] * b_matrix[1][0]);
    k[1][0] = (M_inverse[1][0] * b_matrix[0][0]) + (M_inverse[1][1] * b_matrix[1][0]);

    // Calculates Transpose of k (somewhat redundant, but helps with conceptualization)
    kT[0][0] = k[0][0];
    kT[0][1] = k[1][0];

    // Converts k-values back to original power law form
    c = exp(k[0][0]);
    a = exp(k[1][0]);

    // Prints answer
    printf("The power law exponent is [%0.3f] and the coefficient is [%0.3f]\n", a, c);
    printf("The k1 value is [%0.3f] and the k0 is [%0.3f]\n", k[1][0], k[0][0]);

}