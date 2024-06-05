import pandas as pd

# List of file names
file_list = ["L=50000_avl_shape_uniform_10000_" + str(i * 1) + ".txt" for i in range(1, 11)]

# Initialize the result dataframe
result_df = pd.DataFrame()
# Loop through each file
for file in file_list:
    # Read data from the file
    df = pd.read_csv(file, sep=' ', header=None, names=['s_no','count', 'break'])
    
    # Add data to the result dataframe
    result_df = result_df.add(df, fill_value=0)
    
result_df['s_no'] = result_df['s_no']/10


result_df.to_csv('L=50000_avl_shape_uniform.txt', sep=' ', index=False)
# Remove rows with zero values in the "count" column
result_df = result_df[result_df['count'] != 0]

# Replace the "s_no" column with the remainder of 100
result_df['s_no'] = result_df['s_no'].apply(lambda x: x % 100)

result_df.to_csv('L=50000_avl_shape_uniform_final.txt', sep=' ', index=False)
