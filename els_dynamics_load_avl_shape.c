#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ran2.c" // Include the random number generator function

#define SYSTEM_SIZE 50000 // Define the system size

long sd = 9862384760;

int main() {
    // Declare and initialize variables
    double thres[SYSTEM_SIZE] = {0}, load = 0, load_bundle = 0;
    double min = 0, load_redistribution_increment = 0;
    double load_sub_record_time[101] = {0}, load_count_sub_record_time[101] = {0};
    int interim_time_avl_record[101] = {0}, interim_time_avl_count[101] = {0};
    int time_sub_avl_record[10000] = {0}, time_sub_avl_count[10000] = {0};
    int broken = 0, intact = 0, min_pos = 0, block_intact = 0;
    int avl_broken = 0, event = 0, w_max_event = 0, limit_event_block = 0;
    int max = 0, gr_broken = 0, initial_intact = 0;
    int time_avl = 0, cp_loop = 0, i = 0, j = 0, p = 0, count = 0;
    int iterations = 1; // Number of iterations for averaging

    // Open output files
    FILE *fp = fopen("L=50000_avl_shape_uniform_10000_10.txt", "w");
    FILE *fp2 = fopen("L=50000_avltime_load_uniform_10000_10.txt", "w");

    for (j = 0; j < iterations; j++) { // Averaging starts
        // Reset variables for each iteration
        load = 0;
        load_bundle = 0;
        min = 0;
        load_redistribution_increment = 0;
        broken = 0;
        intact = 0;
        block_intact = 0;
        min_pos = 0;
        avl_broken = 0;
        event = 0;
        gr_broken = 0;
        cp_loop = 0;

        // Assign uniform threshold distribution values for the load
        for (i = 0; i < SYSTEM_SIZE; i++) {
            thres[i] = ran2(&sd);/*uniform threshold distribution*/
             //thres[i] = (ran2(&sd)+ran2(&sd))/2;//triangular distribution
             //thres[i] = (ran2(&sd)+ran2(&sd)+ran2(&sd))/3;//gaussian threshold distribution

        }

        // Find the minimum threshold of load value in the array
        min = thres[0];
        for (i = 0; i < SYSTEM_SIZE; i++) {
            if (thres[i] < min) {
                min = thres[i];
                min_pos = i;
            }
        }

        load = min;
        intact = SYSTEM_SIZE;

        // Begin each iteration of the sample for failure dynamics
        while (1) {
            event++;
            time_avl = 0;
            avl_broken = 0;
            load = min;
            initial_intact = intact;
            load_bundle = load * intact;

            // Redistribution loop
            while (broken < SYSTEM_SIZE) {
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
                if (time_avl < 100) {
                    interim_time_avl_record[time_avl] = broken;
                    interim_time_avl_count[time_avl] = 1;
                }
                gr_broken += broken;
                avl_broken += broken;

                // Stop redistribution if no new fibers fail or all fibers fail
                if (broken == 0 || intact == 0) {
                    if (time_avl < 100 && intact != 0) {
                        // Record sub-avalanche time and size for each duration up to 100
                        for (cp_loop = 1; cp_loop <= time_avl; cp_loop++) {
                            time_sub_avl_record[cp_loop + (time_avl * 100) - 1] += interim_time_avl_record[cp_loop];
                            time_sub_avl_count[cp_loop + (time_avl * 100) - 1] += interim_time_avl_count[cp_loop];
                        }
                        // Record the duration of the avalanche and its corresponding load to initiate it
                        load_sub_record_time[time_avl] += (min * initial_intact / SYSTEM_SIZE);
                        load_count_sub_record_time[time_avl]++;
                    }
                    break;
                }

                // Redistribution of the load after failure of the fibers to remaining intact fibers
                load_redistribution_increment = (load * (double)broken) / (double)intact;
                load += load_redistribution_increment;
            } // End of redistribution loop

            if (intact == 0) break; // If all fibers fail, stop loading

            // Quasi-static loading on the sample
            min = 2;
            for (i = 0; i < SYSTEM_SIZE; i++) {
                if ((thres[i] < min) && thres[i] != 0) {
                    min = thres[i];
                    min_pos = i;
                }
            }
            load = min;
        } // End of each iteration

    } // Averaging ends

    // Write the recorded data for avalanche shape and load to initiate specific durations of avalanches
    for (p = 0; p <= 10000; p++) {
        fprintf(fp, "%d %d %d\n", p, time_sub_avl_count[p], time_sub_avl_record[p]);
    }
    for (p = 0; p <= 100; p++) {
        fprintf(fp2, "%d %lf %lf\n", p, load_sub_record_time[p], load_count_sub_record_time[p]);
    }

    // Close output files
    fclose(fp);
    fclose(fp2);

    return 0;
}
