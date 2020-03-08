rm CR_RMSE_MaxE.txt
cd /home/luo/Chombo/BISICLES/examples/PineIslandGlacier

echo PineIslandGlacier
python ../repostitory/CR_RMSE.py
cd ../MISMIP3D/ 
echo MISMIP3D

python ../repostitory/CR_RMSE.py
cd ../Greenland
echo Greenland
python ../repostitory/CR_RMSE.py
