cd /home/luo/Chombo/BISICLES/examples/PineIslandGlacier
echo PineIslandGlacier
../PineIslandGlacier/compress.sh
cd ../MISMIP3D/ 
echo MISMIP3D
../PineIslandGlacier/compress.sh

cd ../Greenland
echo Greenland
../PineIslandGlacier/compress.sh
