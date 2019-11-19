#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "zfp.h"
#include "sz.h"
#define Level 5 

int ** mapping;
int Part1By1(int x);
int EncodeMorton2(int x, int y)
{
	return (Part1By1(y) << 1) + Part1By1(x);
}








// "Insert" a 0 bit after each of the 16 low bits of x
int Part1By1(int x)
{
	x &= 0x0000ffff;                  // x = ---- ---- ---- ---- fedc ba98 7654 3210
	x = (x ^ (x <<  8)) & 0x00ff00ff; // x = ---- ---- fedc ba98 ---- ---- 7654 3210
	x = (x ^ (x <<  4)) & 0x0f0f0f0f; // x = ---- fedc ---- ba98 ---- 7654 ---- 3210
	x = (x ^ (x <<  2)) & 0x33333333; // x = --fe --dc --ba --98 --76 --54 --32 --10
	x = (x ^ (x <<  1)) & 0x55555555; // x = -f-e -d-c -b-a -9-8 -7-6 -5-4 -3-2 -1-0
	return x;
}




// Inverse of Part1By1 - "delete" all odd-indexed bits
int Compact1By1(int x)
{
	x &= 0x55555555;                  // x = -f-e -d-c -b-a -9-8 -7-6 -5-4 -3-2 -1-0
	x = (x ^ (x >>  1)) & 0x33333333; // x = --fe --dc --ba --98 --76 --54 --32 --10
	x = (x ^ (x >>  2)) & 0x0f0f0f0f; // x = ---- fedc ---- ba98 ---- 7654 ---- 3210
	x = (x ^ (x >>  4)) & 0x00ff00ff; // x = ---- ---- fedc ba98 ---- ---- 7654 3210
	x = (x ^ (x >>  8)) & 0x0000ffff; // x = ---- ---- ---- ---- fedc ba98 7654 3210
	return x;
}




int DecodeMorton2X(int code)
{
	return Compact1By1(code >> 0);
}

int DecodeMorton2Y(int code)
{
	return Compact1By1(code >> 1);
}



struct datapoint{
	int a,b;
	double val;
};

struct box{
	int x1,y1;
	int x2,y2;
};

struct node{
	int x,y;
	double val;
	int flag;
	struct node *fchild;
	struct node *next;
};


void PrintTree(struct node* p, double* fp, int flag)
{
	if (p==NULL) 
		return;
	if(flag==1)
		fp[0]= (*p).val;
	else
		(*p).val=fp[0];
	fp++;
	//	p->flag==1; 
	(*p).flag=1;
	//  printf("%d\n",p->flag);
	if (p->fchild!=NULL) 
	{ PrintTree(p->fchild,fp,flag); }
	if (p->next!=NULL)
	{ PrintTree(p->next,fp,flag); } 


}

int find_father(struct node *data, int size,int a, int b)
{

	int i;
	for(i=0;i<size;i++)
		if(data[i].x==a&&data[i].y==b)
			return i;
	printf("do not find (%d,%d)\n",a,b);
	return -1;
}

int find_father1(struct datapoint *data, int size,int a, int b)
{

	int i;
	for(i=0;i<size;i++)
		if(data[i].a==a&&data[i].b==b)
			return i;
	printf("do not find (%d,%d)\n",a,b);
	return -1;
}
int init_mapping(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{
	int i,j;
	for(i=Level-1;i>0;i--)
		for(j=0;j<cnt[i];j++)
		{


			int a=(int)data[i][j].a/2;

			int b=(int)data[i][j].b/2;
			mapping[i][j]=find_father1(data[i-1],cnt[i-1],a,b);
		}


}

	int
compress (double * array, int nx, double tolerance
	 )
{
	zfp_type type;     /* array scalar type */
	zfp_field* field;  /* array meta data */
	zfp_stream* zfp;   /* compressed stream */
	void* buffer;      /* storage for compressed stream */
	size_t bufsize;    /* byte size of compressed buffer */
	bitstream * stream; /* bit stream to write to or read from */
	size_t zfpsize;    /* byte size of compressed stream */

	/* allocate meta data for the 3D array a[nz][ny][nx] */
	type = zfp_type_double;
	field = zfp_field_1d (array, type, nx);

	/* allocate meta data for a compressed stream */
	zfp = zfp_stream_open (NULL);

	/* set compression mode and parameters via one of three functions */
	/*  zfp_stream_set_rate(zfp, rate, type, 3, 0); */
	/* A_precision = zfp_stream_set_precision(zfp, precision, type);*/
	zfp_stream_set_accuracy (zfp, tolerance);


	/* allocate buffer for compressed data */
	bufsize = zfp_stream_maximum_size (zfp, field);
	buffer = malloc (bufsize);
	assert (buffer);
	/* associate bit stream with allocated buffer */
	stream = stream_open (buffer, bufsize);
	zfp_stream_set_bit_stream (zfp, stream);
	zfp_stream_rewind (zfp);

	/* compress array and output compressed stream */
	//zfpsize = zfp_compress (zfp, field);
	zfpsize = zfp_compress(zfp, field);
	if (!zfpsize) {
		fprintf(stderr, "compression failed\n");
	}
	else{
		FILE *fp=fopen("zfp.b","w");

		fwrite(buffer, 1, zfpsize, fp);
		fclose(fp);
	}
	assert (zfpsize);
	zfp_field_free (field);
	zfp_stream_close (zfp);
	stream_close (stream);

	free( buffer);

	return zfpsize;
}




	int
decompress (double * array, int nx, double tolerance)
{
	zfp_type type;     /* array scalar type */
	zfp_field* field;  /* array meta data */
	zfp_stream* zfp;   /* compressed stream */
	bitstream * stream; /* bit stream to write to or read from */
	size_t zfpsize;    /* byte size of compressed stream */

	void* buffer;      /* storage for compressed stream */
	size_t bufsize;    /* byte size of compressed buffer */

	/* allocate meta data for the 3D array a[nz][ny][nx] */
	type = zfp_type_double;
	field = zfp_field_1d (array, type, nx);

	/* allocate meta data for a compressed stream */
	zfp = zfp_stream_open (NULL);
	zfp_stream_set_accuracy (zfp, tolerance);

	/* associate bit stream with allocated buffer */
	//	stream = stream_open (array_compressed, array_size_compressed);
	//	zfp_stream_set_bit_stream (zfp, stream);
	//	zfp_stream_rewind (zfp);

	//allocate buffer for compressed data 
	bufsize = zfp_stream_maximum_size (zfp, field);
	buffer = malloc (bufsize);
	assert (buffer);
	stream = stream_open (buffer, bufsize);
	zfp_stream_set_bit_stream (zfp, stream);
	zfp_stream_rewind (zfp);


	FILE *fp=fopen("zfp.b","r");
	//fread(array_compressed, 1, array_size_compressed, fp);
	zfpsize = fread(buffer, 1, bufsize, fp);
	fclose(fp);

	if (!zfp_decompress(zfp, field)) {
		fprintf(stderr, "decompression failed\n");
	}
	//assert (zfp_decompress(zfp, field));

	/* clean up */
	zfp_field_free (field);
	zfp_stream_close (zfp);
	stream_close (stream);
	free(buffer);
	return 0;
}

void leveldata_box_zordering_ZFP_compress(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{
	clock_t start_t, end_t; double total_t;

	start_t = clock();
	int i,j,k;

	struct node** trees;
	trees=malloc(Level*sizeof(* trees));
	for(i=0;i<Level;i++)
		trees[i]=malloc(cnt[i]*sizeof(struct node));
	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	double *dataArray=malloc(datasize*sizeof(double));
	int offset=0;

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{

			trees[i][j].flag=0;

		}
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Zordering_initial: %lf\n", total_t  );
	clock_t start_t1=start_t;
	start_t=clock();
	for(i=0;i<Level;i++)
	{ 
		offset=0;
		for(j=0;j<box_cnt[i];j++)
		{
			int a=boxes[i][j].x2-boxes[i][j].x1;
			int b=boxes[i][j].y2-boxes[i][j].y1;
			int z_size= EncodeMorton2(a,b)+1;
			//printf("%d,%d,%d\n",a,b,z_size);
			int *z_index=malloc(z_size*sizeof(int));
			//memset (z_index,-1,z_size*sizeof(int));
			for(k=0;k<z_size;k++){
				z_index[k]=-1;
			}

			int box_size=(a+1)*(b+1);

			for(int m=0;m<=b;m++)
				for(int l=0;l<=a;l++)
				{
					z_index[EncodeMorton2(l,m)]=l+m*(a+1);
				}
			int *amt_index=malloc(box_size*sizeof(int));
			int tr=0;
			for(k=0;k<z_size;k++){
				if(z_index[k]!=-1)
					amt_index[tr++]=z_index[k];
			}
			if(tr!=box_size){
				printf("tr!=box_size, %d, %d\n",tr,box_size);
				for (k=0;k<box_size;k++)
					printf("%d ",amt_index[k]);
			}
			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+amt_index[k]].a;
				trees[i][offset+k].y=data[i][offset+amt_index[k]].b;
				trees[i][offset+k].val=data[i][offset+amt_index[k]].val;
				trees[i][offset+k].flag=1;
				trees[i][offset+k].fchild=NULL;
				trees[i][offset+k].next=NULL;
			}

			offset+=box_size;
			free(z_index);
			free(amt_index);
		}

	}
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Zordering_main: %lf\n", total_t  );
	start_t=clock();

	int offset1=0;
	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			dataArray[offset1]=trees[i][j].val;
			offset1++;
		}

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			if(trees[i][j].flag==0)                 
				printf("Not visit %d,%d\n",i,j);

		}


	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Zordering_travel: %lf\n", total_t  );


	size_t compr_size = compress (dataArray, datasize, 5);

	end_t = clock();
	total_t = (double)(end_t - start_t1) / CLOCKS_PER_SEC;
	printf("ZFP compress: %lf\n", total_t  );

	free(dataArray);
}

void leveldata_box_zordering_ZFP_decompress(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{
	clock_t start_t, end_t; double total_t;

	start_t = clock();
	int i,j,k;

	struct node** trees;
	trees=malloc(Level*sizeof(* trees));
	for(i=0;i<Level;i++)
		trees[i]=malloc(cnt[i]*sizeof(struct node));
	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	int offset=0;

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{

			trees[i][j].flag=0;

		}
	for(i=0;i<Level;i++)
	{ 
		offset=0;
		for(j=0;j<box_cnt[i];j++)
		{
			int a=boxes[i][j].x2-boxes[i][j].x1;
			int b=boxes[i][j].y2-boxes[i][j].y1;
			int z_size= EncodeMorton2(a,b)+1;
			//printf("%d,%d,%d\n",a,b,z_size);
			int *z_index=malloc(z_size*sizeof(int));
			//memset (z_index,-1,z_size*sizeof(int));
			for(k=0;k<z_size;k++){
				z_index[k]=-1;
			}

			int box_size=(a+1)*(b+1);

			for(int m=0;m<=b;m++)
				for(int l=0;l<=a;l++)
				{
					z_index[EncodeMorton2(l,m)]=l+m*(a+1);
				}
			int *amt_index=malloc(box_size*sizeof(int));
			int tr=0;
			for(k=0;k<z_size;k++){
				if(z_index[k]!=-1)
					amt_index[tr++]=z_index[k];
			}
			if(tr!=box_size){
				printf("tr!=box_size, %d, %d\n",tr,box_size);
				for (k=0;k<box_size;k++)
					printf("%d ",amt_index[k]);
			}
			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+amt_index[k]].a;
				trees[i][offset+k].y=data[i][offset+amt_index[k]].b;
				trees[i][offset+k].val=data[i][offset+amt_index[k]].val;
			}

			offset+=box_size;
			free(z_index);
			free(amt_index);
		}

	}





	double * array_decompressed=malloc(datasize*sizeof(double));


	decompress (array_decompressed, datasize, 5);

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("ZFP decompress: %lf\n", total_t  );


	int offset1=0;
	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			trees[i][j].val=array_decompressed[offset1];
			offset1++;
		}

	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);

	free(array_decompressed);
}

void leveldata_box_zordering_SZ_compress(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{
	clock_t start_t, end_t; double total_t;

	start_t = clock();
	int i,j,k;

	struct node** trees;
	trees=malloc(Level*sizeof(* trees));
	for(i=0;i<Level;i++)
		trees[i]=malloc(cnt[i]*sizeof(struct node));
	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	double *dataArray=malloc(datasize*sizeof(double));
	int offset=0;

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{

			trees[i][j].flag=0;

		}
	for(i=0;i<Level;i++)
	{ 
		offset=0;
		for(j=0;j<box_cnt[i];j++)
		{
			int a=boxes[i][j].x2-boxes[i][j].x1;
			int b=boxes[i][j].y2-boxes[i][j].y1;
			int z_size= EncodeMorton2(a,b)+1;
			//printf("%d,%d,%d\n",a,b,z_size);
			int *z_index=malloc(z_size*sizeof(int));
			//memset (z_index,-1,z_size*sizeof(int));
			for(k=0;k<z_size;k++){
				z_index[k]=-1;
			}

			int box_size=(a+1)*(b+1);

			for(int m=0;m<=b;m++)
				for(int l=0;l<=a;l++)
				{
					z_index[EncodeMorton2(l,m)]=l+m*(a+1);
				}
			int *amt_index=malloc(box_size*sizeof(int));
			int tr=0;
			for(k=0;k<z_size;k++){
				if(z_index[k]!=-1)
					amt_index[tr++]=z_index[k];
			}
			if(tr!=box_size){
				printf("tr!=box_size, %d, %d\n",tr,box_size);
				for (k=0;k<box_size;k++)
					printf("%d ",amt_index[k]);
			}
			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+amt_index[k]].a;
				trees[i][offset+k].y=data[i][offset+amt_index[k]].b;
				trees[i][offset+k].val=data[i][offset+amt_index[k]].val;
				trees[i][offset+k].flag=1;
				trees[i][offset+k].fchild=NULL;
				trees[i][offset+k].next=NULL;
			}

			offset+=box_size;
			free(z_index);
			free(amt_index);
		}

	}

	int offset1=0;
	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			//	fwrite(&trees[i][j].val,sizeof(double),1,fp);
			dataArray[offset1]=trees[i][j].val;
			offset1++;
		}

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			if(trees[i][j].flag==0)                 
				printf("Not visit %d,%d\n",i,j);

		}


	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);

	char *confFile = "/home/luo/ZFP/SZ/sz.config";
	size_t outSize;
	int r4 = 0, r3 = 0, r2 = 0, r5 = 0;
	SZ_Init(confFile);

	unsigned char *compressed = SZ_compress(SZ_DOUBLE, dataArray, &outSize, r5, r4, r3, r2 ,datasize);

	FILE *fp=fopen("sz.b","w");
	fwrite(compressed, 1, outSize, fp);
	fclose(fp);
	free(compressed); 
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("SZ compress: %lf\n", total_t  );

	free(dataArray);
}

void leveldata_box_zordering_SZ_decompress(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{
	clock_t start_t, end_t; double total_t;

	start_t = clock();
	int i,j,k;

	struct node** trees;
	trees=malloc(Level*sizeof(* trees));
	for(i=0;i<Level;i++)
		trees[i]=malloc(cnt[i]*sizeof(struct node));
	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	int offset=0;

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{

			trees[i][j].flag=0;

		}
	for(i=0;i<Level;i++)
	{ 
		offset=0;
		for(j=0;j<box_cnt[i];j++)
		{
			int a=boxes[i][j].x2-boxes[i][j].x1;
			int b=boxes[i][j].y2-boxes[i][j].y1;
			int z_size= EncodeMorton2(a,b)+1;
			//printf("%d,%d,%d\n",a,b,z_size);
			int *z_index=malloc(z_size*sizeof(int));
			//memset (z_index,-1,z_size*sizeof(int));
			for(k=0;k<z_size;k++){
				z_index[k]=-1;
			}

			int box_size=(a+1)*(b+1);

			for(int m=0;m<=b;m++)
				for(int l=0;l<=a;l++)
				{
					z_index[EncodeMorton2(l,m)]=l+m*(a+1);
				}
			int *amt_index=malloc(box_size*sizeof(int));
			int tr=0;
			for(k=0;k<z_size;k++){
				if(z_index[k]!=-1)
					amt_index[tr++]=z_index[k];
			}
			if(tr!=box_size){
				printf("tr!=box_size, %d, %d\n",tr,box_size);
				for (k=0;k<box_size;k++)
					printf("%d ",amt_index[k]);
			}
			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+amt_index[k]].a;
				trees[i][offset+k].y=data[i][offset+amt_index[k]].b;
			}

			offset+=box_size;
			free(z_index);
			free(amt_index);
		}

	}





	char *confFile = "/home/luo/ZFP/SZ/sz.config";
	size_t outSize;
	int r4 = 0, r3 = 0, r2 = 0, r5 = 0;
	SZ_Init(confFile);

	unsigned char *compressed1=malloc(datasize*sizeof(double));
	FILE *fp=fopen("sz.b","r");
	//fread(array_compressed, 1, array_size_compressed, fp);
	outSize=fread(compressed1, 1, outSize, fp);
	fclose(fp);



	double *decompressed = (double *)SZ_decompress(SZ_DOUBLE, compressed1, outSize,r5, r4, r3, r2, datasize);
	free(compressed1);
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("SZ decompress: %lf\n", total_t  );

	int offset1=0;
	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			//fwrite(&trees[i][j].val,sizeof(double),1,fp);
			trees[i][j].val=decompressed[offset1];
			offset1++;
		}

	free(decompressed);
	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);
}



void leveldata_box_zordering_level_ZFP_compress(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{
	clock_t start_t, end_t; double total_t;
	double total_t1=0;
	clock_t start_t1;
	start_t = clock();
	start_t1=start_t;
	int i,j,k;
	FILE *fp;
	struct node** trees;
	trees=malloc(Level*sizeof(* trees));
	for(i=0;i<Level;i++)
		trees[i]=malloc(cnt[i]*sizeof(struct node));
	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	double *dataArray=malloc(datasize*sizeof(double));

	int offset=0;

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{

			trees[i][j].flag=0;

		}

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Level_initial: %lf\n", total_t  );
	start_t=clock();



	for(i=0;i<Level;i++)
	{ 
		offset=0;
		for(j=0;j<box_cnt[i];j++)
		{
			int a=boxes[i][j].x2-boxes[i][j].x1;
			int b=boxes[i][j].y2-boxes[i][j].y1;
			int z_size= EncodeMorton2(a,b)+1;
			//printf("%d,%d,%d\n",a,b,z_size);
			int *z_index=malloc(z_size*sizeof(int));
			//memset (z_index,-1,z_size*sizeof(int));
			for(k=0;k<z_size;k++){
				z_index[k]=-1;
			}

			int box_size=(a+1)*(b+1);

			for(int m=0;m<=b;m++)
				for(int l=0;l<=a;l++)
				{
					z_index[EncodeMorton2(l,m)]=l+m*(a+1);
				}
			int *amt_index=malloc(box_size*sizeof(int));
			int tr=0;
			for(k=0;k<z_size;k++){
				if(z_index[k]!=-1)
					amt_index[tr++]=z_index[k];
			}
			if(tr!=box_size){
				printf("tr!=box_size, %d, %d\n",tr,box_size);
				for (k=0;k<box_size;k++)
					printf("%d ",amt_index[k]);
			}
			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+amt_index[k]].a;
				trees[i][offset+k].y=data[i][offset+amt_index[k]].b;
				trees[i][offset+k].val=data[i][offset+amt_index[k]].val;
				//	trees[i][offset+k].x=data[i][offset+k].a;
				//	trees[i][offset+k].y=data[i][offset+k].b;
				//	trees[i][offset+k].val=data[i][offset+k].val;
				trees[i][offset+k].flag=0;
				trees[i][offset+k].fchild=NULL;
				trees[i][offset+k].next=NULL;
			}

			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+amt_index[k]].a;
				trees[i][offset+k].y=data[i][offset+amt_index[k]].b;
				trees[i][offset+k].val=data[i][offset+amt_index[k]].val;
				//      trees[i][offset+k].x=data[i][offset+k].a;
				//      trees[i][offset+k].y=data[i][offset+k].b;
				//      trees[i][offset+k].val=data[i][offset+k].val;
				trees[i][offset+k].flag=0;
				trees[i][offset+k].fchild=NULL;
				trees[i][offset+k].next=NULL;
			}
			offset+=box_size;
			free(z_index);
			free(amt_index);
		}

	}

	end_t = clock();

	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

	printf("Level_main: %lf\n", total_t  );

	total_t1 = (double)(end_t - start_t1) / CLOCKS_PER_SEC;
	for(i=Level-1;i>0;i--)
		for(j=0;j<cnt[i];j++)
		{


			int a=(int)trees[i][j].x/2;

			int b=(int)trees[i][j].y/2;
			mapping[i][j]=find_father(trees[i-1],cnt[i-1],a,b);
		}

	start_t=clock();

	start_t1=start_t;

	for(i=Level-1;i>0;i--)
	{
		for(j=0;j<cnt[i];j++)
		{       
			int father_index=mapping[i][j];
			struct	node *p=trees[i-1][father_index].fchild;
			if (p==NULL)
				trees[i-1][father_index].fchild=&trees[i][j];
			else
			{
				while(p->next!=NULL)
					p=p->next;
				p->next=&trees[i][j];
			}




		}


	}
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Level_build: %lf\n", total_t  );
	start_t=clock();

	double *vp=dataArray;
	for(i=0;i<1;i++)
		for(j=0;j<cnt[i];j++)
		{
			struct  node *p=&trees[i][j];
			PrintTree(p,vp,1);

		}


	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			if(trees[i][j].flag==0)                      
				printf("Not visit %d,%d\n",i,j);

		}
	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Level_travel: %lf\n", total_t  );
	size_t compr_size = compress (dataArray, datasize, 5);

	end_t = clock();
	total_t1 += (double)(end_t - start_t1) / CLOCKS_PER_SEC;
	printf("Level ZFP compress: %lf\n", total_t  );
	free(dataArray);

}


void leveldata_box_zordering_level_ZFP_decompress(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{
	clock_t start_t, end_t; double total_t;

	start_t = clock();
	int i,j,k;
	FILE *fp;
	struct node** trees;
	trees=malloc(Level*sizeof(* trees));
	for(i=0;i<Level;i++)
		trees[i]=malloc(cnt[i]*sizeof(struct node));

	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];

	int offset=0;

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{

			trees[i][j].flag=0;

		}



	for(i=0;i<Level;i++)
	{ 
		offset=0;
		for(j=0;j<box_cnt[i];j++)
		{
			int a=boxes[i][j].x2-boxes[i][j].x1;
			int b=boxes[i][j].y2-boxes[i][j].y1;
			int z_size= EncodeMorton2(a,b)+1;
			//printf("%d,%d,%d\n",a,b,z_size);
			int *z_index=malloc(z_size*sizeof(int));
			//memset (z_index,-1,z_size*sizeof(int));
			for(k=0;k<z_size;k++){
				z_index[k]=-1;
			}

			int box_size=(a+1)*(b+1);

			for(int m=0;m<=b;m++)
				for(int l=0;l<=a;l++)
				{
					z_index[EncodeMorton2(l,m)]=l+m*(a+1);
				}
			int *amt_index=malloc(box_size*sizeof(int));
			int tr=0;
			for(k=0;k<z_size;k++){
				if(z_index[k]!=-1)
					amt_index[tr++]=z_index[k];
			}
			if(tr!=box_size){
				printf("tr!=box_size, %d, %d\n",tr,box_size);
				for (k=0;k<box_size;k++)
					printf("%d ",amt_index[k]);
			}
			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+amt_index[k]].a;
				trees[i][offset+k].y=data[i][offset+amt_index[k]].b;
				trees[i][offset+k].val=data[i][offset+amt_index[k]].val;
				//	trees[i][offset+k].x=data[i][offset+k].a;
				//	trees[i][offset+k].y=data[i][offset+k].b;
				//	trees[i][offset+k].val=data[i][offset+k].val;
				trees[i][offset+k].flag=0;
				trees[i][offset+k].fchild=NULL;
				trees[i][offset+k].next=NULL;
			}

			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+amt_index[k]].a;
				trees[i][offset+k].y=data[i][offset+amt_index[k]].b;
				trees[i][offset+k].val=data[i][offset+amt_index[k]].val;
				//      trees[i][offset+k].x=data[i][offset+k].a;
				//      trees[i][offset+k].y=data[i][offset+k].b;
				//      trees[i][offset+k].val=data[i][offset+k].val;
				trees[i][offset+k].flag=0;
				trees[i][offset+k].fchild=NULL;
				trees[i][offset+k].next=NULL;
			}
			offset+=box_size;
			free(z_index);
			free(amt_index);
		}

	}

	end_t = clock();

	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;


	for(i=Level-1;i>0;i--)
		for(j=0;j<cnt[i];j++)
		{


			int a=(int)trees[i][j].x/2;

			int b=(int)trees[i][j].y/2;
			mapping[i][j]=find_father(trees[i-1],cnt[i-1],a,b);
		}

	start_t=clock();


	for(i=Level-1;i>0;i--)
	{
		for(j=0;j<cnt[i];j++)
		{       
			int father_index=mapping[i][j];
			struct	node *p=trees[i-1][father_index].fchild;
			if (p==NULL)
				trees[i-1][father_index].fchild=&trees[i][j];
			else
			{
				while(p->next!=NULL)
					p=p->next;
				p->next=&trees[i][j];
			}




		}


	}


	double * array_decompressed=malloc(datasize*sizeof(double));


	decompress (array_decompressed, datasize, 5);

	double *vp=array_decompressed;
	for(i=0;i<1;i++)
		for(j=0;j<cnt[i];j++)
		{
			struct  node *p=&trees[i][j];
			PrintTree(p,vp,0);

		}




	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);
	free(array_decompressed);

	end_t = clock();
	total_t += (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Level ZFP decompress: %lf\n", total_t  );
}

void leveldata_box_zordering_level_SZ_compress(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{
	clock_t start_t, end_t; double total_t;

	start_t = clock();
	int i,j,k;
	FILE *fp;
	struct node** trees;
	trees=malloc(Level*sizeof(* trees));
	for(i=0;i<Level;i++)
		trees[i]=malloc(cnt[i]*sizeof(struct node));
	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	double *dataArray=malloc(datasize*sizeof(double));


	int offset=0;

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{

			trees[i][j].flag=0;

		}



	for(i=0;i<Level;i++)
	{ 
		offset=0;
		for(j=0;j<box_cnt[i];j++)
		{
			int a=boxes[i][j].x2-boxes[i][j].x1;
			int b=boxes[i][j].y2-boxes[i][j].y1;
			int z_size= EncodeMorton2(a,b)+1;
			//printf("%d,%d,%d\n",a,b,z_size);
			int *z_index=malloc(z_size*sizeof(int));
			//memset (z_index,-1,z_size*sizeof(int));
			for(k=0;k<z_size;k++){
				z_index[k]=-1;
			}

			int box_size=(a+1)*(b+1);

			for(int m=0;m<=b;m++)
				for(int l=0;l<=a;l++)
				{
					z_index[EncodeMorton2(l,m)]=l+m*(a+1);
				}
			int *amt_index=malloc(box_size*sizeof(int));
			int tr=0;
			for(k=0;k<z_size;k++){
				if(z_index[k]!=-1)
					amt_index[tr++]=z_index[k];
			}
			if(tr!=box_size){
				printf("tr!=box_size, %d, %d\n",tr,box_size);
				for (k=0;k<box_size;k++)
					printf("%d ",amt_index[k]);
			}
			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+amt_index[k]].a;
				trees[i][offset+k].y=data[i][offset+amt_index[k]].b;
				trees[i][offset+k].val=data[i][offset+amt_index[k]].val;
				//	trees[i][offset+k].x=data[i][offset+k].a;
				//	trees[i][offset+k].y=data[i][offset+k].b;
				//	trees[i][offset+k].val=data[i][offset+k].val;
				trees[i][offset+k].flag=0;
				trees[i][offset+k].fchild=NULL;
				trees[i][offset+k].next=NULL;
			}

			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+amt_index[k]].a;
				trees[i][offset+k].y=data[i][offset+amt_index[k]].b;
				trees[i][offset+k].val=data[i][offset+amt_index[k]].val;
				//      trees[i][offset+k].x=data[i][offset+k].a;
				//      trees[i][offset+k].y=data[i][offset+k].b;
				//      trees[i][offset+k].val=data[i][offset+k].val;
				trees[i][offset+k].flag=0;
				trees[i][offset+k].fchild=NULL;
				trees[i][offset+k].next=NULL;
			}
			offset+=box_size;
			free(z_index);
			free(amt_index);
		}

	}

	end_t = clock();

	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;


	for(i=Level-1;i>0;i--)
		for(j=0;j<cnt[i];j++)
		{


			int a=(int)trees[i][j].x/2;

			int b=(int)trees[i][j].y/2;
			mapping[i][j]=find_father(trees[i-1],cnt[i-1],a,b);
		}

	start_t=clock();


	for(i=Level-1;i>0;i--)
	{
		for(j=0;j<cnt[i];j++)
		{       
			int father_index=mapping[i][j];
			struct	node *p=trees[i-1][father_index].fchild;
			if (p==NULL)
				trees[i-1][father_index].fchild=&trees[i][j];
			else
			{
				while(p->next!=NULL)
					p=p->next;
				p->next=&trees[i][j];
			}




		}


	}
	double *vp=dataArray;
	for(i=0;i<1;i++)
		for(j=0;j<cnt[i];j++)
		{
			struct  node *p=&trees[i][j];
			PrintTree(p,vp,1);

		}


	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			if(trees[i][j].flag==0)                      
				printf("Not visit %d,%d\n",i,j);

		}
	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);


	char *confFile = "/home/luo/ZFP/SZ/sz.config";
	size_t outSize;
	int r4 = 0, r3 = 0, r2 = 0, r5 = 0;
	SZ_Init(confFile);

	unsigned char *compressed = SZ_compress(SZ_DOUBLE, dataArray, &outSize, r5, r4, r3, r2 ,datasize);

	fp=fopen("sz.b","w");
	fwrite(compressed, 1, outSize, fp);
	fclose(fp);
	free(compressed);
	end_t = clock();
	total_t += (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Level SZ compress: %lf\n", total_t  );

	free(dataArray);


}

void leveldata_box_zordering_level_SZ_decompress(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{
	clock_t start_t, end_t; double total_t;

	start_t = clock();
	int i,j,k;
	FILE *fp;
	struct node** trees;
	trees=malloc(Level*sizeof(* trees));
	for(i=0;i<Level;i++)
		trees[i]=malloc(cnt[i]*sizeof(struct node));
	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];


	int offset=0;

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{

			trees[i][j].flag=0;

		}



	for(i=0;i<Level;i++)
	{ 
		offset=0;
		for(j=0;j<box_cnt[i];j++)
		{
			int a=boxes[i][j].x2-boxes[i][j].x1;
			int b=boxes[i][j].y2-boxes[i][j].y1;
			int z_size= EncodeMorton2(a,b)+1;
			//printf("%d,%d,%d\n",a,b,z_size);
			int *z_index=malloc(z_size*sizeof(int));
			//memset (z_index,-1,z_size*sizeof(int));
			for(k=0;k<z_size;k++){
				z_index[k]=-1;
			}

			int box_size=(a+1)*(b+1);

			for(int m=0;m<=b;m++)
				for(int l=0;l<=a;l++)
				{
					z_index[EncodeMorton2(l,m)]=l+m*(a+1);
				}
			int *amt_index=malloc(box_size*sizeof(int));
			int tr=0;
			for(k=0;k<z_size;k++){
				if(z_index[k]!=-1)
					amt_index[tr++]=z_index[k];
			}
			if(tr!=box_size){
				printf("tr!=box_size, %d, %d\n",tr,box_size);
				for (k=0;k<box_size;k++)
					printf("%d ",amt_index[k]);
			}
			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+amt_index[k]].a;
				trees[i][offset+k].y=data[i][offset+amt_index[k]].b;
				trees[i][offset+k].val=data[i][offset+amt_index[k]].val;
				//	trees[i][offset+k].x=data[i][offset+k].a;
				//	trees[i][offset+k].y=data[i][offset+k].b;
				//	trees[i][offset+k].val=data[i][offset+k].val;
				trees[i][offset+k].flag=0;
				trees[i][offset+k].fchild=NULL;
				trees[i][offset+k].next=NULL;
			}

			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+amt_index[k]].a;
				trees[i][offset+k].y=data[i][offset+amt_index[k]].b;
				trees[i][offset+k].val=data[i][offset+amt_index[k]].val;
				//      trees[i][offset+k].x=data[i][offset+k].a;
				//      trees[i][offset+k].y=data[i][offset+k].b;
				//      trees[i][offset+k].val=data[i][offset+k].val;
				trees[i][offset+k].flag=0;
				trees[i][offset+k].fchild=NULL;
				trees[i][offset+k].next=NULL;
			}
			offset+=box_size;
			free(z_index);
			free(amt_index);
		}

	}

	end_t = clock();

	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;


	for(i=Level-1;i>0;i--)
		for(j=0;j<cnt[i];j++)
		{


			int a=(int)trees[i][j].x/2;

			int b=(int)trees[i][j].y/2;
			mapping[i][j]=find_father(trees[i-1],cnt[i-1],a,b);
		}

	start_t=clock();


	for(i=Level-1;i>0;i--)
	{
		for(j=0;j<cnt[i];j++)
		{       
			int father_index=mapping[i][j];
			struct	node *p=trees[i-1][father_index].fchild;
			if (p==NULL)
				trees[i-1][father_index].fchild=&trees[i][j];
			else
			{
				while(p->next!=NULL)
					p=p->next;
				p->next=&trees[i][j];
			}




		}


	}
	char *confFile = "/home/luo/ZFP/SZ/sz.config";
	size_t outSize;
	int r4 = 0, r3 = 0, r2 = 0, r5 = 0;
	SZ_Init(confFile);

	unsigned char *compressed1=malloc(datasize*sizeof(double));
	fp=fopen("sz.b","r");
	//fread(array_compressed, 1, array_size_compressed, fp);
	outSize=fread(compressed1, 1, outSize, fp);
	fclose(fp);

	double *decompressed = (double *)SZ_decompress(SZ_DOUBLE, compressed1, outSize,r5, r4, r3, r2, datasize);
	free(compressed1);

	double *vp=decompressed;
	for(i=0;i<1;i++)
		for(j=0;j<cnt[i];j++)
		{
			struct  node *p=&trees[i][j];
			PrintTree(p,vp,0);

		}


	free(decompressed);
	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);

	end_t = clock();
	total_t += (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Level SZ decompress: %lf\n", total_t  );

}



int main()
{
	int i,j,cnt[Level],box_cnt[Level];
	struct datapoint** data;
	data=malloc(Level*sizeof(* data)); 
	struct box** boxes;
	boxes=malloc(Level*sizeof(* boxes));



	FILE *fp=fopen("datapoint_noghost.info","r");

	for(i=0;i<Level;i++)
	{
		fread(&cnt[i],sizeof(int),1,fp);
		printf("data count= %d\n", cnt[i]);
		fread(&box_cnt[i],sizeof(int),1,fp);
		printf("box_cnt= %d\n", box_cnt[i]);
		boxes[i]=malloc(box_cnt[i]*sizeof(struct box));
		fread(boxes[i],sizeof(struct box),box_cnt[i],fp);
		data[i]=malloc(cnt[i]*sizeof(struct datapoint));
		fread(data[i],sizeof(struct datapoint),cnt[i],fp);
		//for(j=0;j<cnt[i];j++)
		//	printf("%d %d %lf\n", data[i][j].a,data[i][j].b,data[i][j].val);
	}
	fclose(fp);


	mapping=malloc(Level*sizeof(* mapping));
	for(i=0;i<Level;i++)
		mapping[i]=malloc(cnt[i]*sizeof(int));
	init_mapping(data,cnt,boxes,box_cnt);
	leveldata_box_zordering_ZFP_compress(data,cnt,boxes,box_cnt);
	leveldata_box_zordering_ZFP_decompress(data,cnt,boxes,box_cnt);
	leveldata_box_zordering_SZ_compress(data,cnt,boxes,box_cnt);
	leveldata_box_zordering_SZ_decompress(data,cnt,boxes,box_cnt);
	leveldata_box_zordering_level_ZFP_compress(data,cnt,boxes,box_cnt);
	leveldata_box_zordering_level_ZFP_decompress(data,cnt,boxes,box_cnt);
	leveldata_box_zordering_level_SZ_compress(data,cnt,boxes,box_cnt);
	leveldata_box_zordering_level_SZ_decompress(data,cnt,boxes,box_cnt);
	//	leveldata_box_zordering_level(data,cnt,boxes,box_cnt);
	for(i=0;i<Level;i++)	
		free(data[i]);
	for(i=0;i<Level;i++)
		free(boxes[i]);
	free(boxes);
	free(data);
	for(i=0;i<Level;i++)
		free(mapping[i]);
	free(mapping);
	return 1;
}
