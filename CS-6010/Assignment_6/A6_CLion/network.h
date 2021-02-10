#ifndef A6_CLION_NETWORK_H
#define A6_CLION_NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Input parameters
int numAgents = 6;
int numNearestNeighbors = 6;
double pReplaceRandom = 0;

// Struct holding information about state (susceptible, infected, recovered) and connection (the index of the node which
// the current associated node is connected to).
typedef struct Node {

    int state;
    int connection;
    int visited;
    int visited_final;

} Node;

// Generates a network where the first row indicates the node number, and the column starting at the second row down
// holds information about the node connections. Node.state holds the "state" of the node, Node.connection holds the
// index of the connected node.
Node *generate_network(int nodes, int neighbors, double randomizer) {

    if (neighbors < 2) {
        neighbors = 2;
        printf("WARNING! Nearest neighbors is too low- it is now equal to 2.");
    }

    if ((neighbors % 2 != 0) && (neighbors < nodes)) {
        neighbors = neighbors + 1;
        printf("WARNING! Nearest neighbors is uneven- it is now equal to nearest neighbors + 1.");
    }

    if (neighbors > nodes) {
        neighbors = nodes;
        printf("WARNING! Nearest neighbors is too high- it is now equal to number of agents.");
    }

    if (randomizer < 0) {
        randomizer = 0;
        printf("WARNING! Randomizer is too low- it is now equal to 0.");
    }

    if (randomizer > 1) {
        randomizer = 1;
        printf("WARNING! Randomizer is too high- it is now equal to 1.");
    }

    // Allocates memory for the graph.
    Node *network = malloc(sizeof(Node) * (nodes + 1) * nodes); // Generates a network with nodes + 1 rows and nodes columns. Each entry is a struct Node.

    int z[nodes];
    int count = 1;

    // Generates "z-array"- this determines how far away an "ordered" neighboring node is based on distance down the column.
    for (int i = 0; i < nodes; i = i + 1) {

        z[i] = count;

        if (i % 2 != 0) {

            count = count + 1;

        }

    }

    // This sets node.state, node.connection, node.visited, and node.visited_final to zero.
    for (int i = 0; i < nodes; i = i + 1) {

        for (int j = 0; j < nodes + 1; j = j + 1) {

            network[(j * nodes) + i].state = 0;
            network[(j * nodes) + i].connection = 0;
            network[(j * nodes) + i].visited = 0;
            network[(j * nodes) + i].visited_final = 0;

        }

    }

    // This fills out node.connection for every single "cell" in the nodes X nodes matrix. This does not include the
    // first row, as that will indicate state.
    for (int i = 0; i < nodes; i = i + 1) {

        for (int j = 0; j < nodes; j = j + 1) {

            if (j % 2 == 0) {

                network[((j + 1) * nodes) + i].connection = (nodes + i - z[j]) % nodes;

            }

            if (j % 2 != 0) {

                network[((j + 1) * nodes) + i].connection = (nodes + i + z[j]) % nodes;

            }

        }

    }

    // This sets node.visited = 1 for each column depending on how many neighbors are indicated.
    for (int i = 0; i < nodes; i = i + 1) {

        for (int j = 0; j < neighbors; j = j + 1) {

            if (j % 2 == 0) {

                if (network[((j + 1) * nodes) + i].visited < 1) {

                    network[((j + 1) * nodes) + i].visited = network[((j + 1) * nodes) + i].visited + 1;
                    network[((j + 2) * nodes) + ((nodes + i - z[j]) % nodes)].visited = network[((j + 2) * nodes) + ((nodes + i - z[j]) % nodes)].visited + 1;

                }

            }

            if (j % 2 != 0) {

                if (network[((j + 1) * nodes) + i].visited < 1) {

                    network[((j + 1) * nodes) + i].visited = network[((j + 1) * nodes) + i].visited + 1;
                    network[(j * nodes) + ((nodes + i + z[j]) % nodes)].visited = network[(j * nodes) + ((nodes + i + z[j]) % nodes)].visited + 1;

                }

            }

        }

    }

    // Normalizes the randomizer.
    double randomizer_normalized = randomizer * 100;

    // This entire loop sets node.visited_final.
    for (int i = 0; i < nodes; i = i + 1) {

        for (int j = 0; j < nodes; j = j + 1) {

            int visited = network[((j + 1) * nodes) + i].visited;

            // This while loop "relaxes" node.visited and begins replacing it with node.visited_final.
            while (visited > 0) {

                int threshold = rand() % 100;

                // This determines whether or not a connection will be broken and randomly reformed.
                if (threshold < randomizer_normalized) {

                    int r = 1;
                    int random_neighbor;

                    // this ensures the node doesn't connect with itself.
                    while (r == 1) {

                        r = 0;

                        random_neighbor = rand() % nodes;

                        if (random_neighbor == i) {

                            r = 1;

                        }

                    }

                    // Clears node.visited and generates a new, random, final connection as node.visited_final for even j increments.
                    if (j % 2 == 0) {

                        network[((j + 2) * nodes) + network[((j + 1) * nodes) + i].connection].visited = network[((j + 2) * nodes) + network[((j + 1) * nodes) + i].connection].visited - 1;
                        network[((j + 1) * nodes) + i].visited = network[((j + 1) * nodes) + i].visited - 1;

                        for (int k = 0; k < nodes; k = k + 1) {

                            if (network[((k + 1) * nodes) + i].connection == random_neighbor) {

                                if ((k < nodes - 2) || ((k >= nodes - 2) && (k % 2 == 0))) {

                                    network[((k + 1) * nodes) + i].visited_final = network[((k + 1) * nodes) + i].visited_final + 1;

                                }

                                if ((k < nodes - 2) && (k % 2 == 0)) {

                                    network[((k + 2) * nodes) + random_neighbor].visited_final = network[((k + 2) * nodes) + random_neighbor].visited_final + 1;

                                }

                                if ((k < nodes - 2) && (k % 2 != 0)) {

                                    network[(k * nodes) + random_neighbor].visited_final = network[(k * nodes) + random_neighbor].visited_final + 1;

                                }

                                if (k == nodes - 2) {

                                    network[((k + 2) * nodes) + random_neighbor].visited_final = network[((k + 2) * nodes) + random_neighbor].visited_final + 1;

                                }

                            }

                        }

                    }

                    // Clears node.visited and generates a new, random, final connection as node.visited_final for odd j increments.
                    if (j % 2 != 0) {

                        network[((j + 1) * nodes) + i].visited = network[((j + 1) * nodes) + i].visited - 1;
                        network[(j * nodes) + network[((j + 1) * nodes) + i].connection].visited = network[(j * nodes) + network[((j + 1) * nodes) + i].connection].visited - 1;

                        for (int k = 0; k < nodes; k = k + 1) {

                            if (network[((k + 1) * nodes) + i].connection == random_neighbor) {

                                if ((k < nodes - 2) || ((k >= nodes - 2) && (k % 2 != 0))) {

                                    network[((k + 1) * nodes) + i].visited_final = network[((k + 1) * nodes) + i].visited_final + 1;

                                }

                                if ((k < nodes - 2) && (k % 2 == 0)) {

                                    network[((k + 2) * nodes) + random_neighbor].visited_final = network[((k + 2) * nodes) + random_neighbor].visited_final + 1;

                                }

                                if ((k < nodes - 2) && (k % 2 != 0)) {

                                    network[(k * nodes) + random_neighbor].visited_final = network[(k * nodes) + random_neighbor].visited_final + 1;

                                }

                                if (k == nodes - 1) {

                                    network[(k * nodes) + random_neighbor].visited_final = network[(k * nodes) + random_neighbor].visited_final + 1;

                                }

                            }

                        }

                    }

                } else {  // This else happens if the threshold is not met, i.e. threshold > randomizer_normalized. It finalizes the "ordered" matrix.

                    network[((j + 1) * nodes) + i].visited_final = network[((j + 1) * nodes) + i].visited_final + 1;

                    if (j % 2 == 0) {

                        network[((j + 2) * nodes) + ((nodes + i - z[j]) % nodes)].visited = network[((j + 2) * nodes) + ((nodes + i - z[j]) % nodes)].visited - 1;
                        network[((j + 2) * nodes) + ((nodes + i - z[j]) % nodes)].visited_final = network[((j + 2) * nodes) + ((nodes + i - z[j]) % nodes)].visited_final + 1;

                    }

                    if (j % 2 != 0) {

                        network[(j * nodes) + ((nodes + i + z[j]) % nodes)].visited = network[(j * nodes) + ((nodes + i + z[j]) % nodes)].visited - 1;
                        network[(j * nodes) + ((nodes + i + z[j]) % nodes)].visited_final = network[(j * nodes) + ((nodes + i + z[j]) % nodes)].visited_final + 1;

                    }

                }

                visited = visited - 1;

            }

        }

    }

    return &network[0];

}

// Prints the network (but inverted to the side).
void print_network(Node *network, int nodes, int neighbors) {

    for (int i = 0; i < nodes; i = i + 1) {
        for (int j = 0; j < nodes; j = j + 1) {

            if (j == 0) {

                printf("N%d|", i + 1);

            }

            while (network[((j + 1) * nodes) + i].visited_final > 0) {

                printf("%d-", network[((j + 1) * nodes) + i].connection);

                network[((j + 1) * nodes) + i].visited_final = network[((j + 1) * nodes) + i].visited_final - 1;

            }

            //printf("%d-", network[((j + 1) * nodes) + i].visited_final);

        }

        printf("END");

        printf("\n");

    }

}

// Frees the memory associated with generating the network.
void free_memory(Node *network) {

    free(network);

}

// Finds the maximum of arr[], which is size n.
int maximum(const int arr[], int n) {

    int i;

    int max = arr[0];

    for (i = 0; i < n; i = i + 1) {

        if (arr[i] > max) {

            max = arr[i];

        }

    }

    return max;

}

// Finds the minimum of arr[], which is size n.
int minimum(const int arr[], int n) {

    int i;

    int min = arr[0];

    for (i = 0; i < n; i = i + 1) {

        if (arr[i] < min) {

            min = arr[i];

        }

    }

    return min;

}

// Finds the median of arr[], which is size n.
int median(int arr[], int n) {

    int i, key, j;

    for (i = 1; i < n; i = i + 1) {

        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {

            arr[j + 1] = arr[j];
            j = j - 1;

        }

        arr[j + 1] = key;

    }

    if (n % 2 != 0) {

        return arr[(n - 1) / 2];

    } else {

        return (arr[n / 2] + arr[(n - 1) / 2]) / 2;

    }

}

// After running the simulation "iterations" number of times, analysis() finds the median, maximum, and minimum of the
// three generated arrays holding the "iterations" number of values for 3 separate quantities.
int analysis(int iterations, int maximum_array[], int max_iteration_array[], int infected_recovered_sum_array[]) {

    printf("Median of maximum infected individuals per %d cycles: %d\n", iterations, median(maximum_array, iterations));
    printf("Median of maximum iteration number per %d cycles: %d\n", iterations, median(max_iteration_array, iterations));
    printf("Median of sum of currently infected and recovered per %d cycles: %d\n", iterations, median(infected_recovered_sum_array, iterations));

    printf("\n");

    printf("Maximum of maximum infected individuals per %d cycles: %d\n", iterations, maximum(maximum_array, iterations));
    printf("Maximum of maximum iteration number per %d cycles: %d\n", iterations, maximum(max_iteration_array, iterations));
    printf("Maximum of sum of currently infected and recovered per %d cycles: %d\n", iterations, maximum(infected_recovered_sum_array, iterations));

    printf("\n");

    printf("Minimum of maximum infected individuals per %d cycles: %d\n", iterations, minimum(maximum_array, iterations));
    printf("Minimum of maximum iteration number per %d cycles: %d\n", iterations, minimum(max_iteration_array, iterations));
    printf("Minimum of sum of currently infected and recovered per %d cycles: %d\n", iterations, minimum(infected_recovered_sum_array, iterations));

    printf("\n");

    return 1;

}

#endif //A6_CLION_NETWORK_H