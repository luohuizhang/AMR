#!/usr/bin/env python
'''Reads NeXus HDF5 files using h5py and prints the contents'''

import h5py    # HDF5 support

fileName = "plot.pigv5.1km.l1l2.4lev.005138.2d.hdf5"
f = h5py.File(fileName,  "r")
for item in f.attrs.keys():
    print(item + ":", f.attrs[item])
mr = f['/level_4/boxes']
print("%s\t%s" % ("#", "mr"))
for i in range(len(mr)):
    #print("%d\t%g" % (i, mr[i]))
    print mr[i]
f.close()
