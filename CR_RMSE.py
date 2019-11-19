from __future__ import division
import sys
import array
import scipy.stats as stats
import os


import numpy as np
import matplotlib.pyplot as plt

import struct

cnt=[]
lev3=[]
lev4=[]
with open('datapoint.dat', 'rb') as f:
    for i in range(5):
        chunk = f.read(4)
        num= struct.unpack('i', chunk)[0] 
        cnt.append(num)
        for j in range(num):
            chunk = f.read(16)
            if i==3:
               lev3.append( struct.unpack('iid', chunk))
            if i==4:
               lev4.append( struct.unpack('iid', chunk))
#for i in range(cnt[3]):

print len(lev3)
print len(lev4)

#list1=["new_delta_0_1","new_delta_1_2","new_delta_2_3","new_delta_3_4"]

#list1=["delta_0_1","delta_1_2","delta_2_3","delta_3_4"]

#list1=["delta_0_1","delta_1_2","delta_2_3","delta_3_4","delta_0_1_2","delta_1_2_3","delta_2_3_4","delta_0_1_2_3","delta_1_2_3_4"]

filename="Level_4.dat"
        
#low_base_fsize=statinfo.st_size
statinfo=os.stat(filename)
fsize=statinfo.st_size/8
fin = open(filename, 'rb')
vals = array.array('d',(int(fsize))*[0])

fin.readinto(vals)
fin.close()

filename_0="Level_0.dat"

#low_base_fsize=statinfo.st_size
statinfo=os.stat(filename_0)
fsize_0=statinfo.st_size/8
fin = open(filename_0, 'rb')
vals_0 = array.array('d',(int(fsize_0))*[0])

fin.readinto(vals_0)
fin.close()

v_max=max(vals_0)
v_min=min(vals_0)

lev4_1=array.array('d', (int(fsize))*[0]);
for i in range(cnt[4]):
    #print lev4[i][0]//2, lev4[i][1]//2
    for j in range(cnt[3]):
        if lev4[i][0]//2==lev3[j][0] and lev4[i][1]//2==lev3[j][1]:
                #print lev4[i], lev3[j]
	    break
    #print j
    if j>=cnt[3]:
	print "error"
	exit();
    lev4_1[i]=lev3[j][2];    
 
fp=open("CR_RMSE.txt","w")
for err in range(8,25):
    print "*******************"
    print err 
    print "*******************"
    PW_E=pow(10,(0-err)/4)*(v_max-v_min)
    fp.write(str(err)+" ") 
    zfpcmpresscmd = '/home/luo/ZFP/zfp/bin/zfp -a '+str(PW_E)+' -s -d -1 '+str(fsize)+' -i '+str(filename)+' -z '+str(filename+".zfp")
    zfpdecmp = '/home/luo/ZFP/zfp/bin/zfp -a  '+str(PW_E)+' -d -1 '+str(fsize)+ ' -z '+str(filename+".zfp")+' -o '+str(filename+".zfp.out")
    print zfpdecmp
    os.system(zfpcmpresscmd)

    os.system(zfpdecmp)

    statinfo=os.stat(filename+".zfp")
    cmpr_fsize=statinfo.st_size/8

    fin = open(filename+'.zfp.out', 'rb')
    vals_1 = array.array('d', (int(fsize))*[0])
    fin.readinto(vals_1)
    fin.close()
     
    
    vals_1=np.array(vals_1)
    vals=np.array(vals)
    NRMSE= np.sqrt(((vals_1 - vals) ** 2).mean())/(v_max-v_min)
    print NRMSE
    fp.write(str(NRMSE)+" ")        

    deltaname="delta_3_4"
    zfpcmpresscmd = '/home/luo/ZFP/zfp/bin/zfp -a '+str(PW_E)+' -s -d -1 '+str(fsize)+' -i '+str(deltaname)+' -z '+str(deltaname+".zfp")
    zfpdecmp = '/home/luo/ZFP/zfp/bin/zfp -a  '+str(PW_E)+' -d -1 '+str(fsize)+ ' -z '+str(deltaname+".zfp")+' -o '+str(deltaname+".zfp.out")
    print zfpdecmp
    os.system(zfpcmpresscmd)

    os.system(zfpdecmp)
    
    statinfo=os.stat(deltaname+".zfp")
    delta_cmpr_fsize=statinfo.st_size/8

    fin = open(deltaname+'.zfp.out', 'rb')
    delta = array.array('d', (int(fsize))*[0])
    fin.readinto(delta)
    fin.close()

    lev4_new=np.array(lev4_1)+np.array(delta)

    NRMSE_final= np.sqrt(((lev4_new - vals) ** 2).mean())/(v_max-v_min)

    print NRMSE_final
    fp.write(str(fsize/cmpr_fsize)+ " ")
    fp.write(str(NRMSE_final)+" ")
    fp.write(str(fsize/(delta_cmpr_fsize))+ "\n")
 
fp.close()
