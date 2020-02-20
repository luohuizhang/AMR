GFORTRAN    = gfortran -Wall
CC          = gcc -O3
MPI_FORTRAN = mpif90 -Wall
MPI_CC      = mpicc 
LD = -lm

.SUFFIXES : .o .c

all: overhead_reordering overhead_level reordering access_number access_queries  distance interpolate 

overhead_reordering : overhead_reordering.o
	$(CC) $(LD) -o $@ overhead_reordering.o -L /home/luo/ZFP/zfp/lib/ -lzfp -L /home/luo/ZFP/SZ/lib -lSZ  -lzstd -lzlib -lm -lgsl -lgslcblas 

overhead_reordering.o : overhead_reordering.c 
	$(CC) -c $(*F).c -I /home/luo/ZFP/zfp/include -I/home/luo/ZFP/SZ/include

overhead_level : overhead_level.o
	$(CC) $(LD) -o $@ overhead_level.o -L /home/luo/ZFP/zfp/lib/ -lzfp -L /home/luo/ZFP/SZ/lib -lSZ  -lzstd -lzlib -lm -lgsl -lgslcblas 

overhead_level.o : overhead_level.c 
	$(CC) -c $(*F).c -I /home/luo/ZFP/zfp/include -I/home/luo/ZFP/SZ/include

reordering : reordering.o
	$(CC) $(LD) -o $@ reordering.o -lgsl -lgslcblas 
reordering.o : reordering.c 
	$(CC) -c $(*F).c -I /home/luo/ZFP/zfp/include -I/home/luo/ZFP/SZ/include


access_number: access_number.o
	$(CC) $(LD) -o $@ access_number.o -lgsl -lgslcblas 
access_number.o : access_number.c 
access_queries: access_queries.o
	$(CC) $(LD) -o $@ access_queries.o -lgsl -lgslcblas 
access_queries.o : access_queries.c 

distance: distance.o
	$(CC) $(LD) -o $@ distance.o -lgsl -lgslcblas -lm 
distance.o : distance.c 
interpolate: interpolate.o
	$(CC) $(LD) -o $@ interpolate.o -lgsl -lgslcblas 
distance.o : interpolate.c 

clean : 
	/bin/rm -f *.o  overhead_reordering overhead_level reordering access_number access_queries  distance interpolate 
