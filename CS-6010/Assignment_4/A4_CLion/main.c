// Stephen allegri
// ID: 903207717

#include <stdio.h>

int O_add(int i, int j, int nRows, int nCols);

int double_scan(int nRows, int nCols);

int double_fill(int nRows, int nCols);

// Global definitions of nRows, nCols, and the board matrix M
int nRows_OG = 6;
int nCols_OG = 6;
int M[6][6];

int main() {

    // Sets all matrix locations to -1 (this will be removed with file read)
    for (int i = 0; i < nRows_OG; i = i + 1) {
        for (int j = 0; j < nCols_OG; j = j + 1) {

            M[i][j] = -1;

        }
    }

    // Setting initial conditions for the board (this will be removed with file read)
    M[0][1] = 1;
    M[1][0] = 0;
    M[2][2] = 0;
    M[3][1] = 1;
    M[2][4] = 1;
    M[3][4] = 1;
    M[3][5] = 0;
    M[4][5] = 0;
    M[5][4] = 0;

    // Prints board
    for (int i = 0; i < nRows_OG; i = i + 1) {
        for (int j = 0; j < nCols_OG; j = j + 1) {

            if (M[i][j] == 1){
                printf("|X|");
            }
            if (M[i][j] == 0){
                printf("|O|");
            }
            if (M[i][j] == -1){
                printf("|_|");
            }

        }
        printf("\n");
    }

    // Runs functions each time the loop "hits" zero
    for (int i = 0; i < nRows_OG; i = i + 1) {
        for (int j = 0; j < nCols_OG; j = j + 1) {

            if (M[i][j] == 0){
                double_scan(nRows_OG, nCols_OG);
                // double_fill(nRows_OG, nCols_OG);
                O_add(i, j, nRows_OG, nCols_OG);
            }

        }
    }

    printf("\n");
    printf("\n");

    // Prints board
    for (int i = 0; i < nRows_OG; i = i + 1) {
        for (int j = 0; j < nCols_OG; j = j + 1) {

            if (M[i][j] == 1){
                printf("|X|");
            }
            if (M[i][j] == 0){
                printf("|O|");
            }
            if (M[i][j] == -1){
                printf("|_|");
            }

        }
        printf("\n");
    }

    // Runs functions each time the loop "hits" zero a second time (for accuracy)
    for (int i = 0; i < nRows_OG; i = i + 1) {
        for (int j = 0; j < nCols_OG; j = j + 1) {

            if (M[i][j] == 0){
                double_scan(nRows_OG, nCols_OG);
                // double_fill(nRows_OG, nCols_OG);
                O_add(i, j, nRows_OG, nCols_OG);

            }

        }
    }

    printf("\n");
    printf("\n");

    for (int i = 0; i < nRows_OG; i = i + 1) {
        for (int j = 0; j < nCols_OG; j = j + 1) {

            if (M[i][j] == 1){
                printf("|X|");
            }
            if (M[i][j] == 0){
                printf("|O|");
            }
            if (M[i][j] == -1){
                printf("|_|");
            }

        }
        printf("\n");
    }

    return 0;

}

int O_add(int i, int j, int nRows, int nCols){

    int inner[4] = {0, 0, 0, 0};
    int outer[4] = {0, 0, 0, 0};

    for (int k = 0; k < 4; k = k + 1) {

        if (k % 2 == 0){
            if (k < 2) {
                inner[k] = j - 1;
                outer[k] = j - 2;
            } else {
                inner[k] = j + 1;
                outer[k] = j + 2;
            }
        } else {
            if (k < 2) {
                inner[k] = i - 1;
                outer[k] = i - 2;
            } else {
                inner[k] = i + 1;
                outer[k] = i + 2;
            }
        }

    }

    for (int k = 0; k < 4; k = k + 1) {

        if (k % 2 == 0){  // Beginning of horizontal
            if (k < 2) {  // Beginning of left
                if (inner[k] >= 0){
                    if (outer[k] >= 0){
                        if (j == (nCols - 1)){
                            if (M[i][j - 2] == 0 && M[i][j - 1] == -1){
                                M[i][j - 1] = 1;
                            }
                            if ((M[i][j - 2] == 1 || M[i][j - 2] == -1) && M[i][j - 1] == -1) {
                                M[i][j - 1] = 0;
                                M[i][j - 2] = 1;
                            }
                        } else {
                            if ((M[i][j - 2] == 0 || M[i][j + 1] == 0)){
                                M[i][j - 1] = 1;
                            }
                            if ((M[i][j - 2] == 1 || M[i][j - 2] == -1) && (M[i][j + 1] == 1 || M[i][j + 1] == -1) && M[i][j - 1] == -1){
                                M[i][j - 1] = 0;
                                M[i][j - 2] = 1;
                                M[i][j + 1] = 1;
                            }
                        }
                    } else {
                        if (M[i][j - 1] == 0) {
                            M[i][j + 1] = 1;
                        }
                        if (M[i][j - 1] == -1 && (M[i][j + 1] == -1 || M[i][j + 1] == 1)) {
                            M[i][j - 1] = 0;
                            M[i][j + 1] = 1;
                        }
                    }
                }
            } else { // Beginning of right
                if (inner[k] < nCols){
                    if (outer[k] < nCols){
                        if (j == 0){
                            if (M[i][j + 2] == 0 && M[i][j + 1] == -1){
                                M[i][j + 1] = 1;
                            }
                            if ((M[i][j + 2] == 1 || M[i][j + 2] == -1) && M[i][j + 1] == -1) {
                                M[i][j + 1] = 0;
                                M[i][j + 2] = 1;
                            }
                        } else {
                            if ((M[i][j + 2] == 0 || M[i][j - 1] == 0)){
                                M[i][j + 1] = 1;
                            }
                            if ((M[i][j + 2] == 1 || M[i][j + 2] == -1) && (M[i][j - 1] == 1 || M[i][j - 1] == -1) && M[i][j + 1] == -1){
                                M[i][j + 1] = 0;
                                M[i][j + 2] = 1;
                                M[i][j - 1] = 1;
                            }
                        }
                    } else {
                        if (M[i][j + 1] == 0) {
                            M[i][j - 1] = 1;
                        }
                        if (M[i][j + 1] == -1 && (M[i][j - 1] == -1 || M[i][j - 1] == 1)) {
                            M[i][j + 1] = 0;
                            M[i][j - 1] = 1;
                        }
                    }
                }
            }
        } else {  // Beginning of vertical
            if (k < 2) {  // Beginning of top
                if (inner[k] >= 0){
                    if (outer[k] >= 0){
                        if (i == (nRows - 1)){
                            if (M[i - 2][j] == 0 && M[i - 1][j] == -1){
                                M[i - 1][j] = 1;
                            }
                            if ((M[i - 2][j] == 1 || M[i - 2][j] == -1) && M[i - 1][j] == -1) {
                                M[i - 1][j] = 0;
                                M[i - 2][j] = 1;
                            }
                        } else {
                            if ((M[i - 2][j] == 0 || M[i + 1][j] == 0)){
                                M[i - 1][j] = 1;
                            }
                            if ((M[i - 2][j] == 1 || M[i - 2][j] == -1) && (M[i + 1][j] == 1 || M[i + 1][j] == -1) && M[i - 1][j] == -1){
                                M[i - 1][j] = 0;
                                M[i - 2][j] = 1;
                                M[i + 1][j] = 1;
                            }
                        }
                    } else {
                        if (M[i - 1][j] == 0) {
                            M[i + 1][j] = 1;
                        }
                        if (M[i - 1][j] == -1 && (M[i + 1][j] == -1 || M[i + 1][j] == 1)) {
                            M[i - 1][j] = 0;
                            M[i + 1][j] = 1;
                        }
                    }
                }
            } else {  // Beginning of bottom
                if (inner[k] < nRows){
                    if (outer[k] < nRows){
                        if (i == 0){
                            if (M[i + 2][j] == 0 && M[i + 1][j] == -1){
                                M[i + 1][j] = 1;
                            }
                            if ((M[i + 2][j] == 1 || M[i + 2][j] == -1) && M[i + 1][j] == -1) {
                                M[i + 1][j] = 0;
                                M[i + 2][j] = 1;
                            }
                        } else {
                            if ((M[i + 2][j] == 0 || M[i - 1][j] == 0)){
                                M[i + 1][j] = 1;
                            }
                            if ((M[i + 2][j] == 1 || M[i + 2][j] == -1) && (M[i - 1][j] == 1 || M[i - 1][j] == -1) && M[i + 1][j] == -1){
                                M[i + 1][j] = 0;
                                M[i + 2][j] = 1;
                                M[i - 1][j] = 1;
                            }
                        }
                    } else {
                        if (M[i + 1][j] == 0) {
                            M[i - 1][j] = 1;
                        }
                        if (M[i + 1][j] == -1 && (M[i - 1][j] == -1 || M[i - 1][j] == 1)) {
                            M[i + 1][j] = 0;
                            M[i - 1][j] = 1;
                        }
                    }
                }
            }
        }

    }

    return 0;

}

int double_scan(int nRows, int nCols){

    // Horizontal Scan
    for (int i = 0; i < nRows; i = i + 1) {
        for (int j = 0; j < nCols; j = j + 1) {

            if (j == 0){
                if (M[i][j] == 0 && M[i][j + 1] == 0){
                    M[i][j + 2] = 1;
                }
                if (M[i][j] == 1 && M[i][j + 1] == 1){
                    M[i][j + 2] = 0;
                }
            }
            if (j == 1){
                if (M[i][j] == 0 && M[i][j + 1] == 0){
                    M[i][j + 2] = 1;
                    M[i][j - 1] = 1;
                }
                if (M[i][j] == 1 && M[i][j + 1] == 1){
                    M[i][j + 2] = 0;
                    M[i][j - 1] = 0;
                }
                if (M[i][j - 1] == 0 && M[i][j] == 0){
                    M[i][j + 1] = 1;
                }
                if (M[i][j - 1] == 1 && M[i][j] == 1){
                    M[i][j + 1] = 0;
                }
            }
            if (1 < j && j <= (nCols - 3)){
                if (M[i][j] == 0 && M[i][j + 1] == 0){
                    M[i][j + 2] = 1;
                    M[i][j - 1] = 1;
                }
                if (M[i][j] == 1 && M[i][j + 1] == 1){
                    M[i][j + 2] = 0;
                    M[i][j - 1] = 0;
                }
                if (M[i][j - 1] == 0 && M[i][j] == 0){
                    M[i][j + 1] = 1;
                    M[i][j - 2] = 1;
                }
                if (M[i][j - 1] == 1 && M[i][j] == 1){
                    M[i][j + 1] = 0;
                    M[i][j - 2] = 0;
                }
            }
            if (j == (nCols - 2)){
                if (M[i][j - 1] == 0 && M[i][j] == 0){
                    M[i][j - 2] = 1;
                    M[i][j + 1] = 1;
                }
                if (M[i][j - 1] == 1 && M[i][j] == 1){
                    M[i][j - 2] = 0;
                    M[i][j + 1] = 0;
                }
                if (M[i][j] == 0 && M[i][j + 1] == 0){
                    M[i][j - 1] = 1;
                }
                if (M[i][j] == 1 && M[i][j + 1] == 1){
                    M[i][j - 1] = 0;
                }
            }
            if (j == (nCols - 1)){
                if (M[i][j - 1] == 0 && M[i][j] == 0){
                    M[i][j - 2] = 1;
                }
                if (M[i][j - 1] == 1 && M[i][j] == 1){
                    M[i][j - 2] = 0;
                }
            }

        }
    }

    // Vertical Scan
    for (int j = 0; j < nCols; j = j + 1) {
        for (int i = 0; i < nRows; i = i + 1) {

            if (i == 0){
                if (M[i][j] == 0 && M[i + 1][j] == 0){
                    M[i + 2][j] = 1;
                }
                if (M[i][j] == 1 && M[i + 1][j] == 1){
                    M[i + 2][j] = 0;
                }
            }
            if (i == 1){
                if (M[i][j] == 0 && M[i + 1][j] == 0){
                    M[i + 2][j] = 1;
                    M[i - 1][j] = 1;
                }
                if (M[i][j] == 1 && M[i + 1][j] == 1){
                    M[i + 2][j] = 0;
                    M[i - 1][j] = 0;
                }
                if (M[i - 1][j] == 0 && M[i][j] == 0){
                    M[i + 1][j] = 1;
                }
                if (M[i - 1][j] == 1 && M[i][j] == 1){
                    M[i + 1][j] = 0;
                }
            }
            if (1 < i && i < (nRows - 3)){
                if (M[i][j] == 0 && M[i + 1][j] == 0){
                    M[i + 2][j] = 1;
                    M[i - 1][j] = 1;
                }
                if (M[i][j] == 1 && M[i + 1][j] == 1){
                    M[i + 2][j] = 0;
                    M[i - 1][j] = 0;
                }
                if (M[i - 1][j] == 0 && M[i][j] == 0){
                    M[i + 1][j] = 1;
                    M[i - 2][j] = 1;
                }
                if (M[i - 1][j] == 1 && M[i][j] == 1){
                    M[i + 1][j] = 0;
                    M[i - 2][j] = 0;
                }
            }
            if (i == (nRows - 2)){
                if (M[i - 1][j] == 0 && M[i][j] == 0){
                    M[i - 2][j] = 1;
                    M[i + 1][j] = 1;
                }
                if (M[i - 1][j] == 1 && M[i][j] == 1){
                    M[i - 2][j] = 0;
                    M[i + 1][j] = 0;
                }
                if (M[i][j] == 0 && M[i + 1][j] == 0){
                    M[i - 1][j] = 1;
                }
                if (M[i][j] == 1 && M[i + 1][j] == 1){
                    M[i - 1][j] = 0;
                }
            }
            if (i == (nRows - 1)){
                if (M[i - 1][j] == 0 && M[i][j] == 0){
                    M[i - 2][j] = 1;
                }
                if (M[i - 1][j] == 1 && M[i][j] == 1){
                    M[i - 2][j] = 0;
                }
            }

        }
    }

    return 0;

}

int double_fill(int nRows, int nCols){

    int count_horizontal_O = 0;
    int count_horizontal_X = 0;
    int count_vertical_O = 0;
    int count_vertical_X = 0;

    // Horizontal fill
    for (int i = 0; i < nRows; i = i + 1) {
        for (int j = 0; j < nCols; j = j + 1) {

            if (M[i][j] == 0){
                count_horizontal_O = count_horizontal_O + 1;
            }

            if (M[i][j] == 1){
                count_horizontal_X = count_horizontal_X + 1;
            }

        }

        if (count_horizontal_O == (nCols/2)){
            for (int j = 0; j < nCols; j = j + 1) {
                if (M[i][j] == -1){
                    M[i][j] = 1;
                }
            }
        }

        if (count_horizontal_X == (nCols/2)){
            for (int j = 0; j < nCols; j = j + 1) {
                if (M[i][j] == -1){
                    M[i][j] = 0;
                }
            }
        }

        count_horizontal_O = 0;
        count_horizontal_X = 0;

    }

    // Vertical fill
    for (int j = 0; j < nCols; j = j + 1) {
        for (int i = 0; i < nRows; i = i + 1) {

            if (M[i][j] == 0){
                count_vertical_O = count_vertical_O + 1;
            }

            if (M[i][j] == 1){
                count_vertical_X = count_vertical_X + 1;
            }

        }

        if (count_vertical_O == (nRows/2)){
            for (int i = 0; i < nRows; i = i + 1) {
                if (M[i][j] == -1){
                    M[i][j] = 1;
                }
            }
        }

        if (count_vertical_X == (nRows/2)){
            for (int i = 0; i < nRows; i = i + 1) {
                if (M[i][j] == -1){
                    M[i][j] = 0;
                }
            }
        }

        count_vertical_O = 0;
        count_vertical_X = 0;

    }

    return 0;

}
