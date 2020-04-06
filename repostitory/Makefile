GFORTRAN    = gfortran -Wall
CC          = gcc -O3
#CC          = gcc -g
MPI_FORTRAN = mpif90 -Wall
MPI_CC      = mpicc 
LD = -lm

.SUFFIXES : .o .c

all: overhead_reordering overhead_level overhead_level_H reordering access_number access_queries  distance overhead_all overhead_recipe overhead_recipe_H reordering_hilbert reordering_gilbert 2Dcompression 

overhead_reordering : overhead_reordering.o
	$(CC) $(LD) -o $@ overhead_reordering.o -L /home/luo/ZFP/zfp/lib/ -lzfp  -lSZ  -lzstd -lzlib -lm -lgsl -lgslcblas 

overhead_reordering.o : overhead_reordering.c 
	$(CC) -c $(*F).c -I /home/luo/ZFP/zfp/include 

overhead_level : overhead_level.o
	$(CC) $(LD) -o $@ overhead_level.o -L /home/luo/ZFP/zfp/lib/ -lzfp  -lSZ  -lzstd -lzlib -lm -lgsl -lgslcblas 

overhead_level.o : overhead_level.c 
	$(CC) -c $(*F).c -I /home/luo/ZFP/zfp/include 

overhead_level_H : overhead_level_H.o
	$(CC) $(LD) -o $@ overhead_level_H.o -L /home/luo/ZFP/zfp/lib/ -lzfp  -lSZ  -lzstd -lzlib -lm -lgsl -lgslcblas 

overhead_level_H.o : overhead_level_H.c 
	$(CC) -c $(*F).c -I /home/luo/ZFP/zfp/include 
reordering : reordering.o
	$(CC) $(LD) -o $@ reordering.o -lgsl -lgslcblas 
reordering.o : reordering.c 
	$(CC) -c $(*F).c -I /home/luo/ZFP/zfp/include 
reordering_hilbert : reordering_hilbert.o
	$(CC) $(LD) -o $@ reordering_hilbert.o -lgsl -lgslcblas 
reordering_hilbert.o : reordering_hilbert.c 
	$(CC) -c $(*F).c -I /home/luo/ZFP/zfp/include 
reordering_gilbert : reordering_gilbert.o
	$(CC) $(LD) -o $@ reordering_gilbert.o -lgsl -lgslcblas 
reordering_gilbert.o : reordering_gilbert.c 
	$(CC) -c $(*F).c -I /home/luo/ZFP/zfp/include 
overhead_all : overhead_all.o
	$(CC) $(LD) -o $@ overhead_all.o -L /home/luo/ZFP/zfp/lib/ -lzfp -lSZ  -lzstd -lzlib -lm -lgsl -lgslcblas  
overhead_all.o : overhead_all.c 
	$(CC) -c $(*F).c -I /home/luo/ZFP/zfp/include 

overhead_recipe : overhead_recipe.o
	$(CC) $(LD) -o $@ overhead_recipe.o -L /home/luo/ZFP/zfp/lib/ -lzfp -lSZ  -lzstd -lzlib -lm -lgsl -lgslcblas  
overhead_recipe.o : overhead_recipe.c 
	$(CC) -c $(*F).c -I /home/luo/ZFP/zfp/include 

2Dcompression : 2Dcompression.o
	$(CC) $(LD) -o $@ 2Dcompression.o -L /home/luo/ZFP/zfp/lib/ -lzfp -lSZ  -lzstd -lzlib -lm -lgsl -lgslcblas  
2Dcompression.o : 2Dcompression.c 
	$(CC) -c $(*F).c -I /home/luo/ZFP/zfp/include 
overhead_recipe_H : overhead_recipe_H.o
	$(CC) $(LD) -o $@ overhead_recipe_H.o -L /home/luo/ZFP/zfp/lib/ -lzfp -lSZ  -lzstd -lzlib -lm -lgsl -lgslcblas  
overhead_recipe_H.o : overhead_recipe_H.c 
	$(CC) -c $(*F).c -I /home/luo/ZFP/zfp/include 

access_number: access_number.o
	$(CC) $(LD) -o $@ access_number.o -lgsl -lgslcblas 
access_number.o : access_number.c 
access_queries: access_queries.o
	$(CC) $(LD) -o $@ access_queries.o -lgsl -lgslcblas -lm
access_queries.o : access_queries.c 

distance: distance.o
	$(CC) $(LD) -o $@ distance.o -lgsl -lgslcblas -lm
distance.o : distance.c 

clean : 
	/bin/rm -f *.o  overhead_reordering overhead_level reordering access_number access_queries  distance overhead_all overhead_recipe 
