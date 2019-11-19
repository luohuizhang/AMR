cd /home/luo/Chombo/BISICLES/examples/PineIslandGlacier
echo PineIslandGlacier
../PineIslandGlacier/compress_index.sh
cd ../MISMIP3D/ 
echo MISMIP3D
../PineIslandGlacier/compress_index.sh

cd ../Greenland
echo Greenland
../PineIslandGlacier/compress_index.sh
