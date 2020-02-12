#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "zfp.h"
#include "sz.h"
#define Level 5
#define Refine_ratio 2
#define SIZE_MAX1  2147483647


double * fp_glob;
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
	int index;
};



void PrintTree(struct node* p,  int flag)
{
	if (p==NULL) 
		return;
	if(flag==1)
		fp_glob[0]= (*p).val;
	else
	{
		if(fp_glob[0]-(*p).val>10)
			printf("%lf,%lf\n",(*p).val,fp_glob[0]);

		(*p).val=fp_glob[0];

	}
	fp_glob++;
	//	p->flag==1; 
	(*p).flag=1;
	//  printf("%d\n",p->flag);
	if (p->fchild!=NULL) 
	{ PrintTree(p->fchild,flag); }
	if (p->next!=NULL)
	{ PrintTree(p->next,flag); } 


}


int find_father(struct datapoint *data, int size,int a, int b)
{

	int i;
	for(i=0;i<size;i++)
		if(data[i].a==a&&data[i].b==b)
			return i;
	printf("do not find (%d,%d)\n",a,b);
	return -1;
}
int compare_box(struct box  b1, struct box  b2)
{
	if(b1.x1/Refine_ratio<b2.x1)
		return 0;

	if(b1.y1/Refine_ratio<b2.y1)
		return 0;

	if(b1.x2/Refine_ratio>b2.x2)
		return 0;

	if(b1.y2/Refine_ratio>b2.y2)
		return 0;

	return 1;

}

int child_cover_parent(struct box  b1, struct box  b2){
	if(b1.x1/Refine_ratio>b2.x1)
		return 0;

	if(b1.y1/Refine_ratio>b2.y1)
		return 0;

	if(b1.x2/Refine_ratio<b2.x2)
		return 0;

	if(b1.y2/Refine_ratio<b2.y2)
		return 0;

	return 1;

}
int find_leftup_box(struct box  b1, struct box  b2){
	if(b1.x1/Refine_ratio<b2.x1)
		return 0;

	if(b1.y1/Refine_ratio<b2.y1)
		return 0;

	if(b1.x2/Refine_ratio<b2.x2&&b1.y2/Refine_ratio<b2.y2)
		return 0;

	if(b1.x1/Refine_ratio>b2.x2)
		return 0;
	if(b1.y1/Refine_ratio>b2.y2)
		return 0;

	return 1;

}


int init_mapping(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{
	int i,j;
	for(i=Level-1;i>0;i--)
		for(j=0;j<cnt[i];j++)
		{


			int a=(int)data[i][j].a/Refine_ratio;

			int b=(int)data[i][j].b/Refine_ratio;
			mapping[i][j]=find_father(data[i-1],cnt[i-1],a,b);
		}


}

int mapping_by_box(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{
	int i,j;
	int offset,k;
	int off1;
	for(i=Level-1;i>0;i--)
	{
		off1=0;
		for(j=0;j<box_cnt[i];j++)
		{
			offset=0;

			int cnt1=0;
			for( k=0;k<box_cnt[i-1];k++)
				if(compare_box(boxes[i][j],boxes[i-1][k]))
				{

					cnt1++;
					break;

				}	
				else
					offset=offset+(boxes[i-1][k].x2-boxes[i-1][k].x1+1)*(boxes[i-1][k].y2-boxes[i-1][k].y1+1);
			int length=(boxes[i][j].x2-boxes[i][j].x1+1)*(boxes[i][j].y2-boxes[i][j].y1+1); 
			int width=boxes[i][j].x2-boxes[i][j].x1+1;
			int width_f=boxes[i-1][k].x2-boxes[i-1][k].x1+1;

			if(k<box_cnt[i-1]) 
				for (int i1=0;i1<length;i1++)
				{

					int off_x=data[i][off1+i1].a/Refine_ratio-data[i-1][offset].a;
					int off_y=data[i][off1+i1].b/Refine_ratio-data[i-1][offset].b;	

					mapping[i][off1+i1]=offset+off_x+off_y*width_f;


				}
			/*Prof. Liu: Here is where I loaf on the job. If the box is overlaped with two parrent boxes.*/
			else

			{ 

				int l;
				struct box box_sub[4];
				for(l=0;l<box_cnt[i-1];l++)
					if(find_leftup_box(boxes[i][j],boxes[i-1][l]))
					{
						//printf("l:%d\n",l);
						int coarse_x=Refine_ratio*boxes[i-1][l].x2+1;
						int coarse_y=Refine_ratio*boxes[i-1][l].y2+1;
						if(coarse_x>boxes[i][j].x2)
							coarse_x=boxes[i][j].x2;
						if(coarse_y>boxes[i][j].y2)
							coarse_y=boxes[i][j].y2;

						box_sub[0].x1=boxes[i][j].x1;
						box_sub[0].y1=boxes[i][j].y1;
						box_sub[0].x2=coarse_x;
						box_sub[0].y2=coarse_y;
						box_sub[1].x1=coarse_x+1;
						box_sub[1].y1=boxes[i][j].y1;
						box_sub[1].x2=boxes[i][j].x2;
						box_sub[1].y2=coarse_y;
						box_sub[2].x1=boxes[i][j].x1;
						box_sub[2].y1=coarse_y+1;
						box_sub[2].x2=coarse_x;
						box_sub[2].y2=boxes[i][j].y2;
						box_sub[3].x1=coarse_x+1;
						box_sub[3].y1=coarse_y+1;
						box_sub[3].x2=boxes[i][j].x2;
						box_sub[3].y2=boxes[i][j].y2;
						//printf("box:%d %d %d %d: \n",boxes[i][j].x1,boxes[i][j].y1,boxes[i][j].x2,boxes[i][j].y2);
						for(int i2=0;i2<4;i2++){
							int offset_sub=0;
							int f_box=-1;
							if(box_sub[i2].x2>=box_sub[i2].x1&&box_sub[i2].y2>=box_sub[i2].y1){
								for(int l1=0;l1<box_cnt[i-1];l1++)
									if(compare_box(box_sub[i2],boxes[i-1][l1]))
									{
										//	printf("box:%d %d %d %d: ",box_sub[i2].x1,box_sub[i2].y1,box_sub[i2].x2,box_sub[i2].y2);
										//	printf("l1:%d, box_cnt: %d\n",l1,box_cnt[i]);
										f_box=l1;
										break;

									}
									else
										offset_sub=offset_sub+(boxes[i-1][l1].x2-boxes[i-1][l1].x1+1)*(boxes[i-1][l1].y2-boxes[i-1][l1].y1+1);
								if(f_box!=-1)
								{
									int width_f_sub=boxes[i-1][f_box].x2-boxes[i-1][f_box].x1+1;
									for (int i1=box_sub[i2].y1;i1<=box_sub[i2].y2;i1++)
										for (int j1=box_sub[i2].x1;j1<=box_sub[i2].x2;j1++)
										{

											int sub_x=j1/Refine_ratio-boxes[i-1][f_box].x1;
											int sub_y=i1/Refine_ratio-boxes[i-1][f_box].y1;
											mapping[i][off1+(i1-boxes[i][j].y1)*width+(j1-boxes[i][j].x1)]=offset_sub+sub_x+sub_y*width_f_sub;


										}

								}
								else
								{
									for (int i1=box_sub[i2].y1;i1<=box_sub[i2].y2;i1++)
										for (int j1=box_sub[i2].x1;j1<=box_sub[i2].x2;j1++)
										{
											int offset_sub1=0;
											int f_box1=-1;
											/*if(j1%2==1&&j1!=boxes[i][j].x1)
											  {
											  mapping[i][off1+(i1-boxes[i][j].y1)*width+(j1-boxes[i][j].x1)]=mapping[i][off1+(i1-boxes[i][j].y1)*width+(j1-boxes[i][j].x1)-1];
											  continue;
											  }*/
											struct box box_sub;
											box_sub.x1=j1;
											box_sub.y1=i1;
											box_sub.x2=j1;
											box_sub.y2=i1;
											for(int l1=0;l1<box_cnt[i-1];l1++)
												if(compare_box(box_sub,boxes[i-1][l1]))
												{
													//      printf("box:%d %d %d %d: ",box_sub[i2].x1,box_sub[i2].y1,box_sub[i2].x2,box_sub[i2].y2);
													//      printf("l1:%d, box_cnt: %d\n",l1,box_cnt[i]);
													f_box1=l1;
													break;

												}
												else
													offset_sub1=offset_sub1+(boxes[i-1][l1].x2-boxes[i-1][l1].x1+1)*(boxes[i-1][l1].y2-boxes[i-1][l1].y1+1);
											int width_f_sub=boxes[i-1][f_box1].x2-boxes[i-1][f_box1].x1+1;


											int sub_x=j1/Refine_ratio-boxes[i-1][f_box1].x1;
											int sub_y=i1/Refine_ratio-boxes[i-1][f_box1].y1;
											mapping[i][off1+(i1-boxes[i][j].y1)*width+(j1-boxes[i][j].x1)]=offset_sub1+sub_x+sub_y*width_f_sub;


										}
								}

							}
						}// box_sub[0-3] 

						break;

					}






			}//Child box are not covered within a parent box.



			off1=off1+length;

			//	printf("cnt1:%d\n",cnt1);
		}//j for




	}


	/*	for(i=Level-1;i>0;i--)
		for(j=0;j<cnt[i];j++)
		{
		if(data[i][j].a/Refine_ratio!=data[i-1][mapping[i][j]].a||data[i][j].b/Refine_ratio!=data[i-1][mapping[i][j]].b) 
		printf("Error! %d,%d: %d, %d\n",data[i][j].a,data[i-1][mapping[i][j]].a,data[i][j].b,data[i-1][mapping[i][j]].b);
		}*/

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
	// array = (double *) buffer;

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
	clock_t start_t1=start_t;
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
//	end_t = clock();
//	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
//	printf("Baseline_init: %lf\n", total_t  );
//	start_t=clock();
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
			int *recipe_en=malloc(box_size*sizeof(int));
			int tr=0;
			for(k=0;k<z_size;k++){
				if(z_index[k]!=-1)
					recipe_en[tr++]=z_index[k];
			}
			if(tr!=box_size){
				printf("tr!=box_size, %d, %d\n",tr,box_size);
				for (k=0;k<box_size;k++)
					printf("%d ",recipe_en[k]);
			}
			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+recipe_en[k]].a;
				trees[i][offset+k].y=data[i][offset+recipe_en[k]].b;
				trees[i][offset+k].val=data[i][offset+recipe_en[k]].val;
				trees[i][offset+k].flag=1;
				//trees[i][offset+k].fchild=NULL;
				//trees[i][offset+k].next=NULL;
			}

			offset+=box_size;
			free(z_index);
			free(recipe_en);
		}

	}
	//end_t = clock();
	//total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	//printf("Baseline_Zordering: %lf\n", total_t  );
	//start_t=clock();

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
	//printf("Baseline_traverse: %lf\n", total_t  );
	printf("Baseline_Zordering: %lf\n", total_t  );
	start_t=clock();


	size_t compr_size = compress (dataArray, datasize, 1);
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Baseline_compress: %lf\n", total_t  );
	start_t=clock();


	free(dataArray);
	end_t = clock();
	total_t = (double)(end_t - start_t1) / CLOCKS_PER_SEC;
	printf("Basline ZFP compress: %lf\n", total_t  );
}

void leveldata_box_zordering_ZFP_decompress(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{



	clock_t start_t, end_t; double total_t;

	start_t = clock();
	clock_t start_t1=start_t;
	int i,j,k;

	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	double *dataArray=malloc(datasize*sizeof(double));
	double * array_decompressed=malloc(datasize*sizeof(double));


	decompress (array_decompressed, datasize, 1);
	struct node** trees;
	trees=malloc(Level*sizeof(* trees));
	for(i=0;i<Level;i++)
		trees[i]=malloc(cnt[i]*sizeof(struct node));

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Baseline_decompress: %lf\n", total_t  );
	start_t=clock();


	int offset=0;

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{

			trees[i][j].flag=0;

		}
//	end_t = clock();
//	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
//	printf("Baseline_init: %lf\n", total_t  );
//	start_t=clock();
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
			int *recipe_en=malloc(box_size*sizeof(int));
			int tr=0;
			for(k=0;k<z_size;k++){
				if(z_index[k]!=-1)
					recipe_en[tr++]=z_index[k];
			}
			if(tr!=box_size){
				printf("tr!=box_size, %d, %d\n",tr,box_size);
				for (k=0;k<box_size;k++)
					printf("%d ",recipe_en[k]);
			}
			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+recipe_en[k]].a;
				trees[i][offset+k].y=data[i][offset+recipe_en[k]].b;
				trees[i][offset+k].val=data[i][offset+recipe_en[k]].val;
				trees[i][offset+k].flag=1;
				//trees[i][offset+k].fchild=NULL;
				//trees[i][offset+k].next=NULL;
			}

			offset+=box_size;
			free(z_index);
			free(recipe_en);
		}

	}
//	end_t = clock();
//	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
//	printf("Baseline_Zordering: %lf\n", total_t  );
//	start_t=clock();




	int offset1=0;
	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			if(trees[i][j].val-array_decompressed[offset1]>10)
				printf("%lf,%lf\n",trees[i][j].val,array_decompressed[offset1]);
			trees[i][j].val=array_decompressed[offset1];
			offset1++;
		}

	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);

	free(array_decompressed);
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Baseline_Zordering: %lf\n", total_t  );
//	printf("Baseline_traverse: %lf\n", total_t  );
	start_t=clock();

	end_t = clock();
	total_t = (double)(end_t - start_t1) / CLOCKS_PER_SEC;
	printf("Baseline ZFP decompress: %lf\n", total_t  );
}

void leveldata_box_zordering_SZ_compress(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{

	clock_t start_t, end_t; double total_t;

	start_t = clock();
	clock_t start_t1=start_t;
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
//	end_t = clock();
//	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
//	printf("Baseline_init: %lf\n", total_t  );
//	start_t=clock();
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
			int *recipe_en=malloc(box_size*sizeof(int));
			int tr=0;
			for(k=0;k<z_size;k++){
				if(z_index[k]!=-1)
					recipe_en[tr++]=z_index[k];
			}
			if(tr!=box_size){
				printf("tr!=box_size, %d, %d\n",tr,box_size);
				for (k=0;k<box_size;k++)
					printf("%d ",recipe_en[k]);
			}
			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+recipe_en[k]].a;
				trees[i][offset+k].y=data[i][offset+recipe_en[k]].b;
				trees[i][offset+k].val=data[i][offset+recipe_en[k]].val;
				trees[i][offset+k].flag=1;
				trees[i][offset+k].fchild=NULL;
				trees[i][offset+k].next=NULL;
			}

			offset+=box_size;
			free(z_index);
			free(recipe_en);
		}

	}
//	end_t = clock();
//	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
//	printf("Baseline_Zordering: %lf\n", total_t  );
//	start_t=clock();
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
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
//	printf("Baseline_traverse: %lf\n", total_t  );
	printf("Baseline_Zordering: %lf\n", total_t  );
	start_t=clock();
	/*confparams_cpr->absErrBound = tor[0];
	  cout << "abs = " << confparams_cpr->absErrBound << endl;

	//cout << "bug start\n" << endl;
	unsigned char *compressed = SZ_compress(SZ_DOUBLE, &(thick[0]), &outSize, r5, r4, r3, r2 ,thick_len);
	double *decompressed = (double *)SZ_decompress(SZ_DOUBLE, compressed, outSize,r5, r4, r3, r2, thick_len);
	 */
	char *confFile = "/home/luo/ZFP/SZ/sz.config";
	size_t outSize;
	int r4 = 0, r3 = 0, r2 = 0, r5 = 0;
	SZ_Init(confFile);

	unsigned char *compressed = SZ_compress(SZ_DOUBLE, dataArray, &outSize, r5, r4, r3, r2 ,datasize);

	FILE *fp=fopen("sz_baseline.b","w");
	fwrite(compressed, 1, outSize, fp);
	fclose(fp);
	free(compressed); 
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Baseline_compress: %lf\n", total_t  );
	start_t=clock();


	free(dataArray);
	end_t = clock();
	total_t = (double)(end_t - start_t1) / CLOCKS_PER_SEC;
	printf("Baseline SZ compress: %lf\n", total_t  );
}

void leveldata_box_zordering_SZ_decompress(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{


	clock_t start_t, end_t; double total_t;

	start_t = clock();
	clock_t start_t1=start_t;
	int i,j,k;

	char *confFile = "/home/luo/ZFP/SZ/sz.config";
	size_t outSize=SIZE_MAX1;
	int r4 = 0, r3 = 0, r2 = 0, r5 = 0;
	SZ_Init(confFile);

	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	unsigned char *compressed1=malloc(datasize*sizeof(double));
	FILE *fp=fopen("sz_baseline.b","r");
	//fread(array_compressed, 1, array_size_compressed, fp);
	outSize=fread(compressed1, 1, outSize, fp);
	fclose(fp);



	double *decompressed = (double *)SZ_decompress(SZ_DOUBLE, compressed1, outSize,r5, r4, r3, r2, datasize);
	free(compressed1);
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Baseline_decompress: %lf\n", total_t  );
	start_t=clock();


	struct node** trees;
	trees=malloc(Level*sizeof(* trees));
	for(i=0;i<Level;i++)
		trees[i]=malloc(cnt[i]*sizeof(struct node));

	int offset=0;

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{

			trees[i][j].flag=0;

		}
//	end_t = clock();
//	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
//	printf("Baseline_init: %lf\n", total_t  );
//	start_t=clock();
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
			int *recipe_en=malloc(box_size*sizeof(int));
			int tr=0;
			for(k=0;k<z_size;k++){
				if(z_index[k]!=-1)
					recipe_en[tr++]=z_index[k];
			}
			if(tr!=box_size){
				printf("tr!=box_size, %d, %d\n",tr,box_size);
				for (k=0;k<box_size;k++)
					printf("%d ",recipe_en[k]);
			}
			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+recipe_en[k]].a;
				trees[i][offset+k].y=data[i][offset+recipe_en[k]].b;
				trees[i][offset+k].val=data[i][offset+recipe_en[k]].val;
				trees[i][offset+k].flag=1;
				//trees[i][offset+k].fchild=NULL;
				//trees[i][offset+k].next=NULL;
			}

			offset+=box_size;
			free(z_index);
			free(recipe_en);
		}

	}
//	end_t = clock();
//	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
//	printf("Baseline_Zordering: %lf\n", total_t  );
//	start_t=clock();




	int offset1=0;
	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			//fwrite(&trees[i][j].val,sizeof(double),1,fp);
			if(trees[i][j].val-decompressed[offset1]>10)
				printf("%lf,%lf\n",trees[i][j].val,decompressed[offset1]);

			trees[i][j].val=decompressed[offset1];
			offset1++;
		}

	free(decompressed);
	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
//	printf("Baseline_traverse: %lf\n", total_t  );
	printf("Baseline_Zordering: %lf\n", total_t  );
	start_t=clock();

	end_t = clock();
	total_t = (double)(end_t - start_t1) / CLOCKS_PER_SEC;
	printf("Baseline SZ decompress: %lf\n", total_t  );
}



void leveldata_box_zordering_level_ZFP_compress(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{
	clock_t start_t, end_t; double total_t;
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

	mapping_by_box(data,cnt,boxes,box_cnt);
	int offset=0;

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{

			trees[i][j].flag=0;

		}

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("LevelRe_init: %lf\n", total_t  );
	start_t=clock();

	int* recipe_de;

	for(i=0;i<Level;i++)
	{ 
		offset=0;

		if(i<Level-1)
			recipe_de=malloc(cnt[i]*sizeof(int));
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
			int *recipe_en=malloc(box_size*sizeof(int));
			int tr=0;
			for(k=0;k<z_size;k++){
				if(z_index[k]!=-1)
					recipe_en[tr++]=z_index[k];
			}
			if(tr!=box_size){
				printf("tr!=box_size, %d, %d\n",tr,box_size);
				for (k=0;k<box_size;k++)
					printf("%d ",recipe_en[k]);
			}
			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+recipe_en[k]].a;
				trees[i][offset+k].y=data[i][offset+recipe_en[k]].b;
				trees[i][offset+k].val=data[i][offset+recipe_en[k]].val;
				trees[i][offset+k].index=offset+recipe_en[k];
				//	trees[i][offset+k].y=data[i][offset+k].b;
				//	trees[i][offset+k].val=data[i][offset+k].val;
				trees[i][offset+k].flag=0;
				trees[i][offset+k].fchild=NULL;
				trees[i][offset+k].next=NULL;
			}
			if(i<Level-1)
				for(int j1=0;j1<box_size;j1++){
					k=0;
					while(recipe_en[k]!=j1)
						k++;
					recipe_de[j1+offset]=k+offset;
				}


			offset+=box_size;
			free(z_index);
			free(recipe_en);
		}

		if(i<Level-1)
		{
			for(j=0;j<cnt[i+1];j++){
				mapping[i+1][j]=recipe_de[mapping[i+1][j]];
			}

			free(recipe_de);

		}
	}
	end_t = clock();

	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

	printf("LevelRe_Zordering: %lf\n", total_t  );

	/*
	   for(i=Level-1;i>0;i--)
	   for(j=0;j<cnt[i];j++)
	   {
	   if(trees[i][j].x/Refine_ratio!=trees[i-1][mapping[i][trees[i][j].index]].x||trees[i][j].y/Refine_ratio!=trees[i-1][mapping[i][trees[i][j].index]].y)
	   printf("error! %d,%d: %d, %d\n",trees[i][j].x,trees[i-1][mapping[i][trees[i][j].index]].x,trees[i][j].y,trees[i-1][mapping[i][trees[i][j].index]].y);
	   }
	 */

	start_t=clock();


	for(i=Level-1;i>0;i--)
	{
		for(j=0;j<cnt[i];j++)
		{       
			int father_index=mapping[i][trees[i][j].index];
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
	printf("LevelRe_build: %lf\n", total_t  );
	start_t=clock();

	//	double *vp=dataArray;
	fp_glob=dataArray;
	for(i=0;i<1;i++)
		for(j=0;j<cnt[i];j++)
		{
			struct  node *p=&trees[i][j];
			PrintTree(p,1);

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
	printf("LevelRe_traverse: %lf\n", total_t  );
	size_t compr_size = compress (dataArray, datasize, 5);
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("LevelRe_compress: %lf\n", total_t  );
	start_t=clock();

	free(dataArray);
	end_t = clock();
	total_t = (double)(end_t - start_t1) / CLOCKS_PER_SEC;
	printf("LevelRe ZFP compress: %lf\n", total_t  );

}


void leveldata_box_zordering_level_ZFP_decompress(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{

	clock_t start_t, end_t; double total_t;
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

	mapping_by_box(data,cnt,boxes,box_cnt);
	int offset=0;

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{

			trees[i][j].flag=0;

		}

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("LevelRe_init: %lf\n", total_t  );
	start_t=clock();

	int* recipe_de;

	for(i=0;i<Level;i++)
	{ 
		offset=0;

		if(i<Level-1)
			recipe_de=malloc(cnt[i]*sizeof(int));
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
			int *recipe_en=malloc(box_size*sizeof(int));
			int tr=0;
			for(k=0;k<z_size;k++){
				if(z_index[k]!=-1)
					recipe_en[tr++]=z_index[k];
			}
			if(tr!=box_size){
				printf("tr!=box_size, %d, %d\n",tr,box_size);
				for (k=0;k<box_size;k++)
					printf("%d ",recipe_en[k]);
			}
			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+recipe_en[k]].a;
				trees[i][offset+k].y=data[i][offset+recipe_en[k]].b;
				trees[i][offset+k].val=data[i][offset+recipe_en[k]].val;
				trees[i][offset+k].index=offset+recipe_en[k];
				//	trees[i][offset+k].y=data[i][offset+k].b;
				//	trees[i][offset+k].val=data[i][offset+k].val;
				trees[i][offset+k].flag=0;
				trees[i][offset+k].fchild=NULL;
				trees[i][offset+k].next=NULL;
			}
			if(i<Level-1)
				for(int j1=0;j1<box_size;j1++){
					k=0;
					while(recipe_en[k]!=j1)
						k++;
					recipe_de[j1+offset]=k+offset;
				}


			offset+=box_size;
			free(z_index);
			free(recipe_en);
		}

		if(i<Level-1)
		{
			for(j=0;j<cnt[i+1];j++){
				mapping[i+1][j]=recipe_de[mapping[i+1][j]];
			}

			free(recipe_de);

		}
	}
	end_t = clock();

	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

	printf("LevelRe_Zordering: %lf\n", total_t  );

	/*
	   for(i=Level-1;i>0;i--)
	   for(j=0;j<cnt[i];j++)
	   {
	   if(trees[i][j].x/Refine_ratio!=trees[i-1][mapping[i][trees[i][j].index]].x||trees[i][j].y/Refine_ratio!=trees[i-1][mapping[i][trees[i][j].index]].y)
	   printf("error! %d,%d: %d, %d\n",trees[i][j].x,trees[i-1][mapping[i][trees[i][j].index]].x,trees[i][j].y,trees[i-1][mapping[i][trees[i][j].index]].y);
	   }
	 */

	start_t=clock();


	for(i=Level-1;i>0;i--)
	{
		for(j=0;j<cnt[i];j++)
		{       
			int father_index=mapping[i][trees[i][j].index];
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
	printf("LevelRe_build: %lf\n", total_t  );
	start_t=clock();

	double * array_decompressed=malloc(datasize*sizeof(double));


	decompress (array_decompressed, datasize, 5);
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("LevelRe_decompress: %lf\n", total_t  );
	start_t=clock();

	//	double *vp=array_decompressed;
	fp_glob=array_decompressed;

	for(i=0;i<1;i++)
		for(j=0;j<cnt[i];j++)
		{
			struct  node *p=&trees[i][j];
			PrintTree(p,0);

		}




	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);
	free(array_decompressed);
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("LevelRe_traverse: %lf\n", total_t  );
	start_t=clock();

	end_t = clock();
	total_t = (double)(end_t - start_t1) / CLOCKS_PER_SEC;
	printf("LevelRe ZFP decompress: %lf\n", total_t  );
}

void leveldata_box_zordering_level_SZ_compress(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{


	clock_t start_t, end_t; double total_t;
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

	mapping_by_box(data,cnt,boxes,box_cnt);
	int offset=0;

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{

			trees[i][j].flag=0;

		}

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("LevelRe_init: %lf\n", total_t  );
	start_t=clock();

	int* recipe_de;

	for(i=0;i<Level;i++)
	{ 
		offset=0;

		if(i<Level-1)
			recipe_de=malloc(cnt[i]*sizeof(int));
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
			int *recipe_en=malloc(box_size*sizeof(int));
			int tr=0;
			for(k=0;k<z_size;k++){
				if(z_index[k]!=-1)
					recipe_en[tr++]=z_index[k];
			}
			if(tr!=box_size){
				printf("tr!=box_size, %d, %d\n",tr,box_size);
				for (k=0;k<box_size;k++)
					printf("%d ",recipe_en[k]);
			}
			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+recipe_en[k]].a;
				trees[i][offset+k].y=data[i][offset+recipe_en[k]].b;
				trees[i][offset+k].val=data[i][offset+recipe_en[k]].val;
				trees[i][offset+k].index=offset+recipe_en[k];
				//	trees[i][offset+k].y=data[i][offset+k].b;
				//	trees[i][offset+k].val=data[i][offset+k].val;
				trees[i][offset+k].flag=0;
				trees[i][offset+k].fchild=NULL;
				trees[i][offset+k].next=NULL;
			}
			if(i<Level-1)
				for(int j1=0;j1<box_size;j1++){
					k=0;
					while(recipe_en[k]!=j1)
						k++;
					recipe_de[j1+offset]=k+offset;
				}


			offset+=box_size;
			free(z_index);
			free(recipe_en);
		}

		if(i<Level-1)
		{
			for(j=0;j<cnt[i+1];j++){
				mapping[i+1][j]=recipe_de[mapping[i+1][j]];
			}

			free(recipe_de);

		}
	}
	end_t = clock();

	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

	printf("LevelRe_Zordering: %lf\n", total_t  );

	/*
	   for(i=Level-1;i>0;i--)
	   for(j=0;j<cnt[i];j++)
	   {
	   if(trees[i][j].x/Refine_ratio!=trees[i-1][mapping[i][trees[i][j].index]].x||trees[i][j].y/Refine_ratio!=trees[i-1][mapping[i][trees[i][j].index]].y)
	   printf("error! %d,%d: %d, %d\n",trees[i][j].x,trees[i-1][mapping[i][trees[i][j].index]].x,trees[i][j].y,trees[i-1][mapping[i][trees[i][j].index]].y);
	   }
	 */

	start_t=clock();


	for(i=Level-1;i>0;i--)
	{
		for(j=0;j<cnt[i];j++)
		{       
			int father_index=mapping[i][trees[i][j].index];
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
	printf("LevelRe_build: %lf\n", total_t  );
	start_t=clock();




	//	double *vp=dataArray;

	fp_glob=dataArray;
	for(i=0;i<1;i++)
		for(j=0;j<cnt[i];j++)
		{
			struct  node *p=&trees[i][j];
			PrintTree(p,1);

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
	printf("LevelRe_traverse: %lf\n", total_t  );
	start_t=clock();

	char *confFile = "/home/luo/ZFP/SZ/sz.config";
	size_t outSize;
	int r4 = 0, r3 = 0, r2 = 0, r5 = 0;
	SZ_Init(confFile);

	unsigned char *compressed = SZ_compress(SZ_DOUBLE, dataArray, &outSize, r5, r4, r3, r2 ,datasize);

	fp=fopen("sz_levelRe.b","w");
	fwrite(compressed, 1, outSize, fp);
	fclose(fp);
	free(compressed);

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("LevelRe_compress: %lf\n", total_t  );
	start_t=clock();


	free(dataArray);
	end_t = clock();
	total_t = (double)(end_t - start_t1) / CLOCKS_PER_SEC;
	printf("LevelRe SZ compress: %lf\n", total_t  );



}

void leveldata_box_zordering_level_SZ_decompress(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{


	clock_t start_t, end_t; double total_t;
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

	mapping_by_box(data,cnt,boxes,box_cnt);
	int offset=0;

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{

			trees[i][j].flag=0;

		}

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("LevelRe_init: %lf\n", total_t  );
	start_t=clock();

	int* recipe_de;

	for(i=0;i<Level;i++)
	{ 
		offset=0;

		if(i<Level-1)
			recipe_de=malloc(cnt[i]*sizeof(int));
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
			int *recipe_en=malloc(box_size*sizeof(int));
			int tr=0;
			for(k=0;k<z_size;k++){
				if(z_index[k]!=-1)
					recipe_en[tr++]=z_index[k];
			}
			if(tr!=box_size){
				printf("tr!=box_size, %d, %d\n",tr,box_size);
				for (k=0;k<box_size;k++)
					printf("%d ",recipe_en[k]);
			}
			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+recipe_en[k]].a;
				trees[i][offset+k].y=data[i][offset+recipe_en[k]].b;
				trees[i][offset+k].val=data[i][offset+recipe_en[k]].val;
				trees[i][offset+k].index=offset+recipe_en[k];
				//	trees[i][offset+k].y=data[i][offset+k].b;
				//	trees[i][offset+k].val=data[i][offset+k].val;
				trees[i][offset+k].flag=0;
				trees[i][offset+k].fchild=NULL;
				trees[i][offset+k].next=NULL;
			}
			if(i<Level-1)
				for(int j1=0;j1<box_size;j1++){
					k=0;
					while(recipe_en[k]!=j1)
						k++;
					recipe_de[j1+offset]=k+offset;
				}


			offset+=box_size;
			free(z_index);
			free(recipe_en);
		}

		if(i<Level-1)
		{
			for(j=0;j<cnt[i+1];j++){
				mapping[i+1][j]=recipe_de[mapping[i+1][j]];
			}

			free(recipe_de);

		}
	}
	end_t = clock();

	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

	printf("LevelRe_Zordering: %lf\n", total_t  );

	/*
	   for(i=Level-1;i>0;i--)
	   for(j=0;j<cnt[i];j++)
	   {
	   if(trees[i][j].x/Refine_ratio!=trees[i-1][mapping[i][trees[i][j].index]].x||trees[i][j].y/Refine_ratio!=trees[i-1][mapping[i][trees[i][j].index]].y)
	   printf("error! %d,%d: %d, %d\n",trees[i][j].x,trees[i-1][mapping[i][trees[i][j].index]].x,trees[i][j].y,trees[i-1][mapping[i][trees[i][j].index]].y);
	   }
	 */

	start_t=clock();


	for(i=Level-1;i>0;i--)
	{
		for(j=0;j<cnt[i];j++)
		{       
			int father_index=mapping[i][trees[i][j].index];
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
	printf("LevelRe_build: %lf\n", total_t  );
	start_t=clock();









	char *confFile = "/home/luo/ZFP/SZ/sz.config";
	size_t outSize=SIZE_MAX1;
	int r4 = 0, r3 = 0, r2 = 0, r5 = 0;
	SZ_Init(confFile);

	unsigned char *compressed1=malloc(datasize*sizeof(double));
	fp=fopen("sz_levelRe.b","r");
	//fread(array_compressed, 1, array_size_compressed, fp);
	outSize=fread(compressed1, 1, outSize, fp);
	fclose(fp);

	double *decompressed = (double *)SZ_decompress(SZ_DOUBLE, compressed1, outSize,r5, r4, r3, r2, datasize);
	free(compressed1);
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("LevelRe_decompress: %lf\n", total_t  );
	start_t=clock();

	//	double *vp=decompressed;
	fp_glob=decompressed;
	for(i=0;i<1;i++)
		for(j=0;j<cnt[i];j++)
		{
			struct  node *p=&trees[i][j];
			PrintTree(p,0);

		}


	free(decompressed);
	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("LevelRe_traverse: %lf\n", total_t  );
	start_t=clock();

	end_t = clock();
	total_t = (double)(end_t - start_t1) / CLOCKS_PER_SEC;
	printf("LevelRe SZ decompress: %lf\n", total_t  );

}



int main()
{
	int i,j,cnt[Level],box_cnt[Level];
	struct datapoint** data;
	data=malloc(Level*sizeof(* data)); 
	struct box** boxes;
	boxes=malloc(Level*sizeof(* boxes));



	FILE *fp=fopen("datapoint.info","r");
	//	FILE *fp=fopen("datapoint_noghost.info","r");

	//	FILE *fp=fopen("datapoint_level_overhead.info","r");
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
	leveldata_box_zordering_ZFP_compress(data,cnt,boxes,box_cnt);
	leveldata_box_zordering_ZFP_decompress(data,cnt,boxes,box_cnt);
	leveldata_box_zordering_SZ_compress(data,cnt,boxes,box_cnt);
	leveldata_box_zordering_SZ_decompress(data,cnt,boxes,box_cnt);
	leveldata_box_zordering_level_ZFP_compress(data,cnt,boxes,box_cnt);
	leveldata_box_zordering_level_ZFP_decompress(data,cnt,boxes,box_cnt);
	leveldata_box_zordering_level_SZ_compress(data,cnt,boxes,box_cnt);
	leveldata_box_zordering_level_SZ_decompress(data,cnt,boxes,box_cnt);
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
