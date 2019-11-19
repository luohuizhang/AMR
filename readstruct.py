import struct

cnt=[]
lev3=[]
lev4=[]
with open('datapoint.dat', 'rb') as f:
    for i in range(5):
        chunk = f.read(4)
        num= struct.unpack('i', chunk)[0] 
        cnt.append(num)
        for j in range(num):
            chunk = f.read(16)
            if i==3:
              print struct.unpack('iid', chunk)
            if i==4:
               print struct.unpack('iid', chunk)

