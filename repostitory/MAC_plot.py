import matplotlib.pyplot as plt
import numpy as np

import sys
import array
import os
import re 

name_hat = "/home/luo/Dropbox/SC2019_Huizhang/HPDC/SC20/figures/"
data = np.loadtxt("MAC.txt")
data=data.reshape(-1,4)
x=range(0,18)
namelist=["P1","P2","P3","P4","P5","P6","M1","M2","M3","M4","M5","M6","G1","G2","G3","G4","G5","G6"]
y1 =data[:,0]
y2 = data[:,1]
y3 =data[:,2]
y4 = data[:,3]
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
ax.set_ylabel('MAC',font)
ax.set_ylim([0,100])

#ax.set_title("ZFP",axis_font)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
ax.set_xlim([-0.5,18])
ax.legend(loc="upper right",ncol=4, prop=font)


plt.savefig(name_hat+'MAC_Zordering.pdf', format='pdf',bbox_inches="tight")
plt.show()





