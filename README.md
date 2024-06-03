*To calculate the avalanche shape.
Execute the code elsdynamics.c file .
Output will be a .txt file with 3 data columns: load per intact fiber, sub avalanche
time step number, broken number of fibers in that avalanche step.
Now use the python code in avalanche_shape.ipynb for calculating the
avalanche shape of the specific duration of the avalanche for processing the files of
elsdynamics.c.

*To calculate the asymmetry measure at each loading step.
For the simulation data from the code elsdynamics.c i.e., load per intact fiber,
sub avalanche time step number, broken number of fibers in that avalanche step,
process this data with the python code load_asymmetry.ipynb . The output will be the
average value of the load to their corresponding asymmetry at each loading step.
Output file will have 4 columns: duration of the avalanche, asymmetry measure,
load and count of the data points to be divided for the average.

*Numerical solutions to equations for the surviving fraction of fiber in single loading
(theoretical).
Use the code single_loading_U.c .Output file will have two columns of data time
and U(surviving fraction of fibers)

*Numerical solutions to equations for the surviving fraction of fiber in where discrete
loading is continued until system collapsed(theoretical).
Use the code cyclic_loading_u.c. The output file will have three columns of data
time for sub avalanche, cumulative time of the sub avalanches over all avalnches and
U(surviving fraction of fibers)
Now use the code “ theoretical_align_U_simulation.c” for aligning the time of the
therotical estimate with the simulation time

*To find the calculate the sub avalanche size in discrete loading from theoretical
estimate of Surviving fraction of fibers (U)
Please use the code time_s.c
