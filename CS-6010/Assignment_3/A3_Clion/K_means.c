#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "time.h"

#include <errno.h>
#include <limits.h>

#define READ_ERROR_STRING "Error:\tFile was not in correct format.\n"

#define USAGE_STRING "USAGE:./executableName input_file k_value"

// In CLion, pass both command line parameters through Run-->Edit Configuration-->program arguments (one space between each argument)
// Set directory to the one running K_means.c and holding the 2 data files.
// Additional note: try and keep k < ~5/6 for good performance.
int main(int argc, char **argv){

    // passed in to the program from the command line.
    int nRows, nCols, k;

    // Here we check to be sure that the correct number of arguments have been
    // passed in from the command line. The first argument is always the program
    // name. If not, we print and error and return error status.
    if(argc != 3)
    {
        fprintf(stderr, "%s\nYou must pass your data file  and k value "
                        "(in that order)as an argument to this program.\n", USAGE_STRING);
        return 1;
    }

    // This section will safely parse the value of k passed in to the program.
    // If the argument cannot be parsed to an integer, or if it is larger than
    // INT_MAX, we error out.
    char *endptr = NULL;
    int base = 10;
    errno = 0;
    long int long_k = strtol(argv[2], &endptr, base);

    // This will trigger if an error was encountered when trying to parse the
    // input, or if the input was not a proper integer (e.g. 124A). This
    // can also trigger if the input is too long to fit even in a long int.
    if((errno != 0) || (*endptr != '\0'))
    {
        fprintf(stderr, "The input: \"%s\" could not be parsed as an integer.\""
                        " \n", argv[2]);
        return 1;
    }
    if((long_k > INT_MAX) || (long_k <= 0))
    {
        fprintf(stderr, "The k-value input was:\t%ld\n"
                        "K must be larger than zero, and no larger than %u.\n", long_k,
                INT_MAX);
        return 1;
    }
    k = (int)long_k;

    // This opens the file for reading. A return value of NULL indicates the file
    // failed to open for some reason, in which case we print out the error and
    // return an error status.
    FILE *infile = fopen(argv[1],"r");
    if(infile == NULL)
    {
        fprintf(stderr, "Could not open the file:\t%s\n", argv[1]);
        perror("Failed to open file");
        return 2;
    }

    // This will read in the number of rows and columns (first line of the file).
    // If it reads fewer than two things, we know the file is incorrect.
    int readIn = fscanf(infile, " %d %d", &nRows, &nCols);

    if(readIn != 2)
    {
        fprintf(stderr, READ_ERROR_STRING);
        fclose(infile);
        return 1;
    }

    // Makes a stack array with nRows rows and nCols columns.z
    // May be indexed with data_array[i][j].
    double data_array_OG[nRows][nCols];

    // This loop reads in the expected number of rows and columns. If it fails to
    // read the expected number, it errors out. This doesn't catch some errors,
    // E.G. too *many* lines in the input file, but you should not be editing
    // those files for the assignment anyway.
    for (int i = 0; i < nRows; ++i)
    {
        for (int j = 0; j < nCols; ++j)
        {
            readIn = fscanf(infile," %lf", &(data_array_OG[i][j]));
            if(!readIn)
            {
                fprintf(stderr, READ_ERROR_STRING );
                return 1;
            }
        }
    }

    // Since we've read in all the data we need, close the file.
    fclose(infile);

/*
################################################|BEGINNING OF NEW CODE|#################################################
*/

    int n = nCols;  // Dimensions
    int iterations = 20;  // Number of iterations set by user.

    struct centroid_coordinates{
        double coordinate;
    }centroid_coordinates[iterations][k][n];

    // Calculating variance/std deviation/z score --> the averaged squared differences from the mean
    double squared_differences_sum[nRows][n];
    double std_deviation[nRows][n];
    double mean_val[n];
    double z_score_storage[nRows][n];

    // Initializing data mean- the next three for loops generate a mean for the data for each dimension.
    for (int i = 0; i < n; i = i + 1) {
        mean_val[n] = 0;
    }

    for (int i = 0; i < nRows; i = i + 1) {
        for (int j = 0; j < n; j = j + 1) {
            mean_val[j] = mean_val[j] + data_array_OG[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        mean_val[i] = mean_val[i] / nRows;
    }

    // Initializing squared_differences_sum- makes sure it equals zero for each iteration.
    for (int i = 0; i < nRows; i = i + 1) {
        for (int j = 0; j < n; j = j + 1) {
            squared_differences_sum[i][j] = 0;
        }
    }

    for (int i = 0; i < nRows; i = i + 1) {
        for (int l = 0; l < n; l = l + 1) {
            squared_differences_sum[i][l] = squared_differences_sum[i][l] + ((data_array_OG[i][l] - mean_val[l]) * (data_array_OG[i][l] - mean_val[l]));
        }
    }

    for (int i = 0; i < nRows; i = i + 1) {
        for (int j = 0; j < n; j = j + 1) {
            std_deviation[i][j] = sqrt(squared_differences_sum[i][j] / (nRows));
        }
    }

    // Calculates final z-score
    for (int i = 0; i < nRows; i = i + 1) {
        for (int j = 0; j < n; j = j + 1) {
            z_score_storage[i][j] = (data_array_OG[i][j] - mean_val[j]) / std_deviation[i][j];
        }
    }

    // K_switch indicates whether the loops will be using normal data or z-scores.
    for (int k_switch = 0; k_switch < 2; k_switch = k_switch + 1) {

        int k_on = k_switch;

        double data_array[nRows][n];

        if (k_on == 0){
            for (int j = 0; j < nRows; j = j + 1) {
                for (int l = 0; l < n; l = l + 1) {
                    data_array[j][l] = data_array_OG[j][l];
                }
            }
        } else {
            for (int j = 0; j < nRows; j = j + 1) {
                for (int l = 0; l < n; l = l + 1) {
                    data_array[j][l] = z_score_storage[j][l];
                }
            }
        }

        // This next chunk of code deals with finding/creating the random, initial centroids.
        double initial_centroids[k][n];
        int random_indices[k];
        double true_initial[k][n];

        // Generates seed for rand() to use- time based, as current time is always different.
        srand(time(0));

        for (int i = 0; i < k; i = i + 1) {
            random_indices[i] = (rand() % nRows) + 1;
            // printf("%d \n", random_indices[i]);
        }

        // Finding k random centroids.
        for (int i = 0; i < k; i = i + 1) {
            for (int j = 0; j < n; j = j + 1) {
                initial_centroids[i][j] = data_array[random_indices[i]][j];
            }
        }

        // Beginning of K-means iterations.
        for (int iteration = 0; iteration < iterations; iteration = iteration + 1) {

            // Stores the randomly generated centroid- first for normal data, then replaced with z_score.
            if (iteration == 0) {
                for (int i = 0; i < k; i = i + 1) {
                    for (int j = 0; j < n; j = j + 1) {
                        true_initial[i][j] = initial_centroids[i][j];
                    }
                }
            }

            // This portion of code finds the Euclidean distance between initial centroids and data. It then assigns the
            // data to whichever centroid is closes, denoted as 1 - n, where k1 = 1, k2 = 2, etc.
            double closest_centroid[nRows];  // Stores 1-n, where each number identifies which centroid it is closest to.
            double squared_diff[n];
            double centroid_eval[k];

            for (int i = 0; i < nRows; i = i + 1) {
                for (int j = 0; j < k; j = j + 1) {
                    double sum = 0;
                    for (int l = 0; l < n; l = l + 1) {
                        squared_diff[l] = (initial_centroids[j][l] - data_array[i][l]) *
                                          (initial_centroids[j][l] - data_array[i][l]);
                        sum = sum + squared_diff[l];
                    }
                    centroid_eval[j] = sqrt(sum);
                }

                double min = centroid_eval[0];
                int index;

                // Figures out which of the n options the value is closest to.
                for (int j = 0; j < k; j = j + 1) {
                    if (min >= centroid_eval[j]) {
                        min = centroid_eval[j];
                        index = j;
                    }
                }

                closest_centroid[i] = index;  // index refers to which node it is closest to (i.e. k1 = index 1, k2 = index 2...)

            }


            double centroid_number[k];  // Creates an empty array of size k.
            double centroid_count[k];  // Counts the number of data points closes to the k centroid.

            // Makes sure to initialize centroid_count; setting it back to zero for each iteration.
            for (int i = 0; i < k; i = i + 1) {
                centroid_count[k] = 0;
            }

            for (int i = 0; i < k; i = i + 1) {
                centroid_number[i] = i;
            }

            // These loops do the actual counting- count values are put into centroid_count[k].
            for (int z = 0; z < nRows; z = z + 1) {
                for (int j = 0; j < k; j = j + 1) {
                    if (closest_centroid[z] == centroid_number[j]) {
                        centroid_count[j] = centroid_count[j] + 1;
                    }
                }
            }

            // I was going to put an array here instead, but C was really bugging out...
            struct value_add {
                double val;
            } value_add[k][n];

            // Initializes value_add- makes sure all values are zero for each iteration.
            for (int i = 0; i < k; i = i + 1) {
                for (int j = 0; j < n; j = j + 1) {
                    value_add[i][j].val = 0;
                }
            }

            // Sums all the data in n dimensions according to which group they are in and puts these sums in their respective index.
            for (int i = 0; i < nRows; i = i + 1) {
                for (int j = 0; j < k; j = j + 1) {
                    if (closest_centroid[i] == centroid_number[j]) {
                        for (int l = 0; l < n; l = l + 1) {
                            value_add[j][l].val = value_add[j][l].val + data_array[i][l];
                        }
                    }

                }

            }

            // New centroids after K-means algorithm pass.
            double new_centroids[k][n];

            // Generates new centroids- finds the mean for each dimension for each respective centroid.
            for (int i = 0; i < k; i = i + 1) {
                for (int j = 0; j < n; j = j + 1) {
                    new_centroids[i][j] = value_add[i][j].val / centroid_count[i];
                }
            }

            // Replaces old centroids with new centroids
            for (int i = 0; i < k; i = i + 1) {
                for (int j = 0; j < n; j = j + 1) {
                    initial_centroids[i][j] = new_centroids[i][j];
                }
            }

            for (int i = 0; i < k; i = i + 1) {
                for (int j = 0; j < n; j = j + 1) {
                    centroid_coordinates[iteration][i][j].coordinate = new_centroids[i][j];
                }
            }

            // The rest of the code primarily deals with printing solutions, for debugging purposes.
            if (k_on == 0 && iteration == 0){
                printf("\n");
                printf("K-means coordinate values for normal data with %d iterations: \n", iterations);
                printf("\n");
                printf("Random, original coordinate(s) for normal data: \n");
                for (int i = 0; i < k; i = i + 1) {
                    printf("Initial coordinate %d: ", i + 1);
                    for (int j = 0; j < n; ++j) {
                        printf("[%f]", true_initial[i][j]);
                    }
                    printf("\n");
                }
            }

            if (k_on == 1 && iteration == 0){
                printf("\n");
                printf("K-means coordinate values for z-score data with %d iterations: \n", iterations);
                printf("\n");
                printf("Random, original coordinate(s) for z-score data: \n");
                for (int i = 0; i < k; i = i + 1) {
                    printf("Initial coordinate %d: ", i + 1);
                    for (int j = 0; j < n; ++j) {
                        printf("[%f]", true_initial[i][j]);
                    }
                    printf("\n");
                }
            }

            printf("\n");
            for (int i = 0; i < k; i = i + 1) {
                printf("Coordinate for Centroid %d, Iteration %d: \n", i + 1, iteration + 1);

                for (int j = 0; j < n; j = j + 1) {
                    printf("%f\n", new_centroids[i][j]);
                }
            }

        }

    }

    printf("\n");
    printf("NOTE: Watch for convergent coordinates (when values begin repeating).");
    printf("\n");

    return 0;

}