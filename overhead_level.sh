cd /home/luo/Chombo/BISICLES/examples/PineIslandGlacier
echo PineIslandGlacier
rm level_overhead.txt
i="2";
while [ $i -lt 6 ]
do
../../code/filetools/stats2d.Linux.64.g++.gfortran.DEBUG.ex plot.pigv5.1km.l1l2.$(( $i-1 ))lev.000000.2d.hdf5 918 1028 9.81
sed -i "7s/.*/#define Level $i/" overhead_reordering.c 
make -f Makefile
 ../PineIslandGlacier/overhead_reordering >>level_overhead.txt
echo $i
i=$[$i+1]
done

i="6";
while [ $i -lt 10 ]
do
../../code/filetools/stats2d.Linux.64.g++.gfortran.DEBUG.ex error_plot.pigv5.1km.l1l2.$(( $i-1 ))lev.000000.2d.hdf5 918 1028 9.81
sed -i "7s/.*/#define Level $i/" overhead_reordering.c 
make -f Makefile
 ../PineIslandGlacier/overhead_reordering >>level_overhead.txt
echo $i
i=$[$i+1]
done
