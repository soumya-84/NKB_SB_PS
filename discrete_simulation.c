#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ran2.c"

#define SYSTEM_SIZE 100000

long sd = 9862384731;

int main() {
    double thres[SYSTEM_SIZE] = {0}, load = 0, load_bundle = 0;
    double min = 0, load_redistribution_increment = 0;
    int broken = 0, intact = 0, min_pos = 0, avl_broken = 0, event = 0, gr_broken = 0;
    int time_avl = 0;
    min = thres[0];
    int i = 0, j = 0;
    int iterations = 1, count = 0, time_series = 0;

    // Open output files for writing simulation data
    FILE *fp = fopen("L=100000_time_simulation_U_0.01.txt", "w");
    FILE *fp2 = fopen("L=100000_time_simulation_S_0.01.txt", "w");

    for (j = 0; j < iterations; j++) { // Loop for averaging starts
        load = 0;
        load_bundle = 0;
        min = 0;
        load_redistribution_increment = 0;
        broken = 0;
        intact = 0;
        min_pos = 0;
        avl_broken = 0;
        event = 0;
        gr_broken = 0;

        // Generate random threshold values for the fibers
        for (i = 0; i < SYSTEM_SIZE; i++) {
            thres[i] = ran2(&sd);
        }

        load = 0.01; // Initial load

        intact = SYSTEM_SIZE;

        while (1) { // Event count loop
            event++;
            time_avl = 0;
            avl_broken = 0;
            load_bundle = load * intact;

            while (broken < SYSTEM_SIZE) { // Redistribution loop
                broken = 0;
                intact = 0;

                // Individual fibers failure condition
                for (i = 0; i < SYSTEM_SIZE; i++) {
                    if (thres[i] > 0) {
                        if (thres[i] <= load) {
                            broken++;
                            thres[i] = 0;
                        } else {
                            intact++;
                        }
                    }
                }

                time_avl++;
                time_series++;
                gr_broken += broken;
                avl_broken += broken;

                // Write simulation data to output files for surviving fraction and sub_avalanche size
                fprintf(fp, "%d %d %lf\n", time_series, time_avl, (double)(SYSTEM_SIZE - gr_broken) / SYSTEM_SIZE);
                fprintf(fp2, "%d %d %lf\n", time_series, time_avl, (double)broken);

                if (broken == 0 || intact == 0) {
                    break;
                }

                // Load redistribution
                load_redistribution_increment = (load * (double)broken) / (double)intact;
                load += load_redistribution_increment;
            }

            if (intact == 0) {
                break;
            }

            load += 0.01; // Discrete loading
        } // End of event count loop
    } // End of averaging loop

    // Close output files
    fclose(fp);
    fclose(fp2);

    return 0;
}
