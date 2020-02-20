import matplotlib.pyplot as plt
import numpy as np

import sys
import array
import os
import re 

name_hat = "/home/luo/Dropbox/SC2019_Huizhang/HPDC/SC20/figures/"


x =[2,3,4,5,6,7,8,9]
#z1 = [5.230,5.837,9.358,7.098,5.925,5.331,5.277,5.974 ]
#z2 = [2.456,7.504,3.269,3.984,7.384,11.163,25.261,40.860]
#z3 = [103.526,76.541,63.936,52.817,49.631,47.876,46.092,46.122]
#z4 = [0.580,0.923,1.203,1.461,2.493,1.691,1.666,1.699]
#z5 = [1.621,1.740,1.973,2.273,2.446,2.485,2.460,2.596]

z1 = [1.689,1.668,1.816,1.954,1.946,1.896,1.835,2.634]
z2 = [1.893,1.936,2.118,2.086,2.174,2.269,2.437,2.878]
z3 = [5.702,4.805,4.496,4.454,4.639,4.563,4.420,4.998]
z4 = [0.149,0.319,0.498,0.910,1.076,1.189,1.206,1.239]
z5 = [0.855,1.092,1.437,1.988,2.038,2.057,1.977,2.019]


#fig = plt.figure(num=None,figsize=(12,7))
fig = plt.figure()
axis_font = {'size':'28'}
plt.rc('xtick', labelsize=24)          # fontsize of the tick labels
plt.rc('ytick', labelsize=24)
font = {'size':'24'}


N = len(x)
ind = np.arange(N)  # the x locations for the groups
width = 0.3       # the width of the bars

ax = fig.add_subplot(111)

rects2 = ax.bar(ind+width, z2, width, color='g',label="LevelRe")

ax.set_ylabel('Time for 1GB data (s)',axis_font)
ax.set_xticks(ind+width)
ax.set_xticklabels( x )
ax.legend(loc=2, prop=font)
ax.set_title("Initialization",axis_font)
#ax.set_xlabel('Number of AMR levels',axis_font)
#def autolabel(rects):
 #   for rect in rects:
  #      h = rect.get_height()
   #     ax.text(rect.get_x()+rect.get_width()/2., 1.05*h, '%d'%int(h),
    #            ha='center', va='bottom')




#autolabel(rects1)
#autolabel(rects2)


#font = {'size':'24'}
#ax1 = fig.add_subplot(111)
#lns1=ax1.plot(x, y1,'-',label="Impact on CR")
#ax1.set_ylabel('CR',font)
#ax1.set_title("Initialization time",axis_font)
#ax1.legend(loc=0)
#ax1.legend()

#ax2 = ax.twinx()  # this is the important function
#lns2=ax2.plot(x, y3, '-r',label="Impact on NRMSE")
#lns1=ax2.plot(x, y4,'-',label="Impact on CR")
#ax2.set_xlim([0, np.e])
#ax2.set_ylabel('NRMSE',font)
#ax2.set_xlabel('S',font)
#ax2.legend(['Impact on NRMSE'])
#plt.legend()
#ax2.legend(loc=0)
#lns = lns1+lns2
#labs = [l.get_label() for l in lns]
#ax1.legend(lns, labs, loc=0)

plt.savefig(name_hat+'Initialization_G.pdf', format='pdf',bbox_inches="tight")
plt.show()
fig = plt.figure()

ax = fig.add_subplot(111)

rects1 = ax.bar(ind, z1, width, color='r' )
rects2 = ax.bar(ind+width, z3, width, color='g')

ax.set_ylabel('Time for 1GB data (s)',axis_font)
#ax.set_xlabel('Number of AMR levels',axis_font)
ax.set_xticks(ind+width)
ax.set_ylim([0,8])
ax.set_xticklabels( x )
ax.legend( (rects1[0], rects2[0]), ('Baseline', 'LevelRe') , loc="up left",prop=font)
ax.set_title("Z-ordering",axis_font)
plt.savefig(name_hat+'Reordering_G.pdf', format='pdf',bbox_inches="tight")
plt.show()

fig = plt.figure()

ax = fig.add_subplot(111)

rects1 = ax.bar(ind+width, z4, width, color='g',label='LevelRe' )
#rects2 = ax.bar(ind+width, y4, width, color='g')

ax.set_ylabel('Time for 1GB data (s)',axis_font)
ax.set_xlabel('Number of AMR levels',axis_font)
ax.set_xticks(ind+width)
ax.set_xticklabels( x )
ax.legend(loc="up left",prop=font)
ax.set_title("Tree building",axis_font)
plt.savefig(name_hat+'Tree_Building_G.pdf', format='pdf',bbox_inches="tight")
plt.show()


fig = plt.figure()

ax = fig.add_subplot(111)

rects2 = ax.bar(ind+width, z5, width, color='g',label="LevelRe")

ax.set_ylabel('Time for 1GB data (s)',axis_font)
ax.set_xlabel('Number of AMR levels',axis_font)
ax.set_xticks(ind+width)
ax.set_xticklabels( x )
ax.legend(loc=2, prop=font)
ax.set_title("Traversing",axis_font)
plt.savefig(name_hat+'Traveling_G.pdf', format='pdf',bbox_inches="tight")
plt.show()

