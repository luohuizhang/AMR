rm result_largerdataset.txt

cd ../repostitory/
sed -i "7s/.*/#define Level 5/" ../repostitory/reordering.c
sed -i "7s/.*/#define Level 5/" ../repostitory/reordering_hilbert.c
make -f Makefile
cd ../PineIslandGlacier
echo PineIslandGlacier
../../code/filetools/stats_all182d.Linux.64.g++.gfortran.DEBUG.ex plot.pigv5.1km.l1l2.4lev.005138.2d.hdf5 918 1028 9.81
../repostitory/reordering
../repostitory/reordering_hilbert

cd ../PineIslandGlacier
echo PineIslandGlacier
../repostitory/compress_largerdataset.sh

cd ../repostitory/
sed -i "7s/.*/#define Level 6/" ../repostitory/reordering.c
sed -i "7s/.*/#define Level 6/" ../repostitory/reordering_hilbert.c
make -f Makefile
cd ../PineIslandGlacier
echo PineIslandGlacier
../../code/filetools/stats_all182d.Linux.64.g++.gfortran.DEBUG.ex error_plot.pigv5.1km.l1l2.5lev.000000.2d.hdf5 918 1028 9.81
../repostitory/reordering
../repostitory/reordering_hilbert

cd ../PineIslandGlacier
echo PineIslandGlacier
../repostitory/compress_largerdataset.sh

cd ../repostitory/
sed -i "7s/.*/#define Level 9/" ../repostitory/reordering.c
sed -i "7s/.*/#define Level 9/" ../repostitory/reordering_hilbert.c
make -f Makefile
cd ../PineIslandGlacier
echo PineIslandGlacier
../../code/filetools/stats_all182d.Linux.64.g++.gfortran.DEBUG.ex error_plot.pigv5.1km.l1l2.8lev.000000.2d.hdf5 918 1028 9.81
../repostitory/reordering
../repostitory/reordering_hilbert

cd ../PineIslandGlacier
echo PineIslandGlacier
../repostitory/compress_largerdataset.sh
cd ../repostitory/
python CR_largerdataset_plot_P.py
