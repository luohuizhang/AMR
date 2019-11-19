cd /home/luo/Chombo/BISICLES/examples/PineIslandGlacier
echo PineIslandGlacier
python ../PineIslandGlacier/CR_RMSE_SZ.py
python ../PineIslandGlacier/CR_RMSE_iterater.py
cd ../MISMIP3D/ 
echo MISMIP3D

python ../PineIslandGlacier/CR_RMSE_SZ.py
python ../PineIslandGlacier/CR_RMSE_iterater.py
cd ../Greenland
echo Greenland
python ../PineIslandGlacier/CR_RMSE_SZ.py
python ../PineIslandGlacier/CR_RMSE_iterater.py
