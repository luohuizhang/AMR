import matplotlib.pyplot as plt
import numpy as np

import sys
import array
import os
import re 

name_hat = "/home/luo/Dropbox/SC2019_Huizhang/HPDC/SC20/figures/"
data = np.loadtxt("CR_RMSE_MaxE.txt")
x=range(0,18)
namelist=["P1","P2","P3","P4","P5","P6","M1","M2","M3","M4","M5","M6","G1","G2","G3","G4","G5","G6"]
y1 =data[:,0]
y2 = data[:,1]
y3= data[:,2]
y4= data[:,3]
#fig = plt.figure(num=None,figsize=(20,4))
#fig = plt.figure()
print np.shape(x)
axis_font = {'size':'24'}
#plt.rc('xtick', labelsize=24)          # fontsize of the tick labels
#plt.rc('ytick', labelsize=24)

N = len(x)
print N
ind = np.arange(N)  # the x locations for the groups
width = 0.2       # the width of the bars

#ax = fig.add_subplot(111)
font = {'size':'24'}



#rects1 = ax.bar(ind-width, y1, width, color='g',label="Z+ZFP")
#rects2 = ax.bar(ind, y2, width, color='r',label="Z+LevelRe+ZFP")
#rects3 = ax.bar(ind+width, y3, width, color='b',label="Z+SZ")
#rects4 = ax.bar(ind+2*width, y4, width, color='y',label="Z+LevelRe+SZ")
#ax.set_ylabel('RMSE',font)
#ax.set_yscale('log')
#ax.set_ylim([1E-4,10000])
#ax.set_title("RMSE comparison",axis_font)
#ax.set_xticks(ind+width)
#ax.set_xticklabels( namelist )
#ax.set_xlim([-0.5,18])
#ax.legend(loc=2,ncol=4, prop=font)


#plt.savefig(name_hat+'RMSE.pdf', format='pdf',bbox_inches="tight")
#plt.show()


y1 =data[:,4]
y2 = data[:,5]
y3= data[:,6]
y4= data[:,7]

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



rects1 = ax.bar(ind-width, y1, width, color='g',label="Z-order+ZFP")
rects2 = ax.bar(ind, y2, width, color='r',label="Z-order+zMesh+ZFP")
rects3 = ax.bar(ind+width, y3, width, color='b',label="Z-order+SZ")
rects4 = ax.bar(ind+2*width, y4, width, color='y',label="Z-order+zMesh+SZ")
ax.set_ylabel('Max Error',font)
#ax.set_yscale('log')
ax.set_ylim([0,1.8])
y_major_locator=plt.MultipleLocator(0.5)
ax.yaxis.set_major_locator(y_major_locator)
#ax.set_title("Z-ordering",axis_font)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
ax.set_xlim([-0.5,18])
ax.legend(loc=0,ncol=2, prop=font)


plt.savefig(name_hat+'MaxErr.pdf', format='pdf',bbox_inches="tight",pad_inches=0)
plt.show()


data = np.loadtxt("CR_RMSE_MaxE_H.txt")

y1 =data[:,4]
y2 = data[:,5]
y3= data[:,6]
y4= data[:,7]

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



rects1 = ax.bar(ind-width, y1, width, color='g',label="Hilbert+ZFP")
rects2 = ax.bar(ind, y2, width, color='r',label="Hilbert+zMesh+ZFP")
rects3 = ax.bar(ind+width, y3, width, color='b',label="Hilbert+SZ")
rects4 = ax.bar(ind+2*width, y4, width, color='y',label="Hilbert+zMesh+SZ")
ax.set_ylabel('Max Error',font)
#ax.set_yscale('log')
ax.set_ylim([0,1.8])
y_major_locator=plt.MultipleLocator(0.5)
ax.yaxis.set_major_locator(y_major_locator)
#ax.set_title("Hilbert curve filling",axis_font)
ax.set_xticks(ind+width)
ax.set_xticklabels( namelist )
ax.set_xlim([-0.5,18])
ax.legend(loc=0,ncol=2, prop=font)


plt.savefig(name_hat+'MaxErr_H.pdf', format='pdf',bbox_inches="tight",pad_inches=0)
plt.show()

