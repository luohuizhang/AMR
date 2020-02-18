


cd ../repostitory/
sed -i "7s/.*/#define Level 5/" ../repostitory/reordering.c
make -f Makefile

cd /home/luo/Chombo/BISICLES/examples/PineIslandGlacier
echo PineIslandGlacier
#../../code/filetools/stats_all182d.Linux.64.g++.gfortran.DEBUG.ex plot.pigv5.1km.l1l2.4lev.005138.2d.hdf5 918 1028 9.81
../repostitory/reordering


cd ../repostitory/
sed -i "7s/.*/#define Level 9/" ../repostitory/reordering.c
make -f Makefile
cd ../MISMIP3D/ 
echo MISMIP3D
#../../code/filetools/stats_all182d.Linux.64.g++.gfortran.DEBUG.ex plot.mismip3D.p075.l1l2.9lev.000000.2d.hdf5 918 1028 9.81
../../code/filetools/stats_all182d.Linux.64.g++.gfortran.DEBUG.ex plot.mismip3D.p075.l1l2.8lev.000512.2d.hdf5 918 1028 9.81
../repostitory/reordering




cd ../repostitory/
sed -i "7s/.*/#define Level 6/" ../repostitory/reordering.c
make -f Makefile
cd ../Greenland
echo Greenland
#../../code/filetools/stats_all182d.Linux.64.g++.gfortran.DEBUG.ex plot.GIS.5km.l1l2.5lev.000000.2d.hdf5 918 1028 9.81
../repostitory/reordering

