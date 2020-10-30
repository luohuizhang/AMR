import matplotlib.pyplot as plt
import numpy as np

import sys
import array
import os
import re 

name_hat = "/home/luo/Dropbox/SC2019_Huizhang/HPDC/IPDPS21/figures/"
data = np.loadtxt("../repostitory/box_pattern.txt")
x=range(0,len(data))

y1 =data[:,0]
y2 = data[:,1]
#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure()
print np.shape(x)
axis_font = {'size':'30'}
plt.rc('xtick', labelsize=28)          # fontsize of the tick labels
plt.rc('ytick', labelsize=28)

font = {'size':'28'}
ax1 = fig.add_subplot(111)
lns1=ax1.plot(x, y1,'g-',label="Z-order")
lns2=ax1.plot(x, y2,'r-',label="Z-order+zMesh")
ax1.set_ylabel('Fetching efficiency',font)
ax1.set_ylim([0.4,1.3])
y_major_locator=plt.MultipleLocator(0.2)
ax1.yaxis.set_major_locator(y_major_locator)
#ax1.set_title("Z-order: Pattern 1",axis_font)
ax1.set_xlim([0,len(data)]);
ax1.set_xlabel('Query ID\n(a)  Pattern 1',font)
ax1.legend(loc=0, prop=font)
#ax1.legend()


plt.savefig(name_hat+'fig_range_query.pdf', format='pdf',bbox_inches="tight")
#plt.show()

data = np.loadtxt("../repostitory/row_pattern.txt")
x=range(0,len(data))

y1 =data[:,0]
y2 = data[:,1]
#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure()
ax1 = fig.add_subplot(111)
lns1=ax1.plot(x, y1,'g-',label="Z")
lns2=ax1.plot(x, y2,'r-',label="Z+LevelRe")
ax1.set_ylabel('Fetching efficiency',font)
#ax1.set_title("Z-order: Pattern 2",axis_font)
ax1.set_xlim([0,len(data)]);
ax1.set_xlabel('Query ID\n(b) Pattern 2',font)
#ax1.legend(loc="upper right", prop=font)
#ax1.legend()


plt.savefig(name_hat+'fig_row_query.pdf', format='pdf',bbox_inches="tight")
#plt.show()


data = np.loadtxt("../repostitory/box_pattern1.txt")
x=range(0,len(data))

y1 =data[:,0]
y2 = data[:,1]
#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure()
print np.shape(x)
axis_font = {'size':'30'}
plt.rc('xtick', labelsize=28)          # fontsize of the tick labels
plt.rc('ytick', labelsize=28)

font = {'size':'28'}
ax1 = fig.add_subplot(111)
lns1=ax1.plot(x, y1,'g-',label="Z")
lns2=ax1.plot(x, y2,'r-',label="Z+LevelRe")
ax1.set_ylabel('Fetching efficiency',font)
#ax1.set_title("Z-order: Pattern 3",axis_font)
ax1.set_xlim([0,len(data)]);
ax1.set_xlabel('Query ID\n(c) Pattern 3',font)
#ax1.legend(loc="center right",prop=font)
#ax1.legend()


plt.savefig(name_hat+'fig_range_query1.pdf', format='pdf',bbox_inches="tight")
#plt.show()

data = np.loadtxt("../repostitory/row_pattern1.txt")
x=range(0,len(data))

y1 =data[:,0]
y2 = data[:,1]
#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure()
ax1 = fig.add_subplot(111)
lns1=ax1.plot(x, y1,'g-',label="Z")
lns2=ax1.plot(x, y2,'r-',label="Z+LevelRe")
ax1.set_ylabel('Fetching efficiency',font)
#ax1.set_title("Z-order: Pattern 4",axis_font)
ax1.set_xlim([0,len(data)]);
ax1.set_xlabel('Query ID\n(d) Pattern 4',font)
#ax1.legend(loc="center right",prop=font)


plt.savefig(name_hat+'fig_row_query1.pdf', format='pdf',bbox_inches="tight")
#plt.show()

