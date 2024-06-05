Measurement of the avalanche shape and calculation of the asymmetry measure for the corresponding measurement of the load(quasi static loading):
Code File: els_dynamics_load_avl_shape.c

Input: Please alter the system size , choice of the threshold distribution of the system, number of iterations 
Output: It will have two output data files
First file:(calculation of the avalanche shape)
One output file name say,L=50000_avl_shape_uniform_10000_10.txt
This file has three columns namingly sub avalanche time, number of times each sub avalanche size was recorded for specific sub avalanche time, cumulative sub avalanche size for the specific sub avalanche time.
In our case we have created 10 number of files separately for each configuration of the system with different seed number  and merged the all the files  into single file namningly L=50000_avl_shape_uniform_10000_final.txt  which has three columns namingly sub avalanche time(sno),number of times each sub avlacnche recorded for specific sub avalanche time(count),cumulative sub avalanche size for he specific sub avalanche time(break) using the code avl_shape_merge.py into a single file.
Now file L=50000_avl_shape_uniform_10000_final.txt  is processed using the code avl_shape.py to calculate he avalanche shapes for specific duration of time. Final output file will have the date for scaled avalanche shape for the specific duration of the avalanche. 
*By altering few changes here we can get unscaled avalanche shape also.

*In the code els_dynamics_load_avl_shape.c, instead of the recording sub avalanche size, we can record the avalanche size for the specific duration of the avalanche and its probability distribution with suitable modifications in the code.
Second file:(calculation of the load per Intact fiber at initiation of the avalanche and corresponding asymmetry measure)
	Second output file name say, L=50000_avltime_load_uniform_10000_10.txt
This file has three columns namingly duration of the avalanche(sno), cumulative load per intact fiber to initiate the failure process in a avalanche(load), number of times load recorded for specific duration of the avalanche.
In our case we have created number of files sepearately for each configuration of the system with different seed number and merged the all files into single file namingly L=50000_avltime_load_uniform_final.txt which has data columns like previous each individual file using the code load_duration_merge.py.
Now file L=50000_avltime_load_uniform_final.txt is further processed using the execution of the code duration_load_asymmetry.py.  This finally gives load applied to initiate the specific duration of the avalanche and corresponding Asymmetry measure of the avalanche shape for that specific duration of the avalanche shape. The final output file has three columns duration of the avalanche ,asymmetry measure of the avalanche, load per intact fiber to initiate the avalanche.

Calculating the simulation data for surviving fraction of fiber (U) as well as sub_avlanche_size(discrete loading) :
Code:discrete_simulation.c
Input: One alter the threshold distributions , system size
Please execute the file discrete simulation.c . 
Output: the output will  have two files with 
one having data for simulation data for surviving fraction of fiber(U) and corresponding time with three columns cumulative sub_avalanche_time, sub_avalanche time for specific avalanche, surviving fraction of fiber with file name L=100000_time_simulation_U_0.01.txt(here).
Second file having data for the sub avalanche size and corresponding time with three columns cumulative sub_avalanche_time, sub_avalanche time for specific avalanche, sub_avalanche_size with file name L=100000_time_simulation_S_0.01.txt(here). 
Calculating numerically solving  the integral equation for limiting time of the surviving fraction of fiber(U)(discrete loading):
This part has to be done after execution of discrete simulation.c only.
Code:cyclic_loading_u.c
After execution of the code, one gets the time_U_0.01_new.txt which will have sub_avalanche time, cumulative sub avalanche time and surviving fraction fiber which is further processed using the code theoretical_align_U_simulation.c  for limited values of time and surviving fraction of fibers and final output file “time_U_0.01_trunc.txt” is generated.

*Few changes in cyclic loading.c , we can generate for the single loading condition to calculate the surviving fraction of fiber.
*for numerically calculating sub avalanche size and its time , We can use the data of time_U_0.01_trunc.txt for differentiation of U which gives us sub avalanche size by choosing the difference of time approximately equals to 1.


Calculation of the last 3 avalanche shapes by variation of interaction range R(discrete loading):
code:lls_range_variation.c
input:Please choose the threshold distribution of the system, system, size, initial loading conditions,iterations of the sample.
After execution of the lls_range_variation.c, the output file has the time series data of the last 3 avlanches in the failure process and its corresponding sub avalanche sizes.
