import matplotlib.pyplot as plt
import numpy as np

import sys
import array
import os
import re 

name_hat = "/home/luo/Dropbox/SC2019_Huizhang/HPDC/SC20/figures/"
data = np.loadtxt("box_pattern1.txt")
x=range(0,len(data))

y1 =data[:,0]
y2 = data[:,1]
#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure()
print np.shape(x)
axis_font = {'size':'28'}
plt.rc('xtick', labelsize=20)          # fontsize of the tick labels
plt.rc('ytick', labelsize=20)

font = {'size':'24'}
ax1 = fig.add_subplot(111)
lns1=ax1.plot(x, y1,'g-',label="Z")
lns2=ax1.plot(x, y2,'r-',label="Z+LevelRe")
ax1.set_ylabel('Fetching efficiency',font)
ax1.set_title("Pattern3 query",axis_font)
ax1.set_xlim([0,len(data)]);
#ax1.set_xlabel('Query ID',font)
#ax1.legend(loc="center right",prop=font)
#ax1.legend()


plt.savefig(name_hat+'fig_range_query1.pdf', format='pdf',bbox_inches="tight")
plt.show()

data = np.loadtxt("row_pattern1.txt")
x=range(0,len(data))

y1 =data[:,0]
y2 = data[:,1]
#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure()
print np.shape(x)
axis_font = {'size':'28'}
plt.rc('xtick', labelsize=20)          # fontsize of the tick labels
plt.rc('ytick', labelsize=20)

font = {'size':'24'}
ax1 = fig.add_subplot(111)
lns1=ax1.plot(x, y1,'g-',label="Z")
lns2=ax1.plot(x, y2,'r-',label="Z+LevelRe")
ax1.set_ylabel('Fetching efficiency',font)
ax1.set_title("Pattern4 query",axis_font)
ax1.set_xlim([0,len(data)]);
ax1.set_xlabel('Query ID',font)
#ax1.legend(loc="center right",prop=font)


plt.savefig(name_hat+'fig_row_query1.pdf', format='pdf',bbox_inches="tight")
plt.show()

data = np.loadtxt("col_pattern1.txt")
x=range(0,len(data))

y1 =data[:,0]
y2 = data[:,1]
#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure()
print np.shape(x)
axis_font = {'size':'28'}
plt.rc('xtick', labelsize=20)          # fontsize of the tick labels
plt.rc('ytick', labelsize=20)

font = {'size':'24'}
ax1 = fig.add_subplot(111)
lns1=ax1.plot(x, y1,'r-',label="Baseline")
lns2=ax1.plot(x, y2,'b-',label="LevelRe")
ax1.set_ylabel('Fetching efficiency',font)
ax1.set_title("Pattern6 query",axis_font)
ax1.set_xlim([0,len(data)]);
ax1.set_xlabel('Query ID',font)
#ax1.legend(loc="center right",prop=font)


plt.savefig(name_hat+'fig_col_query1.pdf', format='pdf',bbox_inches="tight")
plt.show()



data = np.loadtxt("box_pattern_h1.txt")
x=range(0,len(data))

y1 =data[:,0]
y2 = data[:,1]
#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure()
print np.shape(x)
axis_font = {'size':'28'}
plt.rc('xtick', labelsize=20)          # fontsize of the tick labels
plt.rc('ytick', labelsize=20)

font = {'size':'24'}
ax1 = fig.add_subplot(111)
lns1=ax1.plot(x, y1,'b-',label="H")
lns2=ax1.plot(x, y2,'y-',label="H+LevelRe")
ax1.set_ylabel('Fetching efficiency',font)
ax1.set_title("Pattern3 query",axis_font)
ax1.set_xlim([0,len(data)]);
#ax1.set_xlabel('Query ID',font)
#ax1.legend(loc="center right",prop=font)
#ax1.legend()


plt.savefig(name_hat+'fig_range_query_h1.pdf', format='pdf',bbox_inches="tight")
plt.show()

data = np.loadtxt("row_pattern_h1.txt")
x=range(0,len(data))

y1 =data[:,0]
y2 = data[:,1]
#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure()
print np.shape(x)
axis_font = {'size':'28'}
plt.rc('xtick', labelsize=20)          # fontsize of the tick labels
plt.rc('ytick', labelsize=20)

font = {'size':'24'}
ax1 = fig.add_subplot(111)
lns1=ax1.plot(x, y1,'b-',label="H")
lns2=ax1.plot(x, y2,'y-',label="H+LevelRe")
ax1.set_ylabel('Fetching efficiency',font)
ax1.set_title("Pattern4 query",axis_font)
ax1.set_xlim([0,len(data)]);
ax1.set_xlabel('Query ID',font)
#ax1.legend(loc="center right",prop=font)


plt.savefig(name_hat+'fig_row_query_h1.pdf', format='pdf',bbox_inches="tight")
plt.show()

data = np.loadtxt("col_pattern_h1.txt")
x=range(0,len(data))

y1 =data[:,0]
y2 = data[:,1]
#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure()
print np.shape(x)
axis_font = {'size':'28'}
plt.rc('xtick', labelsize=20)          # fontsize of the tick labels
plt.rc('ytick', labelsize=20)

font = {'size':'24'}
ax1 = fig.add_subplot(111)
lns1=ax1.plot(x, y1,'r-',label="Baseline")
lns2=ax1.plot(x, y2,'b-',label="LevelRe")
ax1.set_ylabel('Fetching efficiency',font)
ax1.set_title("Pattern6 query",axis_font)
ax1.set_xlim([0,len(data)]);
ax1.set_xlabel('Query ID',font)
#ax1.legend(loc="center right",prop=font)


plt.savefig(name_hat+'fig_col_query_h1.pdf', format='pdf',bbox_inches="tight")
plt.show()

