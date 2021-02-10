#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("You need to input parameter: file!\n");
    }

    char *infile_name = argv[1]; /// The argv[] can be change depend on your  Directory settings

    FILE *data;
    data = fopen(infile_name, "r");

    if (data == NULL)
    {
        printf("file is error.");
        return -1;
    }

    ///////////////////////////////////////////////////////////////////////////
    ///// Read the Adjacency List file, and Grasp the basic information of maze

    int line;
    int temp;
    int i;
    int *a;
    int num = 1;
    fscanf(data, "%d", &line);

    for (; fscanf(data, "%d", &temp) != EOF;)
    {
        num++;
    }

    // printf("%d\n", num);
    a = (int *)malloc(sizeof(int) * num);
    fseek(data, 0, SEEK_SET);

    for (i = 0; i < num; i++)
    {
        fscanf(data, "%d", &a[i]);
        // printf("%d  ", a[i]);
    }

    int nRows = a[0], nCols = a[1], start = a[2], finish = a[3];

    int k = 4;
    int n = 0;
    int size = nRows * nCols;
    int matrix[size][4];

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix[i][j] = 0;
            // printf("%d", matrix[i][j]);
        }
        // printf("\n");
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////// Store the Adjacency List information into a matrix to Indicates direction, 0:EAST, 1:WEST, 2:SOUTH, 3:NORTH

    while (1)
    {
        while (1)
        {
            if (a[k] == n + 1) // EAST
            {
                matrix[n][0] = 1;
                k++;
                continue;
            }
            if (a[k] == n - 1) // WEST
            {
                matrix[n][1] = 1;
                k++;
                continue;
            }
            if (a[k] == n + nCols) // SOUTH
            {
                matrix[n][2] = 1;
                k++;
                continue;
            }
            if (a[k] == n - nCols) // NORTH
            {
                matrix[n][3] = 1;
                k++;
                continue;
            }
            else
            {
                break;
            }
        }
        n++;
        if (n == size)
        {
            break;
        }
    }

    // for (int i = 0; i < size; i++)
    // {
    //     for (int j = 0; j < 4; j++)
    //     {
    //         printf("%d", matrix[i][j]);
    //     }
    //     printf("\n");
    // }

    int row_start = 0, col_start = 0, row_finish = 0, col_finish = 0;
    col_start = start % nRows;
    row_start = (start - col_start) / nRows;
    col_finish = finish % nRows;
    row_finish = (finish - col_finish) / nRows;
    // printf("%d %d %d %d %d %d\n", start, row_start, col_start, finish, row_finish, col_finish);

    ////////////////////////////////////////
    ///////  Build a maze to record the path

    int maze[nRows][nCols];
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            maze[i][j] = 0;
            // printf("%d", maze[i][j]);
        }
        // printf("\n");
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////// The Breadth First method is used to traverse all possible points around from one point radially.
    ///////// And the number of the paths will be marked out on the map matrix.

    maze[row_start][col_start] = 0;
    int path = 0, test_end = 0;
    int row = 0, col = 0;
    int sto_matrix[nRows][size];
    int sto_row = 1, sto_col = 0;
    int add = 0;
    int path_to_finish = 0;
    sto_matrix[0][0] = start;

    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < size; j++)
        {
            sto_matrix[i][j] = 0;
        }
    }
    sto_matrix[0][0] = start;

    int test = 0;
    while (1)
    {
        int q = 0;
        add += 1;
        for (int i = 0; i < sto_row; i++)
        {
            path = sto_matrix[i][sto_col];
            col = path % nRows;
            row = (path - col) / nRows;

            // printf("%d\n", path);
            // printf("%d %d %d %d", matrix[path][0], matrix[path][1], matrix[path][2], matrix[path][3]);
            // printf("\n");

            if (matrix[path][0] == 1) // EAST
            {
                sto_matrix[q][sto_col + 1] = path + 1;
                maze[row][col + 1] = add;
                matrix[path + 1][1] = -1;
                q++;
            }
            if (matrix[path][1] == 1) // WEST
            {
                sto_matrix[q][sto_col + 1] = path - 1;
                maze[row][col - 1] = add;
                matrix[path - 1][0] = -1;
                q++;
            }
            if (matrix[path][2] == 1) // SOUTH
            {
                sto_matrix[q][sto_col + 1] = path + nCols;
                maze[row + 1][col] = add;
                matrix[path + nCols][3] = -1;
                q++;
            }
            if (matrix[path][3] == 1) // NORTH
            {
                sto_matrix[q][sto_col + 1] = path - nCols;
                maze[row - 1][col] = add;
                matrix[path - nCols][2] = -1;
                q++;
            }
            if (sto_matrix[q - 1][sto_col + 1] == finish)
            {
                path_to_finish = sto_col + 1;
                test_end = 1;
            }
        }

        sto_row = q;
        sto_col++;
        test++;
        if (test_end == 1)
        {
            break;
        }
    }

    printf("Start point: (%d,%d);", row_start, col_start);
    printf("\nFinish point: (%d,%d);", row_finish, col_finish);
    printf("\nThe number of step to finish: %d\n", path_to_finish);

    // for (int i = 0; i < size; i++)
    // {
    //     for (int j = 0; j < 4; j++)
    //     {
    //         printf("%d ", matrix[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("\nThe map of step to finish:\n");
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    ///////////////////////////////////////////////////////////////////////////
    //////// Backtrack from finish to start, to print out the point of the path.
    //////// The result will be represented by a matrix named backtrack.
    //////// Backtrack matrix can show all the possible result,
    //////// When there is a bifurcation in the matrix, there is another possible path.
    //////// The last printed result will be the result in the first row of the matrix, which is one of the path.

    int max_edge = 0;
    if (nRows > nCols || nRows == nCols)
    {
        max_edge = nRows;
    }
    else
    {
        max_edge = nCols;
    }

    int backtrack[max_edge][path_to_finish + 1];
    for (int i = 0; i < max_edge; i++)
    {
        for (int j = 0; j < path_to_finish + 1; j++)
        {
            backtrack[i][j] = 0;
        }
    }

    int sto_num = maze[row_finish][col_finish];
    int sto_row_f = 0, sto_col_f = 0;
    int count = 1;
    int back_path = 0;
    int sto_row1 = 1;
    backtrack[0][0] = finish;
    int check;

    while (1)
    {
        int q = 0;
        for (int i = 0; i < sto_row1; i++)
        {
            back_path = backtrack[i][count - 1];
            sto_col_f = back_path % nRows;
            sto_row_f = (back_path - sto_col_f) / nRows;

            if (maze[sto_row_f][sto_col_f - 1] == sto_num - count) // BACKTRACK WEST
            {
                backtrack[q][count] = backtrack[i][count - 1] - 1;
                q++;
                // printf("%d\n", q);
            }
            if (maze[sto_row_f][sto_col_f + 1] == sto_num - count) // BACKTRACK EAST
            {
                backtrack[q][count] = backtrack[i][count - 1] + 1;
                q++;
                // printf("%d\n", q);
            }
            if (maze[sto_row_f - 1][sto_col_f] == sto_num - count) // BACKTRACK NORTH
            {
                backtrack[q][count] = backtrack[i][count - 1] - nCols;
                q++;
                // printf("%d\n", q);
            }
            if (maze[sto_row_f + 1][sto_col_f] == sto_num - count) // BACKTRACK SOUTH
            {
                backtrack[q][count] = backtrack[i][count - 1] + nCols;
                q++;
                // printf("%d\n", q);
            }
            for (int j = 1; j < q; j++)
            {
                for (int k = 0; k < 4; k++) //  Check where does the point come from, make sure the current point comes from the correct point.
                {
                    check = 0;
                    if (matrix[backtrack[i][count - 1]][k] == -1)
                    {
                        if (k == 0)
                        {
                            backtrack[check][count] = backtrack[i][count - 1] + 1;
                            check++;
                            backtrack[check][count] = 0;
                        }
                        if (k == 1)
                        {
                            backtrack[check][count] = backtrack[i][count - 1] - 1;
                            check++;
                            backtrack[check][count] = 0;
                        }
                        if (k == 2)
                        {
                            backtrack[check][count] = backtrack[i][count - 1] + nCols;
                            check++;
                            backtrack[check][count] = 0;
                        }
                        if (k == 3)
                        {
                            backtrack[check][count] = backtrack[i][count - 1] - nCols;
                            check++;
                            backtrack[check][count] = 0;
                        }
                    }
                }
            }
        }
        count++;
        sto_row1 = q;
        if (count == path_to_finish + 1)
        {
            break;
        }
    }

    printf("Backtrack of all possible path (From left to right is finish to start):\n");
    for (int i = 0; i < max_edge; i++)
    {
        for (int j = 0; j < path_to_finish + 1; j++)
        {
            if (backtrack[i][path_to_finish] == start)
            {
                printf("%d ", backtrack[i][j]);
            }
        }
    }
    printf("\n");

    printf("\nThe track of the point:\n");
    int row_backtrack, col_backtrack, store;
    for (int j = 0; j < path_to_finish; j++)
    {
        store = path_to_finish - j;
        col_backtrack = backtrack[0][store] % nRows;
        row_backtrack = (backtrack[0][store] - col_backtrack) / nRows;
        printf("(%d,%d)->", row_backtrack, col_backtrack);
    }
    printf("(%d,%d)\n", row_finish, col_finish);

    fclose(data);
    return 0;
}
