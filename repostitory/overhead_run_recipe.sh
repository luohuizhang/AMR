
cd ../repostitory/
sed -i "7s/.*/#define Level 5/" ../repostitory/overhead_recipe.c
make -f Makefile


echo PineIslandGlacier 
cd ../PineIslandGlacier
 ../repostitory/overhead_recipe




cd ../repostitory/
sed -i "7s/.*/#define Level 9/" ../repostitory/overhead_recipe.c
make -f Makefile


echo MISMIP3D
cd ../MISMIP3D
 ../repostitory/overhead_recipe 




cd ../repostitory/
sed -i "7s/.*/#define Level 6/" ../repostitory/overhead_recipe.c
make -f Makefile

echo Greenland
cd ../Greenland
 ../repostitory/overhead_recipe 
