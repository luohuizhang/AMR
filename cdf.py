import numpy as np
import matplotlib.pyplot as plt
from matplotlib import mlab
import sys
import array
import os

if len(sys.argv) < 1 :
    print 'usage: python %s <file.dat' % sys.argv[0]
    sys.exit(0)

print sys.argv[1]


statinfo=os.stat(sys.argv[1])
fsize=statinfo.st_size
print fsize
fin = open(sys.argv[1], 'rb')
vals = array.array('d',(int(fsize/8))*[0])

fin.readinto(vals)
fin.close()
x1=min(vals);
x2=max(vals);
plt.figure(num=None,figsize=(3.5,3))
plt.rc('xtick', labelsize=24)          # fontsize of the tick labels
plt.rc('ytick', labelsize=24)
plt.ylim((0.0,1.0))   
plt.xlim(x1,x2)
plt.xticks([x1,x2])


axis_font = {'size':'20'}
axes = plt.gca()
plt.xlabel('Values', **axis_font)
#plt.ylabel('Frequency',**axis_font )
title_name=sys.argv[2]
plt.title(title_name, **axis_font)
#n, bins, patches=plt.hist(vals,bins=1000,normed=True,histtype='bar', label='pdf', color='blue')
n, bins, patches=plt.hist(vals,bins=1000,normed=True,histtype='step', cumulative=True, label='cdf',color='black')



plt.tight_layout()

#plt.savefig('/home/luo/Dropbox/SC2019_Huizhang/AMR2019/figures/fig_'+sys.argv[2]+'.pdf', format='pdf')
plt.show()
