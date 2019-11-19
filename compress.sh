List="Level_0.dat Level_1.dat Level_2.dat Level_3.dat Level_4.dat new_delta_0_1  new_delta_1_2  new_delta_2_3  new_delta_3_4 new_delta_0_1_2 new_delta_1_2_3 new_delta_2_3_4 new_delta_0_1_2_3 new_delta_1_2_3_4"
#List="Level_0.dat Level_1.dat Level_2.dat Level_3.dat Level_4.dat delta_0_1  delta_1_2  delta_2_3  delta_3_4 delta_0_1_2 delta_1_2_3 delta_2_3_4 delta_0_1_2_3 delta_1_2_3_4"
#List="Level_all.dat Level_boxlevel.dat Level_raw.dat Level_row_levelreordering.dat Level_zordering_fitting.dat Level_reordering.dat"
#List="Level_row.dat Level_row_levelreordering.dat Level_box.dat Level_box_levelreordering.dat Level_row_zordering.dat Level_row_zordering_levelreordering.dat Level_box_zordering.dat Level_box_zordering_levelreordering.dat"
#List="Level_box.dat Level_row_levelreordering.dat Level_row_zordering.dat Level_row_zordering_levelreordering.dat"
#List="Level_box.dat  Level_box_levelreordering.dat Level_box_zordering.dat Level_box_zordering_levelreordering.dat"
maxV=`python ../PineIslandGlacier/findmax.py`
#echo $maxV
ratio=0.0001
err=$( echo "$ratio*$maxV " |bc )
echo $err
rm result.txt
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


