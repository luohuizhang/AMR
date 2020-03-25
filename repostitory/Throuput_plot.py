import matplotlib.pyplot as plt
import numpy as np

import sys
import array
import os
import re 

name_hat = "/home/luo/Dropbox/SC2019_Huizhang/HPDC/SC20/figures/"

data = np.loadtxt("throuput.txt")
#data=data.reshape(-1,5)
data_H = np.loadtxt("throuput_H.txt")
#data_H=data_H.reshape(-1,5)
x =range(0,6)
namelist=[ "(P,1)","(M,1)","(G,1)","(P,6)","(M,6)","(G,6)"]
#namelist=["P1","P2","P3","P4","P5","P6"]
Z=np.zeros((8,6),dtype=float)
for i in range(0,8):
    for j in range(0,6):
        Z[i][j]=data[i//2][i%2+2*j] 
print Z
H=np.zeros((8,6),dtype=float)
for i in range(0,8):
    for j in range(0,6):
        H[i][j]=data_H[i//2][i%2+2*j] 

print H

N = len(x)
ind = np.arange(N)  # the x locations for the groups
width = 0.2       # the width of the bars

fig = plt.figure(num=None,figsize=(8,4))
axis_font = {'size':'24'}
plt.rc('xtick', labelsize=24)          # fontsize of the tick labels
plt.rc('ytick', labelsize=24)
font = {'size':'24'}



ax = fig.add_subplot(111)

rects1 = ax.bar(ind-width, Z[0,:], width, color='g',label="Z-order" )
rects2 = ax.bar(ind, Z[1,:], width, color='r',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, H[0,:], width, color='blue',label="Hilbert" )
rects4 = ax.bar(ind+2*width, H[1,:], width, color='y',label="Hilbert+zMesh")

ax.set_ylabel('Throughput (MB/s)',axis_font)
y_major_locator=plt.MultipleLocator(200)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
ax.set_ylim([0,900])
ax.set_xlim([-0.3,5.7])
ax.legend(loc=2,ncol=1, prop=font)
ax.set_title("ZFP compression",axis_font)

plt.savefig(name_hat+'ThrouputZFPCM.pdf', format='pdf',bbox_inches="tight")
plt.show()


fig = plt.figure(num=None,figsize=(8,4))
plt.rc('xtick', labelsize=24)          # fontsize of the tick labels
plt.rc('ytick', labelsize=24)



ax = fig.add_subplot(111)

rects1 = ax.bar(ind-width, Z[2,:], width, color='g',label="Z" )
rects2 = ax.bar(ind, Z[3,:], width, color='r',label="Z+LevelRe")
rects3 = ax.bar(ind+width, H[2,:], width, color='blue',label="H" )
rects4 = ax.bar(ind+2*width, H[3,:], width, color='y',label="H+LevelRe")

ax.set_ylabel('Throughput (MB/s)',axis_font)
y_major_locator=plt.MultipleLocator(100)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
ax.set_ylim([0,400])
ax.set_xlim([-0.3,5.7])
#ax.legend(loc=2,ncol=2, prop=font)
ax.set_title("ZFP decompression",axis_font)

plt.savefig(name_hat+'ThrouputZFPDECM.pdf', format='pdf',bbox_inches="tight")
plt.show()



fig = plt.figure(num=None,figsize=(8,4))
plt.rc('xtick', labelsize=24)          # fontsize of the tick labels
plt.rc('ytick', labelsize=24)



ax = fig.add_subplot(111)

rects1 = ax.bar(ind-width, Z[4,:], width, color='g',label="Z" )
rects2 = ax.bar(ind, Z[5,:], width, color='r',label="Z+LevelRe")
rects3 = ax.bar(ind+width, H[4,:], width, color='blue',label="H" )
rects4 = ax.bar(ind+2*width, H[5,:], width, color='y',label="H+LevelRe")

ax.set_ylabel('Throughput (MB/s)',axis_font)
y_major_locator=plt.MultipleLocator(100)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
ax.set_ylim([0,400])
ax.set_xlim([-0.3,5.7])
#ax.legend(loc=2,ncol=2, prop=font)
ax.set_title("SZ compression",axis_font)

plt.savefig(name_hat+'ThrouputSZCM.pdf', format='pdf',bbox_inches="tight")
plt.show()



fig = plt.figure(num=None,figsize=(8,4))
plt.rc('xtick', labelsize=24)          # fontsize of the tick labels
plt.rc('ytick', labelsize=24)



ax = fig.add_subplot(111)

rects1 = ax.bar(ind-width, Z[6,:], width, color='g',label="Z" )
rects2 = ax.bar(ind, Z[7,:], width, color='r',label="Z+LevelRe")
rects3 = ax.bar(ind+width, H[6,:], width, color='blue',label="H" )
rects4 = ax.bar(ind+2*width, H[7,:], width, color='y',label="H+LevelRe")

ax.set_ylabel('Throughput (MB/s)',axis_font)
y_major_locator=plt.MultipleLocator(100)
ax.yaxis.set_major_locator(y_major_locator)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
ax.set_ylim([0,400])
ax.set_xlim([-0.3,5.7])
#ax.legend(loc=2,ncol=2, prop=font)
ax.set_title("SZ decompression",axis_font)

plt.savefig(name_hat+'ThrouputSZDECM.pdf', format='pdf',bbox_inches="tight")
plt.show()

