#List="Level_0.dat Level_1.dat Level_2.dat Level_3.dat Level_4.dat new_delta_0_1  new_delta_1_2  new_delta_2_3  new_delta_3_4 new_delta_0_1_2 new_delta_1_2_3 new_delta_2_3_4 new_delta_0_1_2_3 new_delta_1_2_3_4"
#List="Level_all.dat Level_boxlevel.dat Level_raw.dat Level_row_levelreordering.dat Level_zordering_fitting.dat Level_reordering.dat"
#List="Level_row.dat Level_row_levelreordering.dat Level_box.dat Level_box_levelreordering.dat Level_row_zordering.dat Level_row_zordering_levelreordering.dat Level_box_zordering.dat Level_box_zordering_levelreordering.dat"
#List="Level_box.dat Level_row_levelreordering.dat Level_row_zordering.dat Level_row_zordering_levelreordering.dat"

rm result.txt
declare -i n=18
# Index of output file
declare -i j

# Main loop for batch execution
for ((j=0;j<$n;j=$j+1))
do

#List="Level_box_$j.dat  Level_box_levelreordering_$j.dat Level_box_zordering_$j.dat Level_box_zordering_levelreordering_$j.dat"

List="Level_box_zordering_$j.dat delta_0_1.dat_$j  delta_1_2.dat_$j  delta_2_3.dat_$j  delta_3_4.dat_$j delta_0_1_2.dat_$j delta_1_2_3.dat_$j delta_2_3_4.dat_$j"
maxV=`python ../PineIslandGlacier/findmax1.py Level_box_$j.dat`
#echo $maxV

maxV=$( echo $maxV | awk '{printf("%.15f\n", $1)}')
ratio=0.0001
err=$( echo "$ratio*$maxV " |bc )
toobig=$(echo "$err > 10000"|bc )
#echo "$err > 10000"|bc
if [ $toobig -gt 0 ];
then
err=100
fi

echo $err
set -- $List
for i
do
#    echo $err

echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
echo $i
echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"


	size='0'
size=$(( $size+ $(stat -c%s $i)/8 ))
	echo $size 
	/home/luo/ZFP/zfp/bin/zfp -a $err -s -d -1 $size -i $i -z $i.zfp
	echo $(stat -c%s $i)/$(stat -c%s $i.zfp) |bc -l>>result.txt 

	done

	set -- $List
	err_sz=$( echo "0.1*$err " |bc )
	sed -i "66s/.*/absErrBound =$err/" /home/luo/ZFP/SZ/sz.config
	for i
	do
#    echo $err

	echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
	echo $i
	echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"


	size='0'
size=$(( $size+ $(stat -c%s $i)/8 ))
	echo $size 
	/home/luo/ZFP/SZ/bin/testdouble_compress /home/luo/ZFP/SZ/sz.config  $i $size
	echo $(stat -c%s $i)/$(stat -c%s $i.sz) |bc -l>>result.txt

	done


	done
