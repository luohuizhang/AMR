cd /home/luo/Chombo/BISICLES/examples/PineIslandGlacier
echo PineIslandGlacier

#../../code/filetools/stats2d.Linux.64.g++.gfortran.DEBUG.ex plot.pigv5.1km.l1l2.4lev.005138.2d.hdf5 918 1028 9.81
#python ../PineIslandGlacier/value_plot.py Level_row.dat PineIslandGlacier_Row-major 
#python ../PineIslandGlacier/value_plot.py Level_row_levelreordering.dat PineIslandGlacier_Row-major+Level-reordering
#python ../PineIslandGlacier/value_plot.py Level_box.dat PineIslandGlacier_Row-major
#python ../PineIslandGlacier/value_plot.py Level_box_levelreordering.dat PineIslandGlacier_Row-major+Box+Level-reordering
#python ../PineIslandGlacier/value_plot.py Level_row_zordering.dat PineIslandGlacier_Z-ordering
#python ../PineIslandGlacier/value_plot.py Level_row_zordering_levelreordering.dat PineIslandGlacier_Z-ordering+Level-reordering
python ../PineIslandGlacier/value_plot.py Level_box_zordering.dat PineIslandGlacier_Z-ordering
python ../PineIslandGlacier/value_plot.py Level_box_zordering_levelreordering.dat PineIslandGlacier_Z-ordering+level-reordering

cd ../MISMIP3D/ 
echo MISMIP3D
#../../code/filetools/stats2d.Linux.64.g++.gfortran.DEBUG.ex plot.mismip3D.p075.l1l2.5lev.004993.2d.hdf5 918 1028 9.81
#python ../PineIslandGlacier/value_plot.py Level_raw.dat MISMIP3D_Row-major 
#python ../PineIslandGlacier/value_plot.py Level_boxlevel.dat MISMIP3D_Row-major+Level-reordering
#python ../PineIslandGlacier/value_plot.py Level_zordering.dat MISMIP3D_Z-ordering
#python ../PineIslandGlacier/value_plot.py Level_reordering.dat MISMIP3D_Z-ordering+Level-reordering

#python ../PineIslandGlacier/value_plot.py Level_row.dat MISMIP3D_Row-major
#python ../PineIslandGlacier/value_plot.py Level_row_levelreordering.dat MISMIP3D_Row-major+Level-reordering
#python ../PineIslandGlacier/value_plot.py Level_box.dat MISMIP3D_Row-major
#python ../PineIslandGlacier/value_plot.py Level_box_levelreordering.dat MISMIP3D_Row-major+Box+Level-reordering
#python ../PineIslandGlacier/value_plot.py Level_row_zordering.dat MISMIP3D_Z-ordering
#python ../PineIslandGlacier/value_plot.py Level_row_zordering_levelreordering.dat MISMIP3D_Z-ordering+Level-reordering
python ../PineIslandGlacier/value_plot.py Level_box_zordering.dat MISMIP3D_Z-ordering
python ../PineIslandGlacier/value_plot.py Level_box_zordering_levelreordering.dat MISMIP3D_Z-ordering+level-reordering

cd ../Greenland
echo Greenland
#../../code/filetools/stats2d.Linux.64.g++.gfortran.DEBUG.ex plot.GIS.5km.l1l2.5lev.000001.2d.hdf5 918 1028 9.81

#python ../PineIslandGlacier/value_plot.py Level_raw.dat Greenland_Row-major 
#python ../PineIslandGlacier/value_plot.py Level_boxlevel.dat Greenland_Row-major+Level-reordering
#python ../PineIslandGlacier/value_plot.py Level_zordering.dat Greenland_Z-ordering
#python ../PineIslandGlacier/value_plot.py Level_reordering.dat Greenland_Z-ordering+Level-reordering

#python ../PineIslandGlacier/value_plot.py Level_row.dat Greenland_Row-major
#python ../PineIslandGlacier/value_plot.py Level_row_levelreordering.dat Greenland_Row-major+Level-reordering
#python ../PineIslandGlacier/value_plot.py Level_box.dat Greenland_Row-major
#python ../PineIslandGlacier/value_plot.py Level_box_levelreordering.dat Greenland_Row-major+Box+Level-reordering
#python ../PineIslandGlacier/value_plot.py Level_row_zordering.dat Greenland_Z-ordering
#python ../PineIslandGlacier/value_plot.py Level_row_zordering_levelreordering.dat Greenland_Z-ordering+Level-reordering
python ../PineIslandGlacier/value_plot.py Level_box_zordering.dat Greenland_Z-ordering
python ../PineIslandGlacier/value_plot.py Level_box_zordering_levelreordering.dat Greenland_Z-ordering+level-reordering

