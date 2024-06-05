#include <stdio.h>
#include <stdlib.h>
#include "ran2.c" // Random number generator

long sd = -937176386; // Seed for random number generator
#define L 50000 // Number of elements
#define Range 1000 // Range for redistribution

int main() {
    // Variable declarations
    int i = 0, j = 0, k = 0, m = 0, n = 0, broken = 0, min_pos = 0, check[L] = {0}, R_Nr = 0, L_Nr = 0, r = 0, l = 0;
    int block_avl_broken = 0, former_block_avl_broken = 0, avl_broken = 0, gr_broken = 0, intact = 0;
    int avl_series[1000] = {0}, avl_series_count[1000] = {0};
    double thres[L] = {0}, load[L] = {0}, load_2[L] = {0},min = 0;
    int avl_count = 0,avl_time = 0,time = 0;
    int data[3][100];
    int iterations=100;// Number of iterations for averaging

    // Initialize data array
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 101; j++) {
            data[i][j] = 0;
        }
    }

    // Main iteration loop
    for (k = 0; k < iterations; k++) {
        printf("%d iteration\n", k);

        // Reset variables for each iteration
        for (i = 0; i < L; i++) {
            thres[i] = 0;
            load[L] = 0;
            load_2[L] = 0;
            check[L] = 0;
        }
        for (i = 0; i < 1000; i++) {
            avl_series[i] = 0;
        }
        broken = 0;
        min_pos = 0;
        R_Nr = 0;
        L_Nr = 0;
        r = 0;
        l = 0;
        avl_broken = 0;
        gr_broken = 0;
        intact = 0;
        min = 0;
        avl_count = 0;

        // Initialize threshold values
        for (i = 0; i < L; i++) {
            thres[i] = ran2(&sd);
        }
        // Find minimum threshold
        min = 2;
        for (i = 0; i < L; i++) {
            if ((min > thres[i]) && (thres[i] > 0)) {
                min = thres[i];
                min_pos = i;
            }
        }

        // Initialize load array with minimum threshold
        for (i = 0; i < L; i++) {
            load[i] = min;
        }
        intact = L;
        time = 0;
        // Avalanche initiation loop
        while (2) {
            avl_broken = 0;
            avl_time = 0;
            avl_count++;
            // Redistribution loop
            while (2) {
                // Mark all elements as unchecked
                for (i = 0; i < L; i++) {
                    check[i] = 1;
                }
                broken = 0;
                intact = 0;
                // Check which elements have broken
                for (i = 0; i < L; i++) {
                    if ((thres[i] <= load[i]) && thres[i] > 0) {
                        thres[i] = 0;
                        load_2[i] = load[i];
                        load[i] = 0;
                        check[i] = 0;
                        broken++;
                    } else {
                        intact++;
                    }
                }
                avl_broken += broken;
                gr_broken += broken;
                avl_time++;
                time++;

                // Break if no elements have broken or if all elements have broken
                if (broken == 0 || gr_broken >= L) {
                    break;
                }

                // Redistribution to right neighbors
                for (i = 0; i < L; i++) {
                    if (load[i] == 0 && check[i] == 0) {
                        r = (i);
                        for (int R = 0; R < Range; R++) {
                            for (; load[r] == 0; r++) {
                                if (r == (L - 1))
                                    r = -1;
                            }
                            load[r] += load_2[i] / (2 * Range);
                            if (r == (L - 1)) {
                                r = -1;
                            }
                            r++;
                        }
                    }
                }

                // Redistribution to left neighbors
                for (i = 0; i < L; i++) {
                    if (load[i] == 0 && check[i] == 0) {
                        l = (i);
                        for (int R = 0; R < Range; R++) {
                            for (; load[l] == 0; l--) {
                                if (l == 0)
                                    l = L;
                            }
                            load[l] += load_2[i] / (2 * Range);
                            if (l == 0) {
                                l = L;
                            }
                            l--;
                        }
                    }
                }

                // Update avalanche series
                avl_series_count[avl_time]++;
                avl_series[time] = broken;
                for (i = 0; i < L; i++) {
                    check[i] = 1;
                    load_2[i] = 0;
                }
            } // Redistribution loop ends

            // Break if all elements have broken
            if (gr_broken >= L)
                break;
            // Increment load on remaining elements
            for (i = 0; i < L; i++) {
                if (thres[i] > 0) {
                    load[i] += 0.01; // Increment load
                }
            }
        }

        // Determine start time and end time of avalanche series of the last 3 avalanches and store the corresponding sub avalanche size
        int begin = 0, finish = 0, count = 0;
        for (i = time - 1; i > 0; i--) {
            if (avl_series[i] == 0) {
                count++;
                if (count == 4) {
                    begin = i;
                    break;
                }
                if (count == 1) {
                    finish = i;
                }
            }
        }
        count = 0;
        int moving_begin = 0;
        for (i = begin; i <= finish; i++) {
            if (avl_series[i] == 0) {
                count++;
                moving_begin = i;
            }
            data[count - 1][i - moving_begin] += avl_series[i];
        }
    } // End of iterations

    // Write results to file
    FILE *fp = fopen("R=1000avg_100_last3.txt", "w");
    int scaled_time = 0;
    for (i = 0; i < 4; i++) {
        for (j = 1; j < 100; j++) {
            if (data[i][j] == 0)
                break;
            scaled_time++;
            fprintf(fp, "%d %lf\n", scaled_time, (double)data[i][j] / iterations);
        }
    }
    fclose(fp);

    return 0;
}
