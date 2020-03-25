import matplotlib.pyplot as plt
import numpy as np

import sys
import array
import os
import re 

name_hat = "/home/luo/Dropbox/SC2019_Huizhang/HPDC/SC20/figures/"
data = np.loadtxt("box_pattern.txt")
x=range(0,len(data))

y1 =data[:,0]
y2 = data[:,1]
#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure()
print np.shape(x)
axis_font = {'size':'28'}
plt.rc('xtick', labelsize=24)          # fontsize of the tick labels
plt.rc('ytick', labelsize=24)

font = {'size':'24'}
ax1 = fig.add_subplot(111)
lns1=ax1.plot(x, y1,'g-',label="Z-order")
lns2=ax1.plot(x, y2,'r-',label="Z-order+zMesh")
ax1.set_ylabel('Fetching efficiency',font)
ax1.set_ylim([0.4,1.3])
ax1.set_title("Pattern1 query",axis_font)
ax1.set_xlim([0,len(data)]);
#ax1.set_xlabel('Query ID',font)
ax1.legend(loc=0, prop=font)
#ax1.legend()


plt.savefig(name_hat+'fig_range_query.pdf', format='pdf',bbox_inches="tight")
plt.show()

data = np.loadtxt("row_pattern.txt")
x=range(0,len(data))

y1 =data[:,0]
y2 = data[:,1]
#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure()
print np.shape(x)
axis_font = {'size':'28'}
plt.rc('xtick', labelsize=24)          # fontsize of the tick labels
plt.rc('ytick', labelsize=24)

font = {'size':'24'}
ax1 = fig.add_subplot(111)
lns1=ax1.plot(x, y1,'g-',label="Z")
lns2=ax1.plot(x, y2,'r-',label="Z+LevelRe")
ax1.set_ylabel('Fetching efficiency',font)
ax1.set_title("Pattern2 query",axis_font)
ax1.set_xlim([0,len(data)]);
#ax1.set_xlabel('Query ID',font)
#ax1.legend(loc="upper right", prop=font)
#ax1.legend()


plt.savefig(name_hat+'fig_row_query.pdf', format='pdf',bbox_inches="tight")
plt.show()

data = np.loadtxt("col_pattern.txt")
x=range(0,len(data))

y1 =data[:,0]
y2 = data[:,1]
#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure()
print np.shape(x)
axis_font = {'size':'28'}
plt.rc('xtick', labelsize=24)          # fontsize of the tick labels
plt.rc('ytick', labelsize=24)

font = {'size':'24'}
ax1 = fig.add_subplot(111)
lns1=ax1.plot(x, y1,'g-',label="Z")
lns2=ax1.plot(x, y2,'r-',label="Z+LevelRe")
ax1.set_ylabel('Fetching efficiency',font)
ax1.set_title("Pattern3 query",axis_font)
ax1.set_xlim([0,len(data)]);
#ax1.set_xlabel('Query ID',font)
#ax1.legend(loc="upper right", prop=font)
#ax1.legend()


plt.savefig(name_hat+'fig_col_query.pdf', format='pdf',bbox_inches="tight")
plt.show()


data = np.loadtxt("box_pattern_h.txt")
x=range(0,len(data))

y1 =data[:,0]
y2 = data[:,1]
#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure()
print np.shape(x)
axis_font = {'size':'28'}
plt.rc('xtick', labelsize=24)          # fontsize of the tick labels
plt.rc('ytick', labelsize=24)

font = {'size':'24'}
ax1 = fig.add_subplot(111)
lns1=ax1.plot(x, y1,'b-',label="Hilbert")
lns2=ax1.plot(x, y2,'y-',label="Hilbert+zMesh")
ax1.set_ylabel('Fetching efficiency',font)
ax1.set_title("Pattern1 query",axis_font)
ax1.set_xlim([0,len(data)]);
ax1.set_ylim([0.6,1.2]);
#ax1.set_xlabel('Query ID',font)
ax1.legend(loc=0, prop=font)
#ax1.legend()


plt.savefig(name_hat+'fig_range_query_h.pdf', format='pdf',bbox_inches="tight")
plt.show()

data = np.loadtxt("row_pattern_h.txt")
x=range(0,len(data))

y1 =data[:,0]
y2 = data[:,1]
#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure()
print np.shape(x)
axis_font = {'size':'28'}
plt.rc('xtick', labelsize=24)          # fontsize of the tick labels
plt.rc('ytick', labelsize=24)

font = {'size':'24'}
ax1 = fig.add_subplot(111)
lns1=ax1.plot(x, y1,'b-',label="H")
lns2=ax1.plot(x, y2,'y-',label="H+LevelRe")
ax1.set_ylabel('Fetching efficiency',font)
ax1.set_title("Pattern2 query",axis_font)
ax1.set_xlim([0,len(data)]);
#ax1.set_xlabel('Query ID',font)
#ax1.legend(loc="upper right", prop=font)
#ax1.legend()


plt.savefig(name_hat+'fig_row_query_h.pdf', format='pdf',bbox_inches="tight")
plt.show()

data = np.loadtxt("col_pattern_h.txt")
x=range(0,len(data))

y1 =data[:,0]
y2 = data[:,1]
#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure()
print np.shape(x)
axis_font = {'size':'28'}
plt.rc('xtick', labelsize=24)          # fontsize of the tick labels
plt.rc('ytick', labelsize=24)

font = {'size':'24'}
ax1 = fig.add_subplot(111)
lns1=ax1.plot(x, y1,'r-',label="Baseline")
lns2=ax1.plot(x, y2,'b-',label="LevelRe")
ax1.set_ylabel('Fetching efficiency',font)
ax1.set_title("Pattern3 query",axis_font)
ax1.set_xlim([0,len(data)]);
#ax1.set_xlabel('Query ID',font)
#ax1.legend(loc="upper right", prop=font)
#ax1.legend()


plt.savefig(name_hat+'fig_col_query_h.pdf', format='pdf',bbox_inches="tight")
plt.show()

