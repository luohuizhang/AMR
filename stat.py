from __future__ import division
import sys
import array
import scipy.stats as stats
import os
from statsmodels import robust
#from scipy import stats
import numpy as np
import matplotlib.pyplot as plt



#list1=["new_delta_0_1","new_delta_1_2","new_delta_2_3","new_delta_3_4"]

#list1=["delta_0_1","delta_1_2","delta_2_3","delta_3_4"]

#list1=["delta_0_1","delta_1_2","delta_2_3","delta_3_4","delta_0_1_2","delta_1_2_3","delta_2_3_4","delta_0_1_2_3","delta_1_2_3_4"]
list1=["new_delta_0_1","new_delta_1_2","new_delta_2_3","new_delta_3_4","new_delta_0_1_2","new_delta_1_2_3","new_delta_2_3_4","new_delta_0_1_2_3","new_delta_1_2_3_4"]
fp=open("stat.txt","w")
for filename in list1:
        print "*******************"
        print filename
        print "*******************"
       	fin = open(filename, 'rb')
        statinfo=os.stat(filename)
        fsize=statinfo.st_size
        print fsize/8
        vals_1 = array.array('d', (int(fsize/8))*[0])
	fin.readinto(vals_1)
	fin.close()
         
        print np.shape(vals_1)
        
        Average= robust.mad(vals_1)
        print Average 
        fp.write(str(Average)+" ")        
        standard=np.std(vals_1)
        print standard
        fp.write(str(standard)+"\n")


fp.close()
