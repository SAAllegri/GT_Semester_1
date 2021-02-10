// Stephen allegri
// ID: 903207717

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Recursive function used to solve the puzzle (utilizing random value generation and checking functions)
int recursive_solve(int grid_size, int *grid, int *grid_OG, int recur);

// Checks the board to make sure rules are met
int check_rules(int grid_size, const int *grid);

// Checks the board to make sure all spaces are filled
int check_filled(int grid_size, const int *grid);

// Function to block triple Os and Xs
int double_scan(int grid_size, int *grid);

// Additional function to block triple Os and Xs
int double_scan_2(int grid_size, int *grid);

// Function to fill rows that have max number of Os or Xs
int complement_fill(int grid_size, int *grid);

// Prints board
void print_board(int grid_size, const int *grid);

int main(){

    // Accepts user inputted .txt location
    printf("Enter puzzle.txt location: ");
    char location[200];
    scanf("%s", location);
    printf("\n");
    // E:\GT_Courses\Semester_1\CSE-6010\Assignments\Assignment_4\A4_Clion_Updated\puzzle3.txt

    // Reads file
    FILE *infile;
    infile = fopen(location, "r");
    int grid_size = 0;
    fscanf(infile, "%d", &grid_size);

    // Allocates memory for 2 grids
    int *grid = malloc(grid_size * grid_size * sizeof(int));
    int *grid_OG = malloc(grid_size * grid_size * sizeof(int));

    char c;
    int count = 0;

    // Copies file data to grids
    while (1) {

        c = fgetc(infile); // reading the file
        if (c == EOF) {
            break;
        }
        if (c == "\n") {
            continue;
        }
        if (c == '?') {  // Empty spaces represented as -1
            grid[count] = -1;
            grid_OG[count] = -1;
            count++;
        }
        if (c == 'X') { // X's represented as 1
            grid[count] = 1;
            grid_OG[count] = 1;
            count++;
        }
        if (c == 'O') { // O's represented as 0
            grid[count] = 0;
            grid_OG[count] = 0;
            count++;
        }

    }

    fclose(infile); // Closing the file

    // Print initial board
    printf("Given Board:\n");
    print_board(grid_size, grid);

    // Sets up recursion function
    int recur = 1;
    srand(time(NULL) * 100);

    recursive_solve(grid_size, grid, grid_OG, recur);

    printf("\n");
    printf("Puzzle solver is finished.\n");

    return 0;

}

// Recursive function used to solve the puzzle (utilizing random value generation and checking functions)
int recursive_solve(int grid_size, int *grid, int *grid_OG, int recur) {

    if (recur == 0) {
        return 0;
    } else {

        int random;

        // Utilizes random number generator to complete puzzle in unison with rules functions
        for (int i = 0; i < grid_size; i = i + 1) {
            for (int j = 0; j < grid_size; j = j + 1) {
                double_scan(grid_size, grid);
                double_scan_2(grid_size, grid);
                complement_fill(grid_size, grid);
                if (*(grid + (grid_size * i + j)) == -1) {
                    random = rand() % 2;
                    if (random == 0) {
                        *(grid + (grid_size * i + j)) = 0;
                    }
                    if (random == 1) {
                        *(grid + (grid_size * i + j)) = 1;
                    }
                }
            }
        }

        // Checks filled grid with rules functions
        if (check_filled(grid_size, grid) == 1 && check_rules(grid_size, grid) == 0) {
            printf("\n");
            printf("Solution:\n");
            print_board(grid_size, grid);
            printf("\n");
            return 0;
        } else {
            // Clears grid and replaces values with original values
            for (int i = 0; i < grid_size; ++i) {
                for (int j = 0; j < grid_size; ++j) {
                    *(grid + (grid_size * i + j)) = *(grid_OG + (grid_size * i + j));
                }
            }

            // Recur function
            recursive_solve(grid_size, grid, grid_OG, recur);

            return 1;

        }
    }

}

// Checks the board to make sure rules are met
int check_rules(int grid_size, const int *grid) {

    int error = 0;

    // Checks for horizontal triple Os and Xs
    for (int i = 0; i < grid_size; i = i + 1) {
        for (int j = 0; j < grid_size - 2; j = j + 1) {

            if ((*(grid + (grid_size * i + j)) == *(grid + (grid_size * i + (j + 1)))) &&
                (*(grid + (grid_size * i + j)) == *(grid + (grid_size * i + (j + 2))))) {
                error = 1;
            }

        }
    }

    // Checks for vertical triple Os and Xs
    for (int j = 0; j < grid_size; j = j + 1) {
        for (int i = 0; i < grid_size - 2; i = i + 1) {

            if ((*(grid + (grid_size * i + j)) == *(grid + (grid_size * (i + 1) + j))) &&
                (*(grid + (grid_size * i + j)) == *(grid + (grid_size * (i + 2) + j)))) {
                error = 1;
            }

        }
    }

    int O_count = 0;
    int X_count = 0;

    // Checks for horizontal equal Os and Xs
    for (int i = 0; i < grid_size; i = i + 1) {
        for (int j = 0; j < grid_size; j = j + 1) {

            if (*(grid + (grid_size * i + j)) == 0) {
                O_count = O_count + 1;
            }
            if (*(grid + (grid_size * i + j)) == 1) {
                X_count = X_count + 1;
            }

        }

        if (O_count != X_count) {
            error = 1;
        }

        O_count = 0;
        X_count = 0;

    }

    // Checks for vertical equal Os and Xs
    for (int j = 0; j < grid_size; j = j + 1) {
        for (int i = 0; i < grid_size; i = i + 1) {

            if (*(grid + ((grid_size * i) + j)) == 0) {
                O_count = O_count + 1;
            }
            if (*(grid + ((grid_size * i) + j)) == 1) {
                X_count = X_count + 1;
            }

        }

        if (O_count != X_count) {
            error = 1;
        }

        O_count = 0;
        X_count = 0;

    }

    // Checks for duplicate rows
    for (int i = 0; i < grid_size; i = i + 1) {

        int check_array[grid_size];

        for (int j = 0; j < grid_size; j = j + 1) {
            check_array[j] = 0;
        }

        for (int j = 0; j < grid_size; j = j + 1) {
            check_array[j] = *(grid + (grid_size * i + j));
        }

        int size_count = 0;

        for (int j = 0; j < i; j = j + 1) {

            for (int k = 0; k < grid_size; k = k + 1) {
                if (check_array[k] == *(grid + (grid_size * j + k))) {
                    size_count = size_count + 1;
                }
            }

            if (size_count == grid_size) {
                error = 1;
            }

            size_count = 0;

        }

        for (int j = 0; j > i && j < grid_size; j = j + 1) {

            for (int k = 0; k < grid_size; k = k + 1) {
                if (check_array[k] == *(grid + (grid_size * j + k))) {
                    size_count = size_count + 1;
                }
            }

            if (size_count == grid_size) {
                error = 1;
            }

            size_count = 0;

        }
    }

    // Checks for duplicate column
    for (int j = 0; j < grid_size; j = j + 1) {

        int check_array[grid_size];

        for (int i = 0; i < grid_size; i = i + 1) {
            check_array[i] = 0;
        }

        for (int i = 0; i < grid_size; i = i + 1) {
            check_array[i] = *(grid + (grid_size * i + j));
        }

        int size_count = 0;

        for (int i = 0; i < j; i = i + 1) {

            for (int k = 0; k < grid_size; k = k + 1) {
                if (check_array[k] == *(grid + (grid_size * k + i))) {
                    size_count = size_count + 1;
                }
            }

            if (size_count == grid_size) {
                error = 1;
            }

            size_count = 0;

        }

        for (int i = 0; i > j && j < grid_size; i = i + 1) {

            for (int k = 0; k < grid_size; k = k + 1) {
                if (check_array[k] == *(grid + (grid_size * k + i))) {
                    size_count = size_count + 1;
                }
            }

            if (size_count == grid_size) {
                error = 1;
            }

            size_count = 0;

        }
    }

    return error;

}

// Checks the board to make sure all spaces are filled
int check_filled(int grid_size, const int *grid) {

    int filled = 1;

    for (int i = 0; i < grid_size; i = i + 1) {
        for (int j = 0; j < grid_size; j = j + 1) {

            if (*(grid + (grid_size * i + j)) == -1) {
                filled = 0;
            }

        }
    }

    return filled;

}

// Function to block triple Os and Xs
int double_scan(int grid_size, int *grid) {

    // Horizontal Scan
    for (int i = 0; i < grid_size; i = i + 1) {
        for (int j = 0; j < grid_size; j = j + 1) {

            if (j == 0){
                if (*(grid + (grid_size * i + j)) == 0 && *(grid + (grid_size * i + (j + 1))) == 0 && *(grid + (grid_size * i + (j + 2))) == -1) {  //
                    *(grid + (grid_size * i + (j + 2))) = 1;
                }
                if (*(grid + (grid_size * i + j)) == 1 && *(grid + (grid_size * i + (j + 1))) == 1 && *(grid + (grid_size * i + (j + 2))) == -1) { //
                    *(grid + (grid_size * i + (j + 2))) = 0;
                }
            }
            if (j == 1){
                if (*(grid + (grid_size * i + j)) == 0 && *(grid + (grid_size * i + (j + 1))) == 0) {
                    if (*(grid + (grid_size * i + (j + 2))) == -1) { //
                        *(grid + (grid_size * i + (j + 2))) = 1;
                    }
                    if (*(grid + (grid_size * i + (j - 1))) == -1) { //
                        *(grid + (grid_size * i + (j - 1))) = 1;
                    }
                }
                if (*(grid + (grid_size * i + j)) == 1 && *(grid + (grid_size * i + (j + 1))) == 1){
                    if (*(grid + (grid_size * i + (j + 2))) == -1) { //
                        *(grid + (grid_size * i + (j + 2))) = 0;
                    }
                    if (*(grid + (grid_size * i + (j - 1))) == -1) { //
                        *(grid + (grid_size * i + (j - 1))) = 0;
                    }
                }
                if (*(grid + (grid_size * i + (j - 1))) == 0 && *(grid + (grid_size * i + j)) == 0 && *(grid + (grid_size * i + (j + 1))) == -1){ //
                    *(grid + (grid_size * i + (j + 1))) = 1;
                }
                if (*(grid + (grid_size * i + (j - 1))) == 1 && *(grid + (grid_size * i + j)) == 1 && *(grid + (grid_size * i + (j + 1))) == -1){ //
                    *(grid + (grid_size * i + (j + 1))) = 0;
                }
            }
            if (1 < j && j < (grid_size - 2)){
                if (*(grid + (grid_size * i + j)) == 0 && *(grid + (grid_size * i + (j + 1))) == 0){
                    if (*(grid + (grid_size * i + (j + 2))) == -1) { //
                        *(grid + (grid_size * i + (j + 2))) = 1;
                    }
                    if (*(grid + (grid_size * i + (j - 1))) == -1) { //
                        *(grid + (grid_size * i + (j - 1))) = 1;
                    }
                }
                if (*(grid + (grid_size * i + j)) == 1 && *(grid + (grid_size * i + (j + 1))) == 1){
                    if (*(grid + (grid_size * i + (j + 2))) == -1) { //
                        *(grid + (grid_size * i + (j + 2))) = 0;
                    }
                    if (*(grid + (grid_size * i + (j - 1))) == -1) { //
                        *(grid + (grid_size * i + (j - 1))) = 0;
                    }
                }
                if (*(grid + (grid_size * i + (j - 1))) == 0 && *(grid + (grid_size * i + j)) == 0){
                    if (*(grid + (grid_size * i + (j + 1))) == -1) { //
                        *(grid + (grid_size * i + (j + 1))) = 1;
                    }
                    if (*(grid + (grid_size * i + (j - 2))) == -1) { //
                        *(grid + (grid_size * i + (j - 2))) = 1;
                    }
                }
                if (*(grid + (grid_size * i + (j - 1))) == 1 && *(grid + (grid_size * i + j)) == 1){
                    if (*(grid + (grid_size * i + (j + 1))) == -1) { //
                        *(grid + (grid_size * i + (j + 1))) = 0;
                    }
                    if (*(grid + (grid_size * i + (j - 2))) == -1) { //
                        *(grid + (grid_size * i + (j - 2))) = 0;
                    }
                }
            }
            if (j == (grid_size - 2)){
                if (*(grid + (grid_size * i + (j - 1))) == 0 && *(grid + (grid_size * i + j)) == 0){
                    if (*(grid + (grid_size * i + (j - 2))) == -1) { //
                        *(grid + (grid_size * i + (j - 2))) = 1;
                    }
                    if (*(grid + (grid_size * i + (j + 1))) == -1) { //
                        *(grid + (grid_size * i + (j + 1))) = 1;
                    }
                }
                if (*(grid + (grid_size * i + (j - 1))) == 1 && *(grid + (grid_size * i + j)) == 1){
                    if (*(grid + (grid_size * i + (j - 2))) == -1) { //
                        *(grid + (grid_size * i + (j - 2))) = 0;
                    }
                    if (*(grid + (grid_size * i + (j + 1))) == -1) { //
                        *(grid + (grid_size * i + (j + 1))) = 0;
                    }
                }
                if (*(grid + (grid_size * i + j)) == 0 && *(grid + (grid_size * i + (j + 1))) == 0 && *(grid + (grid_size * i + (j - 1))) == -1){ //
                    *(grid + (grid_size * i + (j - 1))) = 1;
                }
                if (*(grid + (grid_size * i + j)) == 1 && *(grid + (grid_size * i + (j + 1))) == 1 && *(grid + (grid_size * i + (j - 1))) == -1){ //
                    *(grid + (grid_size * i + (j - 1))) = 0;
                }
            }
            if (j == (grid_size - 1)){
                if (*(grid + (grid_size * i + (j - 1))) == 0 && *(grid + (grid_size * i + j)) == 0 && *(grid + (grid_size * i + (j - 2))) == -1){ //
                    *(grid + (grid_size * i + (j - 2))) = 1;
                }
                if (*(grid + (grid_size * i + (j - 1))) == 1 && *(grid + (grid_size * i + j)) == 1 && *(grid + (grid_size * i + (j - 2))) == -1){ //
                    *(grid + (grid_size * i + (j - 2))) = 0;
                }
            }

        }
    }

    // Vertical Scan
    for (int j = 0; j < grid_size; j = j + 1) {
        for (int i = 0; i < grid_size; i = i + 1) {

            if (i == 0){
                if (*(grid + (grid_size * i + j)) == 0 && *(grid + (grid_size * (i + 1) + j)) == 0 && *(grid + (grid_size * (i + 2) + j)) == -1) { //
                    *(grid + (grid_size * (i + 2) + j)) = 1;
                }
                if (*(grid + (grid_size * i + j)) == 1 && *(grid + (grid_size * (i + 1) + j)) == 1 && *(grid + (grid_size * (i + 2) + j)) == -1) { //
                    *(grid + (grid_size * (i + 2) + j)) = 0;
                }
            }
            if (i == 1){
                if (*(grid + (grid_size * i + j)) == 0 && *(grid + (grid_size * (i + 1) + j)) == 0) {
                    if (*(grid + (grid_size * (i + 2) + j)) == -1) { //
                        *(grid + (grid_size * (i + 2) + j)) = 1;
                    }
                    if (*(grid + (grid_size * (i -1) + j)) == -1) { //
                        *(grid + (grid_size * (i - 1) + j)) = 1;
                    }
                }
                if (*(grid + (grid_size * i + j)) == 1 && *(grid + (grid_size * (i + 1) + j)) == 1){
                    if (*(grid + (grid_size * (i + 2) + j)) == -1) { //
                        *(grid + (grid_size * (i + 2) + j)) = 0;
                    }
                    if (*(grid + (grid_size * (i - 1) + j)) == -1) { //
                        *(grid + (grid_size * (i - 1) + j)) = 0;
                    }
                }
                if (*(grid + (grid_size * (i - 1) + j)) == 0 && *(grid + (grid_size * i + j)) == 0 && *(grid + (grid_size * (i + 1) + j)) == -1){ //
                    *(grid + (grid_size * (i + 1) + j)) = 1;
                }
                if (*(grid + (grid_size * (i - 1) + j)) == 1 && *(grid + (grid_size * i + j)) == 1 && *(grid + (grid_size * (i + 1) + j)) == -1){ //
                    *(grid + (grid_size * (i + 1) + j)) = 0;
                }
            }
            if (1 < i && i < (grid_size - 2)){
                if (*(grid + (grid_size * i + j)) == 0 && *(grid + (grid_size * (i + 1) + j)) == 0){
                    if (*(grid + (grid_size * (i + 2) + j)) == -1) { //
                        *(grid + (grid_size * (i + 2) + j)) = 1;
                    }
                    if (*(grid + (grid_size * (i - 1) + j)) == -1) { //
                        *(grid + (grid_size * (i - 1) + j)) = 1;
                    }
                }
                if (*(grid + (grid_size * i + j)) == 1 && *(grid + (grid_size * (i + 1) + j)) == 1){
                    if (*(grid + (grid_size * (i + 2) + j)) == -1) { //
                        *(grid + (grid_size * (i + 2) + j)) = 0;
                    }
                    if (*(grid + (grid_size * (i - 1) + j)) == -1) { //
                        *(grid + (grid_size * (i - 1) + j)) = 0;
                    }
                }
                if (*(grid + (grid_size * (i - 1) + j)) == 0 && *(grid + (grid_size * i + j)) == 0){
                    if (*(grid + (grid_size * (i + 1) + j)) == -1) { //
                        *(grid + (grid_size * (i + 1) + j)) = 1;
                    }
                    if (*(grid + (grid_size * (i - 2) + j)) == -1) { //
                        *(grid + (grid_size * (i - 2) + j)) = 1;
                    }
                }
                if (*(grid + (grid_size * (i - 1) + j)) == 1 && *(grid + (grid_size * i + j)) == 1){
                    if (*(grid + (grid_size * (i + 1) + j)) == -1) { //
                        *(grid + (grid_size * (i + 1) + j)) = 0;
                    }
                    if (*(grid + (grid_size * (i - 2) + j)) == -1) { //
                        *(grid + (grid_size * (i - 2) + j)) = 0;
                    }
                }
            }
            if (i == (grid_size - 2)){
                if (*(grid + (grid_size * (i - 1) + j)) == 0 && *(grid + (grid_size * i + j)) == 0){
                    if (*(grid + (grid_size * (i - 2) + j)) == -1) { //
                        *(grid + (grid_size * (i - 2) + j)) = 1;
                    }
                    if (*(grid + (grid_size * (i + 1) + j)) == -1) { //
                        *(grid + (grid_size * (i + 1) + j)) = 1;
                    }
                }
                if (*(grid + (grid_size * (i - 1) + j)) == 1 && *(grid + (grid_size * i + j)) == 1){
                    if (*(grid + (grid_size * (i - 2) + j)) == -1) { //
                        *(grid + (grid_size * (i - 2) + j)) = 0;
                    }
                    if (*(grid + (grid_size * (i + 1) + j)) == -1) { //
                        *(grid + (grid_size * (i + 1) + j)) = 0;
                    }
                }
                if (*(grid + (grid_size * i + j)) == 0 && *(grid + (grid_size * (i + 1) + j)) == 0 && *(grid + (grid_size * (i - 1) + j)) == -1){ //
                    *(grid + (grid_size * (i - 1) + j)) = 1;
                }
                if (*(grid + (grid_size * i + j)) == 1 && *(grid + (grid_size * (i + 1) + j)) == 1 && *(grid + (grid_size * (i - 1) + j)) == -1){ //
                    *(grid + (grid_size * (i - 1) + j)) = 0;
                }
            }
            if (i == (grid_size - 1)){
                if (*(grid + (grid_size * (i - 1) + j)) == 0 && *(grid + (grid_size * i + j)) == 0 && *(grid + (grid_size * (i - 2) + j)) == -1){ //
                    *(grid + (grid_size * (i - 2) + j)) = 1;
                }
                if (*(grid + (grid_size * (i - 1) + j)) == 1 && *(grid + (grid_size * i + j)) == 1 && *(grid + (grid_size * (i - 2) + j)) == -1){ //
                    *(grid + (grid_size * (i - 2) + j)) = 0;
                }
            }

        }
    }

    return 0;

}

// Additional function to block triple Os and Xs
int double_scan_2(int grid_size, int *grid) {

    // Horizontal Scan
    for (int i = 0; i < grid_size; i = i + 1) {
        for (int j = 0; j < grid_size; j = j + 1) {

            if (j < (grid_size - 2)){
                if (*(grid + (grid_size * i + j)) == 0 && *(grid + (grid_size * i + (j + 2))) == 0){
                    if (*(grid + (grid_size * i + (j + 1))) == -1) { //
                        *(grid + (grid_size * i + (j + 1))) = 1;
                    }
                }
                if (*(grid + (grid_size * i + j)) == 1 && *(grid + (grid_size * i + (j + 2))) == 1){
                    if (*(grid + (grid_size * i + (j + 1))) == -1) { //
                        *(grid + (grid_size * i + (j + 1))) = 0;
                    }
                }
            }

        }
    }

    // Vertical Scan
    for (int j = 0; j < grid_size; j = j + 1) {
        for (int i = 0; i < grid_size; i = i + 1) {

            if (i < (grid_size - 2)){
                if (*(grid + (grid_size * i + j)) == 0 && *(grid + (grid_size * (i + 2) + j)) == 0){
                    if (*(grid + (grid_size * (i + 1) + j)) == -1) { //
                        *(grid + (grid_size * (i + 1) + j)) = 1;
                    }
                }
                if (*(grid + (grid_size * i + j)) == 1 && *(grid + (grid_size * (i + 2) + j)) == 1){
                    if (*(grid + (grid_size * (i + 1) + j)) == -1) { //
                        *(grid + (grid_size * (i + 1) + j)) = 0;
                    }
                }
            }

        }
    }

    return 0;

}

// Function to fill rows that have max number of Os or Xs
int complement_fill(int grid_size, int *grid){

    int count_horizontal_O = 0;
    int count_horizontal_X = 0;
    int count_vertical_O = 0;
    int count_vertical_X = 0;

    // Horizontal fill
    for (int i = 0; i < grid_size; i = i + 1) {

        for (int j = 0; j < grid_size; j = j + 1) {

            if (*(grid + (grid_size * i + j)) == 0){
                count_horizontal_O = count_horizontal_O + 1;
            }

            if (*(grid + (grid_size * i + j)) == 1){
                count_horizontal_X = count_horizontal_X + 1;
            }

        }

        if (count_horizontal_O == (grid_size/2)){
            for (int j = 0; j < grid_size; j = j + 1) {
                if (*(grid + (grid_size * i + j)) == -1){
                    *(grid + (grid_size * i + j)) = 1;
                }
            }
        }

        if (count_horizontal_X == (grid_size/2)){
            for (int j = 0; j < grid_size; j = j + 1) {
                if (*(grid + (grid_size * i + j)) == -1){
                    *(grid + (grid_size * i + j)) = 0;
                }
            }
        }

        count_horizontal_O = 0;
        count_horizontal_X = 0;

    }

    // Vertical fill
    for (int j = 0; j < grid_size; j = j + 1) {
        for (int i = 0; i < grid_size; i = i + 1) {

            if (*(grid + (grid_size * i + j)) == 0){
                count_vertical_O = count_vertical_O + 1;
            }

            if (*(grid + (grid_size * i + j)) == 1){
                count_vertical_X = count_vertical_X + 1;
            }

        }

        if (count_vertical_O == (grid_size/2)){
            for (int i = 0; i < grid_size; i = i + 1) {
                if (*(grid + (grid_size * i + j)) == -1){
                    *(grid + (grid_size * i + j)) = 1;
                }
            }
        }

        if (count_vertical_X == (grid_size/2)){
            for (int i = 0; i < grid_size; i = i + 1) {
                if (*(grid + (grid_size * i + j)) == -1){
                    *(grid + (grid_size * i + j)) = 0;
                }
            }
        }

        count_vertical_O = 0;
        count_vertical_X = 0;

    }

    return 0;

}

// Prints board
void print_board(int grid_size, const int *grid) {

    for (int i = 0; i < grid_size; i = i + 1) {
        for (int j = 0; j < grid_size; j = j + 1) {

            if (*(grid + i * grid_size + j) == 1){
                printf("|X|");
            }
            if (*(grid + i * grid_size + j) == 0){
                printf("|O|");
            }
            if (*(grid + i * grid_size + j) == -1){
                printf("|_|");
            }

        }
        printf("\n");
    }

}
