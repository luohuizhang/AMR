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
statinfo=os.stat(filename_0)
fsize_0=statinfo.st_size/8
fin = open(filename_0, 'rb')
vals_0 = array.array('d',(int(fsize_0))*[0])
fin.readinto(vals_0)
fin.close()
v_max=max(vals_0)
v_min=min(vals_0)

lev4_map=array.array('i', (int(fsize))*[0]);
fin = open("Mapping_3_4", 'rb')
fin.readinto(lev4_map)
fin.close()

lev4_nocp = array.array('d', (int(cnt[4]))*[0])
for i in range(cnt[4]):
    lev4_nocp[i]=lev3[lev4_map[i]][2]


    
 
fp=open("CR_RMSE.txt","w")
for err in range(8,25):
    print "*******************"
    print err 
    print "*******************"
    PW_E=pow(10,(0-err)/4)*(v_max-v_min)
    sz1="sed -i \"66s/.*/absErrBound ="+str(PW_E)+"/\" /home/luo/ZFP/SZ/sz.config"
    os.system(sz1)
    fp.write(str(err)+" ") 

    szcmpresscmd = '/home/luo/Tao/LossyCompressStudy/SZ/example/testdouble_compress /home/luo/ZFP/SZ/sz.config Level_4.dat '+str(fsize)
    szdecmp = '/home/luo/Tao/LossyCompressStudy/SZ/example/testdouble_decompress /home/luo/ZFP/SZ/sz.config Level_4.dat.sz '+str(fsize)

    os.system(szcmpresscmd)

    os.system(szdecmp)

    statinfo=os.stat(filename+".sz")
    cmpr_fsize=statinfo.st_size/8

    fin = open(filename+'.sz.out', 'rb')
    vals_1 = array.array('d', (int(fsize))*[0])
    fin.readinto(vals_1)
    fin.close()
     
    
    vals_1=np.array(vals_1)
    vals=np.array(vals)
    NRMSE= np.sqrt(((vals_1 - vals) ** 2).mean())/(v_max-v_min)
    print NRMSE
    fp.write(str(NRMSE)+" ")        

    deltaname="delta_3_4"
    szcmpresscmd = '/home/luo/Tao/LossyCompressStudy/SZ/example/testdouble_compress /home/luo/ZFP/SZ/sz.config delta_3_4 '+str(fsize)
    szdecmp = '/home/luo/Tao/LossyCompressStudy/SZ/example/testdouble_decompress /home/luo/ZFP/SZ/sz.config delta_3_4.sz '+str(fsize)

    os.system(szcmpresscmd)

    os.system(szdecmp)
    statinfo=os.stat(deltaname+".sz")
    delta_cmpr_fsize=statinfo.st_size/8

    fin = open(deltaname+'.sz.out', 'rb')
    delta = array.array('d', (int(fsize))*[0])
    fin.readinto(delta)
    fin.close()

    szcmpresscmd = '/home/luo/Tao/LossyCompressStudy/SZ/example/testdouble_compress /home/luo/ZFP/SZ/sz.config Level_3.dat '+str(cnt[3])
    szdecmp = '/home/luo/Tao/LossyCompressStudy/SZ/example/testdouble_decompress /home/luo/ZFP/SZ/sz.config Level_3.dat.sz '+str(cnt[3])

    os.system(szcmpresscmd)

    os.system(szdecmp)

    fin = open('Level_3.dat.sz.out', 'rb')
    lev3_decoded = array.array('d', (int(cnt[3]))*[0])
    fin.readinto(lev3_decoded)
    fin.close()
    lev4_decoded = array.array('d', (int(cnt[4]))*[0])
    for i in range(cnt[4]):
        lev4_decoded[i]=lev3_decoded[lev4_map[i]]
    lev4_new=np.array(lev4_decoded)+np.array(delta)
    lev4_new_nocp=np.array(lev4_nocp)+np.array(delta)    
    NRMSE_final= np.sqrt(((lev4_new - vals) ** 2).mean())/(v_max-v_min)
    NRMSE_nocp= np.sqrt(((lev4_new_nocp - vals) ** 2).mean())/(v_max-v_min)
    print lev4_new-vals
    #print vals
    print NRMSE_final
    fp.write(str(fsize/cmpr_fsize)+ " ")
    fp.write(str(NRMSE_final)+" ")
    fp.write(str(fsize/(delta_cmpr_fsize))+ " ")
    fp.write(str(NRMSE_nocp)+" ")
    fp.write(str(fsize/(delta_cmpr_fsize))+ "\n")
 
fp.close()
