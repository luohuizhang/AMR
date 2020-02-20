
cd ../repostitory/
sed -i "7s/.*/#define Level 5/" ../repostitory/overhead_reordering.c
make -f Makefile


echo PineIslandGlacier 
 ../repostitory/overhead_reordering  ../PineIslandGlacier/datapoint_0




sed -i "7s/.*/#define Level 9/" ../repostitory/overhead_reordering.c
make -f Makefile


echo MISMIP3D
 ../repostitory/overhead_reordering ../MISMIP3D/datapoint_0




sed -i "7s/.*/#define Level 6/" ../repostitory/overhead_reordering.c
make -f Makefile

echo Greenland
 ../repostitory/overhead_reordering ../Greenland/datapoint_0
