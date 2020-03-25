import matplotlib.pyplot as plt
import numpy as np

import sys
import array
import os
import re 

name_hat = "/home/luo/Dropbox/SC2019_Huizhang/HPDC/SC20/figures/"

data = np.loadtxt("level_overhead.txt")
data=data.reshape(-1,5)
data_H = np.loadtxt("level_overhead_H.txt")
data_H=data_H.reshape(-1,5)
x =[2,3,4,5,6,7,8,9]
#z1 = [5.230,5.837,9.358,7.098,5.925,5.331,5.277,5.974 ]
#z2 = [2.456,7.504,3.269,3.984,7.384,11.163,25.261,40.860]
#z3 = [103.526,76.541,63.936,52.817,49.631,47.876,46.092,46.122]
#z4 = [0.580,0.923,1.203,1.461,2.493,1.691,1.666,1.699]
#z5 = [1.621,1.740,1.973,2.273,2.446,2.485,2.460,2.596]

datasize=[39572.0,67736,128016,263044,543712,1094888,2227500,4574888]
for j in range(0,5):
    for i in range (0,8):
        data[i][j]=134217728/datasize[i]*data[i][j]
        data_H[i][j]=134217728/datasize[i]*data_H[i][j]
z1 = data[:,0] 
z2 = data[:,1] 
z3 = data[:,2] 
z4 = data[:,3] 
z5 = data[:,4]
z6 = data_H[:,0] 
z7 = data_H[:,1] 
z8 = data_H[:,2] 
z9 = data_H[:,3] 
z10 =data_H[:,4]

#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure(num=None,figsize=(8,4))
axis_font = {'size':'24'}
plt.rc('xtick', labelsize=24)          # fontsize of the tick labels
plt.rc('ytick', labelsize=24)
font = {'size':'24'}


N = len(x)
ind = np.arange(N)  # the x locations for the groups
width = 0.2       # the width of the bars

ax = fig.add_subplot(111)

rects1 = ax.bar(ind, z2, width, color='r',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, z7, width, color='y',label="Hilbert+zMesh")

ax.set_ylabel('Time for 1GB data (s)',axis_font)
ax.set_ylim([0,2])
ax.set_xticks(ind+width)
ax.set_xticklabels( x )
ax.set_xlim([-0.1,7.5])
ax.set_xlabel('Number of AMR levels',axis_font)
ax.legend(loc=2, prop=font)
ax.set_title("Initialization",axis_font)

plt.savefig(name_hat+'Initialization_G.pdf', format='pdf',bbox_inches="tight")
plt.show()
fig = plt.figure(num=None,figsize=(8,4))

ax = fig.add_subplot(111)

rects1 = ax.bar(ind-width, z1, width, color='g',label="Z-order" )
rects2 = ax.bar(ind, z3, width, color='r',label="Z-order+zMesh")
rects3 = ax.bar(ind+width, z6, width, color='blue',label="Hilbert" )
rects4 = ax.bar(ind+2*width, z8, width, color='y',label="Hilbert+zMesh")
ax.set_ylabel('Time for 1GB data (s)',axis_font)
ax.set_xlabel('Number of AMR levels',axis_font)
ax.set_xticks(ind+width)
ax.set_ylim([0,15])
ax.set_xticklabels( x )
ax.set_xlim([-0.3,7.7])
ax.set_title("Space filling",axis_font)
ax.legend( loc=0,ncol=1,prop=font)
plt.savefig(name_hat+'Reordering_G.pdf', format='pdf',bbox_inches="tight")
plt.show()

fig = plt.figure(num=None,figsize=(8,4))

ax = fig.add_subplot(111)

rects1 = ax.bar(ind, z4, width, color='r',label='Z-order+zMesh' )
rects3 = ax.bar(ind+width, z9, width, color='y',label="Hilbert+zMesh")

ax.set_ylabel('Time for 1GB data (s)',axis_font)
ax.set_ylim([0,3])
ax.set_xlabel('Number of AMR levels',axis_font)
ax.set_xticks(ind+width)
ax.set_xticklabels( x )
ax.set_xlim([-0.1,7.5])
ax.set_xlabel('Number of AMR levels',axis_font)
ax.legend(loc="up left",ncol=1,prop=font)
ax.set_title("Tree building",axis_font)
plt.savefig(name_hat+'Tree_Building_G.pdf', format='pdf',bbox_inches="tight")
plt.show()


fig = plt.figure(num=None,figsize=(8,4))

ax = fig.add_subplot(111)

rects2 = ax.bar(ind, z5, width, color='r',label="Z-order+zMesh")
rects4 = ax.bar(ind+width, z10, width, color='y',label="Hilbert+zMesh")

ax.set_ylabel('Time for 1GB data (s)',axis_font)
ax.set_ylim([0,3])
ax.set_xlabel('Number of AMR levels',axis_font)
ax.set_xticks(ind+width)
ax.set_xticklabels( x )
ax.set_xlim([-0.1,7.5])
ax.legend(loc=2,ncol=1, prop=font)
ax.set_title("Traversing",axis_font)
plt.savefig(name_hat+'Traveling_G.pdf', format='pdf',bbox_inches="tight")
plt.show()

