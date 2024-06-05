

import pandas as pd
import numpy as np

begin=0
end=0
loop=0
breaking=0


result=[]
df = pd.read_csv('L=50000_avl_shape_uniform_final.txt', sep=" ")
df['avl_norm']=df['break']/df['count']
df_load=pd.read_csv('L=50000_avltime_load_uniform_final.txt', sep=' ')

df_load['load_norm']=df_load['load']/df_load['load_count']

with open('L=50000_time_asymmetry_load_uniform.txt', 'w') as f:
       
    for index, row in df.iterrows():
        if(row['break']==0):
            end=index
            selected_rows= df.iloc[begin:end+1,3].values
            selected_rows=np.append(0,selected_rows)
            selected_rows=selected_rows/np.max(selected_rows)
            tau=int((len(selected_rows))-1)
            Asym=0
            for i in range(len(selected_rows)):
                print(i,tau)
                #print(tau)
                Asym+=abs(selected_rows[i]-np.minimum(selected_rows[i],selected_rows[tau-i]))
            load_norm_value = df_load.loc[loop, 'load_norm']

            # Write data to the file with additional column
            f.write(str(tau) + " " + str(Asym / tau) + " " + str(load_norm_value) + "\n")
            print("asym:", Asym / tau, "time: ", tau, "load_norm:", load_norm_value)
            print("asym:",Asym/tau,"time: ",tau)
            begin=end+1

            loop+=1
    


 
        

