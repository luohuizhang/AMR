import matplotlib.pyplot as plt
import numpy as np

import sys
import array
import os
import re 

name_hat = "/home/luo/Dropbox/SC2019_Huizhang/HPDC/SC20/figures/"
data = np.loadtxt("result.txt")
data=data.reshape(-1,8)
x=range(0,18)
namelist=["P1","P2","P3","P4","P5","P6","M1","M2","M3","M4","M5","M6","G1","G2","G3","G4","G5","G6"]
y1 =data[:,0]
y2 = data[:,1]
y3= data[:,2]
y4= data[:,3]
y5 =data[:,4]
y6 = data[:,5]
y7= data[:,6]
y8= data[:,7]
fig = plt.figure(num=None,figsize=(20,4))
#fig = plt.figure()
print np.shape(x)
axis_font = {'size':'24'}
plt.rc('xtick', labelsize=24)          # fontsize of the tick labels
plt.rc('ytick', labelsize=24)

N = len(x)
print N
ind = np.arange(N)  # the x locations for the groups
width = 0.2       # the width of the bars

ax = fig.add_subplot(111)
font = {'size':'24'}



rects1 = ax.bar(ind-width, y1, width, color='g',label="Z")
rects2 = ax.bar(ind, y2, width, color='r',label="Z+LevelRe")
rects3 = ax.bar(ind+width, y3, width, color='b',label="H")
rects4 = ax.bar(ind+2*width, y4, width, color='y',label="H+LevelRe")
ax.set_ylabel('Compression ratio',font)
#ax.set_title("ZFP",axis_font)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
ax.set_xlim([-0.5,18])
ax.legend(loc=2,ncol=4, prop=font)


plt.savefig(name_hat+'CR_ZFP_Zordering.pdf', format='pdf',bbox_inches="tight")
plt.show()


fig = plt.figure(num=None,figsize=(20,4))
#fig = plt.figure()
print np.shape(x)
axis_font = {'size':'24'}
plt.rc('xtick', labelsize=24)          # fontsize of the tick labels
plt.rc('ytick', labelsize=24)
ax = fig.add_subplot(111)
font = {'size':'24'}



rects1 = ax.bar(ind-width, y5, width, color='g',label="Z")
rects2 = ax.bar(ind, y6, width, color='r',label="Z+LevelRe")
rects3 = ax.bar(ind+width, y7, width, color='b',label="H")
rects4 = ax.bar(ind+2*width, y8, width, color='y',label="H+LevelRe")
ax.set_ylabel('Compression ratio',font)
y_major_locator=plt.MultipleLocator(100)
ax.yaxis.set_major_locator(y_major_locator)
#ax.set_title("ZFP",axis_font)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
ax.set_xlim([-0.5,18])
ax.legend(loc=2,ncol=2, prop=font)


plt.savefig(name_hat+'CR_SZ_Zordering.pdf', format='pdf',bbox_inches="tight")
plt.show()



