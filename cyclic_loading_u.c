#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
    /* Block of code to determine the terminal time of each avalanche
       from the simulation data of U for limiting the values for the integral equation */
    double t_ser = 0, t_avl = 0, U_sim = 0, t_prev = 0, loop = 0;
    double time[500] = {0}, surv_frac_sim[500] = {0};
    FILE *fp2 = fopen("L=100000_time_simulation_U_0.01.txt", "r");

    // Read simulation data from file
    while (1)
    {
        fscanf(fp2, "%lf %lf %lf\n", &t_ser, &t_avl, &U_sim);
        // Check for terminal time and store it in the time array
        if (t_avl < t_prev) {
            time[(int)loop] = t_prev;
            loop++;
        }
        t_prev = t_avl; // Update previous avalanche time
        if (feof(fp2)) break; // Break loop if end of file is reached
    }
    fclose(fp2); // Close the input file

    /* Block of code to calculate U from the integral equation
       and limit it in time with reference to simulation data */
    double a = 0, b = 0, c = 1, U = 1, t = 0, time_U_prev = 0;
    double U_step[50000] = {0};
    FILE *fp = fopen("time_U_0.01_new.txt", "w"); // Output file declaration
    double sigma_L = 0, sigma_R = 1, sigma = 0.01, load = 0;

    U = 1; // Initial surviving fraction

    // Main loop for cyclic loading, iterating 1000 times
    for (int i = 0; i < 1000; i++)
    {
        c = 1; // Reset c for the new iteration

        // Compute load increment based on previous U_step values
        for (int n = 0; n < i; n++)
        {
            c *= U_step[n];
        }
        load += (c * 0.01); // Accumulate load

        // Update sigma values for subsequent calculations
        if (i > 0)
        {
            sigma_L = (sigma / U); // Update left sigma
            sigma = (sigma / U) + 0.01; // Update sigma with increment delta
            t = 0; a = 0; b = 0; // Reset time and auxiliary variables
        }

        // Break condition for sigma to exit the loop if it exceeds a certain value
        if ((sigma) > sigma_R * sigma_R / (4 * (sigma_R - sigma_L))) {
            break;
        }

        // Inner loop to compute the surviving fraction U
        for (U = 1; U > 0.1; U -= 0.00001)
        {
            // Calculate terms for the integral equation
            double A = sigma_R - sigma_L;
            double B = sigma_R / (sigma_R - sigma_L);
            double C = sigma / (sigma_R - sigma_L);
            double D = log(fabs((U * U) * A - (sigma_R * U) + sigma));
            double E = ((B / (2 * sqrt((B * B / 4) - C))) * log(fabs((2 * U - B - 2 * sqrt((B * B / 4) - C))))) - ((B / (2 * sqrt((B * B / 4) - C))) * log(fabs((2 * U - B + 2 * sqrt((B * B / 4) - C)))));
            double F = log(fabs(A - sigma_R + sigma));
            double G = ((B / (2 * sqrt((B * B / 4) - C))) * log(fabs((2 - B - 2 * sqrt((B * B / 4) - C))))) - ((B / (2 * sqrt((B * B / 4) - C))) * log(fabs((2 - B + 2 * sqrt((B * B / 4) - C)))));
            t = -0.5 * (D + E - F - G); // Calculate time t using the integral equation terms

            a = t; // Update a with the current time

            // Check if the current time a is greater than the previous maximum time b
            if (b < a)
            {
                if (time[i] > t)
                {
                    // Write the computed time and surviving fraction to the output file
                    fprintf(fp, "%0.15lf %0.15lf %0.15lf\n", t, t + time_U_prev, U * c);
                }
            }
            else
            {
                if (b != 0) {
                    break;
                }
            }
            b = a; // Update previous maximum time

            // Reset variables for the next iteration
            t = 0;
            A = 0;
            B = 0;
            C = 0;
            D = 0;
            E = 0;
            F = 0;
            G = 0;
        }
        c = U; // Update c with the current U
        U_step[i] = U; // Store the current U in U_step array
        time_U_prev += b; // Accumulate the total time
    }

    fclose(fp); // Close the output file
    return 0;
}
