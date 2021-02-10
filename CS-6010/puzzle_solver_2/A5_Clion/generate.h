// Stephen Allegri
// ID: 903207717

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef A5_CLION_MAZE_FUNCTIONS_H
#define A5_CLION_MAZE_FUNCTIONS_H

typedef struct Node {

    int N;
    int E;
    int S;
    int W;
    int previous;
    int next;
    int visited;

} Node;

// Prints the maze, where | and _ denote walls and + denotes a connection
void print_maze (Node *maze_ptr, int nRows, int nCols) {

    for (int i = 0; i < nRows; i = i + 1) {
        // Prints northern walls and connections
        for (int j = 0; j < nCols; j = j + 1) {

            printf(" ");

            if (maze_ptr[(i * nRows) + j].N == -1) {
                printf("_");
            } else {
                printf("+");
            }

        }

        printf("\n");

        // Prints interior nodes, walls, and connections
        for (int j = 0; j < nCols; j = j + 1) {

            if (maze_ptr[(i * nRows) + j].W == -1) {
                printf("|");
            }

            printf("O");

            if ((j == nCols - 1) && maze_ptr[(i * nRows) + j].E == -1) {
                printf("|");
            }

            if (maze_ptr[(i * nRows) + j].E != -1) {
                printf("+");
            }

        }

        printf("\n");

    }

    // Prints bottom wall of the maze
    for (int i = 0; i < nCols; i = i + 1) {

        printf(" ");

        printf("_");

    }

}

// Sets all Node variables to -1 (indicates no changes have been made)
int set_walls (Node *maze_ptr, int nRows, int nCols) {

    for (int i = 0; i <  nRows; i = i + 1) {
        for (int j = 0; j < nCols; j = j + 1) {

            maze_ptr[(nRows * i) + j].N = -1;
            maze_ptr[(nRows * i) + j].E = -1;
            maze_ptr[(nRows * i) + j].S = -1;
            maze_ptr[(nRows * i) + j].W = -1;
            maze_ptr[(nRows * i) + j].next = -1;
            maze_ptr[(nRows * i) + j].visited = -1;

        }

    }

    return 1;

}

// Determines a random start location within the maze
int start (int nRows, int nCols) {

    return rand() % (nRows * nCols);

}

// Utilizes a while loop to generate a path within the maze
// (the while loop closes when there are no available nodes to connect with)
int generate_path (Node *maze_ptr, int nRows, int nCols, int start_location) {

    // Initializes location and sets location as "visited"
    int location = start_location;
    maze_ptr[location].visited = 1;

    // Checks if at least one surrounding node of "location" is unvisited and within the maze boundary
    while ((maze_ptr[location - nCols].visited == -1 && (location - nCols) >= 0)
           || (maze_ptr[location + 1].visited == -1 && ((location % nCols) + 1) < nCols)
           || (maze_ptr[location + nCols].visited == -1 && (location + nCols) < (nRows * nCols))
           || (maze_ptr[location - 1].visited == -1 && ((location % nCols) - 1) >= 0)) {

        int storageArray[4] = {0, 0, 0, 0};

        if (maze_ptr[location - nCols].visited == -1 && (location - nCols) >= 0) {
            storageArray[0] = 1;
        }
        if (maze_ptr[location + 1].visited == -1 && ((location % nCols) + 1) < nCols) {
            storageArray[1] = 1;
        }
        if (maze_ptr[location + nCols].visited == -1 && (location + nCols) < (nRows * nCols)) {
            storageArray[2] = 1;
        }
        if (maze_ptr[location - 1].visited == -1 && ((location % nCols) - 1) >= 0) {
            storageArray[3] = 1;
        }

        int z = 0;

        for (int i = 0; i < 4; i = i + 1) {

            if (storageArray[i] == 1) {
                z = z + 1;
            }

        }

        int direction = rand() % z;

        int n = 0;
        int s = 0;

        // Chooses "random" unvisited adjacent node to visit next
        for (int i = 0; i < 4; i = i + 1) {

            if (storageArray[i] == 1) {

                if (n == direction) {
                    s = i;
                }

                n = n + 1;

            }

        }

        // The next four if statements determine the next "visited" node and set the according Node variables.
        if (s == 0) { // Looks to north node
            if (maze_ptr[location - nCols].visited == -1 && (location - nCols) >= 0) {
                maze_ptr[location].next = location - nCols;
                maze_ptr[location - nCols].previous = location;
                maze_ptr[location].N = location - nCols;
                maze_ptr[location - nCols].S = location;
                location = location - nCols;
            }
        }

        if (s == 1) { // Looks to east node
            if (maze_ptr[location + 1].visited == -1 && ((location % nCols) + 1) < nCols) {
                maze_ptr[location].next = location + 1;
                maze_ptr[location + 1].previous = location;
                maze_ptr[location].E = location + 1;
                maze_ptr[location + 1].W = location;
                location = location + 1;
            }
        }

        if (s == 2) { // looks to south node
            if (maze_ptr[location + nCols].visited == -1 && (location + nCols) < (nRows * nCols)) {
                maze_ptr[location].next = location + nCols;
                maze_ptr[location + nCols].previous = location;
                maze_ptr[location].S = location + nCols;
                maze_ptr[location + nCols].N = location;
                location = location + nCols;
            }
        }

        if (s == 3) { // Looks to west node
            if (maze_ptr[location - 1].visited == -1 && ((location % nCols) - 1) >= 0) {
                maze_ptr[location].next = location - 1;
                maze_ptr[location - 1].previous = location;
                maze_ptr[location].W = location - 1;
                maze_ptr[location - 1].E = location;
                location = location - 1;
            }
        }

        maze_ptr[location].visited = 1;

    }

    return location;

}

// Begins at the ending location of generate_path() and works back until a node is reached with at least one available
// adjacent "unvisited" node- utilizes recursive function
int backtrack (Node *maze_ptr, int nRows, int nCols, int end) {

    if (maze_ptr[end - nCols].visited == -1 && (end - nCols) >= 0
        || maze_ptr[end + 1].visited == -1 && ((end % nCols) + 1) < nCols
        || maze_ptr[end + nCols].visited == -1 && (end + nCols) < (nRows * nCols)
        || maze_ptr[end - 1].visited == -1 && ((end % nCols) - 1) >= 0) {

        return end;

    } else {

        backtrack(maze_ptr, nRows, nCols, maze_ptr[end].previous);

    }

}

// Writes nRows, nCols, start, finish, and maze connections to a .txt file to be read by the maze solver.
void generate_output (Node *maze_ptr, int nRows, int nCols, int start, int finish) {

    FILE *f;
    f = fopen("maze_data.txt", "w");

    fprintf(f, "%d", nRows);
    fprintf(f, " ");
    fprintf(f, "%d", nCols);
    fprintf(f, "\n");

    fprintf(f, "%d", start);
    fprintf(f, " ");
    fprintf(f, "%d", finish);
    fprintf(f, "\n");

    // Writes maze connection data (with a space after each connection!)
    for (int i = 0; i < nRows; i = i + 1) {
        for (int j = 0; j < nCols; j = j + 1) {

            if (maze_ptr[(i * nRows) + j].N != -1) {
                fprintf(f, "%d ", maze_ptr[(i * nRows) + j].N);
            }
            if (maze_ptr[(i * nRows) + j].E != -1) {
                fprintf(f, "%d ", maze_ptr[(i * nRows) + j].E);
            }
            if (maze_ptr[(i * nRows) + j].S != -1) {
                fprintf(f, "%d ", maze_ptr[(i * nRows) + j].S);
            }
            if (maze_ptr[(i * nRows) + j].W != -1) {
                fprintf(f, "%d ", maze_ptr[(i * nRows) + j].W);
            }

            fprintf(f, "\n");

        }
    }

    fclose(f);

}

#endif //A5_CLION_MAZE_FUNCTIONS_H
