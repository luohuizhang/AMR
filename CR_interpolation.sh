cd /home/luo/Chombo/BISICLES/examples/PineIslandGlacier
echo PineIslandGlacier
../PineIslandGlacier/compress_interpolation.sh

cd ../MISMIP3D/ 
echo MISMIP3D

../PineIslandGlacier/compress_interpolation.sh

cd ../Greenland
echo Greenland
../PineIslandGlacier/compress_interpolation.sh
