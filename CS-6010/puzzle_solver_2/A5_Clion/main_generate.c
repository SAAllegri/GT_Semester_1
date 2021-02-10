// Stephen Allegri
// ID: 903207717

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "generate.h"

int main(int argc, char **argv) {

    // Makes sure the right number of parameters are run through main()
    if (argc != 4) {
        printf("Invalid argument number.\n");
    }

    // Sets seed based on time for rand()
    srand(time(NULL) * 100);

    char *ptr = NULL;

    // Rows and columns acquired from main() parameters
    int nRows = strtol(argv[1], &ptr, 10);
    int nCols = strtol(argv[2], &ptr, 10);
    int empty = 0;

    // Allocates memory for maze
    Node *maze_ptr = (Node*)malloc(nRows * nCols * sizeof(Node));

    set_walls(maze_ptr, nRows, nCols);

    int start_location = start(nRows, nCols);

    printf("Maze starts at: %d\n", start_location);

    int stop = generate_path(maze_ptr, nRows, nCols, start_location);
    int back;

    // Runs generate_path() and backtrack() until all nodes are visited
    while (empty != 1) {

        int n = 0;
        for (int i = 0; i < nRows; i = i + 1) {
            for (int j = 0; j < nCols; j = j + 1) {

                if (maze_ptr[(i * nRows) + j].visited == -1) {
                    n = n + 1;
                }

            }
        }

        if (n == 0) {
            empty = 1;
        } else {
            back = backtrack(maze_ptr, nRows, nCols, stop);
            stop = generate_path(maze_ptr, nRows, nCols, back);
        }

    }

    printf("Maze finishes at: %d\n", stop);

    print_maze(maze_ptr, nRows, nCols);

    generate_output(maze_ptr, nRows, nCols, start_location, stop);

    free(maze_ptr);

    return 0;

}
