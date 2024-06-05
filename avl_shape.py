import pandas as pd

# Read the data from the file "L=50000_avl_shape_uniform_final.txt" using space as a delimiter
df = pd.read_csv("L=50000_avl_shape_uniform_final.txt", sep=" ")

import numpy as np

# Initialize variables to track the beginning and end of segments in the dataframe
begin = 0 
end = 0

# Iterate over each row in the dataframe
for index, row in df.iterrows():
    end = index  # Update the end variable to the current index
    
    # Check if the 'break' column in the current row is 0
    if row["break"] == 0:  
        # Select the rows from 'begin' to 'end' inclusive, and get their values from the third column (index 2)
        selected_rows = df.iloc[begin:end+1, 2].values
        
        # Append 0 at the beginning of the selected rows
        selected_rows = np.append(0, selected_rows)
        
        # Normalize the selected rows by their maximum value
        selected_rows = selected_rows / np.max(selected_rows)
        
        max_index = len(selected_rows) - 1  # Determine the maximum index of the selected rows(duration of the avalanche)

        # Open a file to write the normalized index and value pairs
        with open(str(max_index) + "_L=50000_time_shape_uniform" + ".txt", 'w') as f:
            # Iterate over the array and write normalized index divided by max index and value to the file
            for index, value in enumerate(selected_rows):
                normalized_index = index / max_index  # scaled time of the avalanche shape
                f.write(f'{normalized_index} {value}\n')  # Write the normalized index and value to the file

        # Update 'begin' to the index after 'end' for the next segment
        begin = end + 1
