import matplotlib.pyplot as plt
import numpy as np

import sys
import array
import os
import re 

name_hat = "/home/luo/Dropbox/SC2019_Huizhang/HPDC/IPDPS21/figures/"

namelist=[ "1", "2", "4","8","16","32","64","128","256","512","1K","2K","4K","8K","16K","32K","64K"]
data = np.loadtxt("zorder0.txt")
data=data.reshape(-1,4)
data_H = np.loadtxt("hilbert0.txt")
data_H=data_H.reshape(-1,4)
N=len(data[:,0])
x =range(0,N)
ZFP=np.zeros((N,4),dtype=float)
for i in range(0,N):
    for j in range(0,2):
        ZFP[i][j]=data[i][2*j] 
        ZFP[i][j+2]=data_H[i][2*j] 
print  ZFP 
SZ=np.zeros((N,4),dtype=float)
for i in range(0,N):
    for j in range(0,2):
        SZ[i][j]=data[i][2*j+1] 
        SZ[i][j+2]=data_H[i][2*j+1] 
print  SZ 

ind = np.arange(N)  # the x locations for the groups
width = 0.2       # the width of the bars

axis_font = {'size':'28'}
plt.rc('xtick', labelsize=28)          # fontsize of the tick labels
plt.rc('ytick', labelsize=28)
font = {'size':'28'}

fig = plt.figure(num=None,figsize=(20,4))
ax = fig.add_subplot(111)


rects1 = ax.bar(ind-width, ZFP[:,0], width, color='g',hatch='.',label="Z-order")
rects2 = ax.bar(ind, ZFP[:,1], width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, ZFP[:,2], width, color='b',hatch='x',label="Hilbert")
rects4 = ax.bar(ind+2*width, ZFP[:,3], width, color='y',hatch='/',label="Hilbert+zMesh")

ax.set_ylabel('Compression ratio',axis_font)
#ax.set_yscale('log')
y_major_locator=plt.MultipleLocator(1)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
ax.set_ylim([8,11])
ax.set_xlim([-0.3,N-0.3])
#ax.legend(ncol=3, prop=font,bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0)
ax.legend(ncol=2, prop=font)
#ax.set_title("P1 ZFP compression",axis_font)

ax.set_xlabel('Number of parallel processors',axis_font)
plt.savefig(name_hat+'ZFP_parallel.pdf', format='pdf',bbox_inches="tight")
#plt.show()


fig = plt.figure(num=None,figsize=(20,4))
ax = fig.add_subplot(111)


rects1 = ax.bar(ind-width, SZ[:,0], width, color='g',hatch='.',label="Z-order")
rects2 = ax.bar(ind, SZ[:,1], width, color='r',hatch='+',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, SZ[:,2], width, color='b',hatch='x',label="Hilbert")
rects4 = ax.bar(ind+2*width, SZ[:,3], width, color='y',hatch='/',label="Hilbert+zMesh")

ax.set_ylabel('Compression ratio',axis_font)
#ax.set_yscale('log')
y_major_locator=plt.MultipleLocator(50)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
ax.set_ylim([0,150])
ax.set_xlim([-0.3,N-0.3])
#ax.legend(ncol=3, prop=font,bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0)
#ax.set_title("P1 ZFP compression",axis_font)

ax.legend(ncol=2, prop=font)
ax.set_xlabel('Number of parallel processors',axis_font)
plt.savefig(name_hat+'SZ_parallel.pdf', format='pdf',bbox_inches="tight")
plt.show()

