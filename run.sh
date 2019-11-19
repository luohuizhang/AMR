cd /home/luo/Chombo/BISICLES/examples/PineIslandGlacier
gcc test.c -o test
gcc linear.c -o linear
gcc quadratic.c -o quadratic
gcc interpolate.c -o interpolate
gcc interpolate_linear.c -o interpolate_linear
gcc interpolate_quadratic.c -o interpolate_quadratic

echo PineIslandGlacier
../PineIslandGlacier/test
../PineIslandGlacier/linear
../PineIslandGlacier/quadratic
../PineIslandGlacier/interpolate
../PineIslandGlacier/interpolate_linear
../PineIslandGlacier/interpolate_quadratic
cd ../MISMIP3D/ 

echo MISMIP3D
../PineIslandGlacier/test

../PineIslandGlacier/linear
../PineIslandGlacier/quadratic
../PineIslandGlacier/interpolate
../PineIslandGlacier/interpolate_linear
../PineIslandGlacier/interpolate_quadratic

cd ../Greenland

echo Greenland
../PineIslandGlacier/test

../PineIslandGlacier/linear
../PineIslandGlacier/quadratic
../PineIslandGlacier/interpolate
../PineIslandGlacier/interpolate_linear
../PineIslandGlacier/interpolate_quadratic
