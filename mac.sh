
cd /home/luo/Chombo/BISICLES/examples/PineIslandGlacier
echo PineIslandGlacier

rm mac.txt
declare -i n=18
# Index of output file
declare -i j

# Main loop for batch execution
for ((j=0;j<$n;j=$j+1))
do

#List="Level_box_$j.dat  Level_box_levelreordering_$j.dat Level_box_zordering_$j.dat Level_box_zordering_levelreordering_$j.dat"
List="Level_box_zordering_$j.dat Level_box_zordering_levelreordering_$j.dat"


set -- $List
for i
do
#    echo $err

echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
echo $i
echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"

python ../repostitory/value_mac.py $i>>mac.txt

done


done
cd ../MISMIP3D/ 
echo MISMIP3D

rm mac.txt
declare -i n=18
# Index of output file
declare -i j

# Main loop for batch execution
for ((j=0;j<$n;j=$j+1))
do

#List="Level_box_$j.dat  Level_box_levelreordering_$j.dat Level_box_zordering_$j.dat Level_box_zordering_levelreordering_$j.dat"
List="Level_box_zordering_$j.dat Level_box_zordering_levelreordering_$j.dat"


set -- $List
for i
do
#    echo $err

echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
echo $i
echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"

python ../repostitory/value_mac.py $i>>mac.txt

done


done



cd ../Greenland
echo Greenland
rm mac.txt
declare -i n=18
# Index of output file
declare -i j

# Main loop for batch execution
for ((j=0;j<$n;j=$j+1))
do

#List="Level_box_$j.dat  Level_box_levelreordering_$j.dat Level_box_zordering_$j.dat Level_box_zordering_levelreordering_$j.dat"
List="Level_box_zordering_$j.dat Level_box_zordering_levelreordering_$j.dat"


set -- $List
for i
do
#    echo $err

echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
echo $i
echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"

python ../repostitory/value_mac.py $i>>mac.txt

done


done
