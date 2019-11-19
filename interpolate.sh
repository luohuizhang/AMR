cd /home/luo/Chombo/BISICLES/examples/PineIslandGlacier
echo PineIslandGlacier
#../../code/filetools/stats2d.Linux.64.g++.gfortran.DEBUG.ex plot.pigv5.1km.l1l2.4lev.005138.2d.hdf5 918 1028 9.81
../PineIslandGlacier/interpolate_all
cd ../MISMIP3D/ 
echo MISMIP3D
#../../code/filetools/stats2d.Linux.64.g++.gfortran.DEBUG.ex plot.mismip3D.p075.l1l2.5lev.004993.2d.hdf5 918 1028 9.81
../PineIslandGlacier/interpolate_all
cd ../Greenland
echo Greenland
#../../code/filetools/stats2d.Linux.64.g++.gfortran.DEBUG.ex plot.GIS.5km.l1l2.5lev.000001.2d.hdf5 918 1028 9.81
../PineIslandGlacier/interpolate_all

