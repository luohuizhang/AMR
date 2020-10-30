#!/usr/bin/env python
'''Reads NeXus HDF5 files using h5py and prints the contents'''
import numpy as np
import h5py    # HDF5 support
import struct
fileName = "plot.GIS.5km.l1l2.5lev.000000.2d.hdf5"
f = h5py.File(fileName,  "r")
fw = open('box', 'wb')
#for item in f.attrs.keys():
#    print(item + ":", f.attrs[item])
for lev in range(0,6):
    attrs="/level_"+str(lev)+"/boxes"
    mr = f[attrs]
    data=len(mr)
    print data
    s = struct.pack('i', data)
    fw.write(s)
    for i in range(len(mr)):
        #print mr[i]
        data=mr[i][0]
        s = struct.pack('i', data)
        fw.write(s)
        data=mr[i][1]
        s = struct.pack('i', data)
        fw.write(s)
        data=mr[i][2]
        s = struct.pack('i', data)
        fw.write(s)
        data=mr[i][3]
        s = struct.pack('i', data)
        fw.write(s)
    attrs="/level_"+str(lev)+"/Processors"
    mr = f[attrs]
   # print("%s\t%s" % ("#", "mr"))
    data=mr[:]
   # print data
    s = struct.pack('i'*len(data), *data)
    fw.write(s)
f.close()


fw.close()

