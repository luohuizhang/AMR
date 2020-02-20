#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define Level 5 
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


void mapping(struct node **data, int cnt [Level], int **mapping)
{
	int com_cnt=0;
	int i,j,k; double delta;
	char filename[50];

	for(k=Level-1;k>0;k--)   
		for(j=0;j<cnt[k];j++)
			for(i=0;i<cnt[k-1];i++)
			{
				if(data[k-1][i].x==data[k][j].x/2&&data[k-1][i].y==data[k][j].y/2)
				{
					//printf("%d %d %lf, %d %d %lf\n", data[li][i].a,data[li][i].b,data[li][i].val,data[hi][j].a,data[hi][j].b,data[hi][j].val);

					com_cnt++;
					break;
				}
			}

	printf("com_cnt= %d\n", com_cnt);
}

void PrintTree(struct node* p,FILE* fp)
{
	if (p==NULL) 
		return;
	fwrite(&(p->val),sizeof(double),1,fp);
	//	p->flag==1; 
	(*p).flag=1;
	//  printf("%d\n",p->flag);
	if (p->fchild!=NULL) 
	{ PrintTree(p->fchild,fp); }
	if (p->next!=NULL)
	{ PrintTree(p->next,fp); } 


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

void leveldata_row(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{
	clock_t start_t, end_t; double total_t;

	start_t = clock();
	int i,j,k;
	char filename[50];
	sprintf(filename,"Level_row.dat");
	FILE *fp=fopen(filename,"w");
	for(i=0;i<Level;i++)
	{
		for(k=-100;k<3000;k++)

			for(j=0;j<cnt[i];j++)
			{ 

				if(data[i][j].a==k)  
					//if(data[i][j].b==k)
					fwrite(&data[i][j].val,sizeof(double),1,fp);
			}

	}
	fclose(fp);
	end_t = clock();

	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Row-major: %f\n", total_t  );
}

void leveldata_row_level(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{
	clock_t start_t, end_t; double total_t;

	start_t = clock();
	int i,j,k;
	char filename[50];
	sprintf(filename,"Level_row_levelreordering.dat");
	FILE *fp=fopen(filename,"w");

	struct node** trees;
	trees=malloc(Level*sizeof(* trees));
	for(i=0;i<Level;i++)
		trees[i]=malloc(cnt[i]*sizeof(struct node));
	for(i=0;i<Level;i++)

	{
		int offset=0;
		for(k=-1000;k<3000;k++)

			for(j=0;j<cnt[i];j++)
			{

				if(data[i][j].a==k)  
					//		if(data[i][j].b==k)
				{

					trees[i][offset].x=data[i][j].a;
					trees[i][offset].y=data[i][j].b;
					trees[i][offset].val=data[i][j].val;
					trees[i][offset].flag=0;
					trees[i][offset].fchild=NULL;
					trees[i][offset].next=NULL;
					offset++;
				}
			}
		//        printf("offset: %d,%d\n",cnt[i],offset);
	}

	end_t = clock();

	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Row+level, row: %f\n", total_t  );

	start_t=clock();
	int ** mapping;
	mapping=malloc(Level*sizeof(* mapping));
	for(i=0;i<Level;i++)
		mapping[i]=malloc(cnt[i]*sizeof(int));
	for(i=Level-1;i>0;i--)
		for(j=0;j<cnt[i];j++)
		{


			int a=(int)trees[i][j].x/2;

			int b=(int)trees[i][j].y/2;
			mapping[i][j]=find_father(trees[i-1],cnt[i-1],a,b);
		}

	end_t = clock();

	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Row+level, mapping: %f\n", total_t  );

	start_t=clock();



	for(i=Level-1;i>0;i--)
	{
		for(j=0;j<cnt[i];j++)
		{       

			// if(father_index==-1)
			//	printf("%d,%d,%d,%d\n",a,b,trees[i][j].x,trees[i][j].y);
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
	printf("Row+level, build up trees: %f\n", total_t  );

	start_t=clock();

	for(i=0;i<1;i++)
		for(j=0;j<cnt[i];j++)
		{
			struct  node *p=&trees[i][j];
			PrintTree(p,fp);
		}

	end_t = clock();

	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Row+leve, travle trees: %f\n", total_t  );

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			if(trees[i][j].flag==0)                      
				printf("Not visit %d, %d\n",i,j);

		}

	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);


	fclose(fp);
}
void leveldata_box(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level],int col)
{
	clock_t start_t, end_t; double total_t;

	start_t = clock();
	int i,j;
	char filename[50];
	sprintf(filename,"Level_box_%d.dat",col);
	FILE *fp=fopen(filename,"w");

	for(i=0;i<Level;i++)
	{
		for(j=0;j<cnt[i];j++)
		{
			fwrite(&data[i][j].val,sizeof(double),1,fp);
		}

	}
	fclose(fp);
	end_t = clock();

	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Row-major: %f\n", total_t  );
}




void leveldata_box_level(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level],int col)
{
	clock_t start_t, end_t, total_t;

	start_t = clock();
	int i,j;
	char filename[50];
	sprintf(filename,"Level_box_levelreordering_%d.dat",col);
	FILE *fp=fopen(filename,"w");

	struct node** trees;
	trees=malloc(Level*sizeof(* trees));
	for(i=0;i<Level;i++)
		trees[i]=malloc(cnt[i]*sizeof(struct node));
	for(i=0;i<Level;i++)

	{

		for(j=0;j<cnt[i];j++)
		{


			trees[i][j].x=data[i][j].a;
			trees[i][j].y=data[i][j].b;
			trees[i][j].val=data[i][j].val;
			trees[i][j].flag=0;
			trees[i][j].fchild=NULL;
			trees[i][j].next=NULL;
		}

	}
	int ** mapping;
	mapping=malloc(Level*sizeof(* mapping));
	for(i=0;i<Level;i++)
		mapping[i]=malloc(cnt[i]*sizeof(int));
	for(i=Level-1;i>0;i--)
		for(j=0;j<cnt[i];j++)
		{


			int a=(int)trees[i][j].x/2;

			int b=(int)trees[i][j].y/2;
			mapping[i][j]=find_father(trees[i-1],cnt[i-1],a,b);
		}


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

	for(i=0;i<1;i++)
		for(j=0;j<cnt[i];j++)
		{
			struct  node *p=&trees[i][j];
			PrintTree(p,fp);

		}


	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			if(trees[i][j].flag==0)                      
				printf("Not visit %d,%d\n",i,j);

		}
	fclose(fp);
	for(i=0;i<Level;i++)
		free(trees[i]);
	for(i=0;i<Level;i++)
		free(mapping[i]);
	free(mapping);
	free(trees);
}


void leveldata_row_zordering(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{
	clock_t start_t, end_t; double total_t;

	start_t = clock();
	int i,j,k;
	char filename[50];
	sprintf(filename,"Level_row_zordering.dat");
	FILE *fp=fopen(filename,"w");



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

	struct node * data0=malloc(cnt[0]*sizeof(struct node));

	for(i=0;i<1;i++)

	{
		offset=0;
		for(k=-1000;k<3000;k++)

			for(j=0;j<cnt[i];j++)
			{

				if(data[i][j].a==k)  
					//	if(data[i][j].b==k)
				{

					data0[offset].x=data[i][j].a;
					data0[offset].y=data[i][j].b;
					data0[offset].val=data[i][j].val;
					data0[offset].flag=0;
					data0[offset].fchild=NULL;
					data0[offset].next=NULL;
					offset++;
				}
			}
		//        printf("offset: %d,%d\n",cnt[i],offset);
	}



	int max_x=0;
	int max_y=0;
	for(i=0;i<1;i++)
	{

		for(j=0;j<cnt[i];j++)
		{


			if(data[i][j].a>max_x)
				max_x=data[i][j].a;
			if(data[i][j].b>max_y)
				max_y=data[i][j].b;



		}
		// printf("offset: %d,%d\n",cnt[i],offset);

		int z0_size= EncodeMorton2(max_x,max_y)+1;
		//printf("%d,%d,%d\n",a,b,z_size);
		int *z0_index=malloc(z0_size*sizeof(int));
		//memset (z_index,-1,z_size*sizeof(int));
		for(k=0;k<z0_size;k++){

			z0_index[k]=-1;
		}

		int box0_size=(max_x+1)*(max_y+1);
		//printf("cnt[0], box0_size: %d,%d,%d\n",cnt[0],z0_size,box0_size);
		for(int m=0;m<=max_y;m++)
			for(int l=0;l<=max_x;l++)
			{
				z0_index[EncodeMorton2(l,m)]=l+m*(max_x+1);
			}
		int *amt0_index=malloc(box0_size*sizeof(int));
		int tr0=0;
		for(k=0;k<z0_size;k++){
			if(z0_index[k]!=-1)
				amt0_index[tr0++]=z0_index[k];
		}
		if(tr0!=box0_size){
			printf("tr!=box_size, %d, %d\n",tr0,box0_size);
			for (k=0;k<box0_size;k++)
				printf("%d ",amt0_index[k]);
		}
		for(k=0;k<box0_size;k++)
		{
			trees[i][k].x=data0[amt0_index[k]].x;
			trees[i][k].y=data0[amt0_index[k]].y;
			trees[i][k].val=data0[amt0_index[k]].val;
			trees[i][k].flag=0;
			trees[i][k].fchild=NULL;
			trees[i][k].next=NULL;
		}

		free(z0_index);
		free(amt0_index);

		free(data0);

	}

	for(i=1;i<Level;i++)
	{ 
		offset=0;
		for(j=0;j<box_cnt[i];j++)
		{
			int a=boxes[i][j].y2-boxes[i][j].y1;
			int b=boxes[i][j].x2-boxes[i][j].x1;
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
	printf("Zordering: %f\n", total_t  );

	start_t=clock();

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			fwrite(&trees[i][j].val,sizeof(double),1,fp);
			trees[i][j].flag=1;
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
	printf("Zordering I/O: %f\n", total_t  );


	fclose(fp);




}



void leveldata_row_zordering_level(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{
	clock_t start_t, end_t; double total_t;

	start_t = clock();
	int i,j,k;
	char filename[50];
	sprintf(filename,"Level_row_zordering_levelreordering.dat");
	FILE *fp=fopen(filename,"w");


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

	struct node * data0=malloc(cnt[0]*sizeof(struct node));

	for(i=0;i<1;i++)

	{
		offset=0;
		for(k=-1000;k<3000;k++)

			for(j=0;j<cnt[i];j++)
			{

				if(data[i][j].a==k)  
					//		if(data[i][j].b==k)
				{

					data0[offset].x=data[i][j].a;
					data0[offset].y=data[i][j].b;
					data0[offset].val=data[i][j].val;
					data0[offset].flag=0;
					data0[offset].fchild=NULL;
					data0[offset].next=NULL;
					offset++;
				}
			}
		//        printf("offset: %d,%d\n",cnt[i],offset);
	}




	int max_x=0;
	int max_y=0;
	for(i=0;i<1;i++)
	{

		for(j=0;j<cnt[i];j++)
		{


			if(data[i][j].a>max_x)
				max_x=data[i][j].a;
			if(data[i][j].b>max_y)
				max_y=data[i][j].b;



		}
		// printf("offset: %d,%d\n",cnt[i],offset);

		int z0_size= EncodeMorton2(max_x,max_y)+1;
		//printf("%d,%d,%d\n",a,b,z_size);
		int *z0_index=malloc(z0_size*sizeof(int));
		//memset (z_index,-1,z_size*sizeof(int));
		for(k=0;k<z0_size;k++){

			z0_index[k]=-1;
		}

		int box0_size=(max_x+1)*(max_y+1);
		//printf("cnt[0], box0_size: %d,%d,%d\n",cnt[0],z0_size,box0_size);
		for(int m=0;m<=max_y;m++)
			for(int l=0;l<=max_x;l++)
			{
				z0_index[EncodeMorton2(l,m)]=l+m*(max_x+1);
			}
		int *amt0_index=malloc(box0_size*sizeof(int));
		int tr0=0;
		for(k=0;k<z0_size;k++){
			if(z0_index[k]!=-1)
				amt0_index[tr0++]=z0_index[k];
		}
		if(tr0!=box0_size){
			printf("tr!=box_size, %d, %d\n",tr0,box0_size);
			for (k=0;k<box0_size;k++)
				printf("%d ",amt0_index[k]);
		}
		for(k=0;k<box0_size;k++)
		{
			trees[i][k].x=data0[amt0_index[k]].x;
			trees[i][k].y=data0[amt0_index[k]].y;
			trees[i][k].val=data0[amt0_index[k]].val;
			trees[i][k].flag=0;
			trees[i][k].fchild=NULL;
			trees[i][k].next=NULL;
		}

		free(z0_index);
		free(amt0_index);

		free(data0);

	}

	for(i=1;i<Level;i++)
	{ 
		offset=0;
		for(j=0;j<box_cnt[i];j++)
		{
			int a=boxes[i][j].y2-boxes[i][j].y1;
			int b=boxes[i][j].x2-boxes[i][j].x1;
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
	printf("Zordering+level, zordering: %f\n", total_t  );

	start_t=clock();


	int ** mapping;
	mapping=malloc(Level*sizeof(* mapping));
	for(i=0;i<Level;i++)
		mapping[i]=malloc(cnt[i]*sizeof(int));




	for(i=Level-1;i>0;i--)
		for(j=0;j<cnt[i];j++)
		{


			int a=(int)trees[i][j].x/2;

			int b=(int)trees[i][j].y/2;
			mapping[i][j]=find_father(trees[i-1],cnt[i-1],a,b);
		}


	end_t = clock();

	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Zordering+level, mapping: %f\n", total_t  );

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
	end_t = clock();

	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Zordering+level, build up trees: %f\n", total_t  );

	start_t=clock();

	for(i=0;i<1;i++)
		for(j=0;j<cnt[i];j++)
		{
			struct  node *p=&trees[i][j];
			PrintTree(p,fp);

		}
	end_t = clock();

	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Zordering+level, travel trees: %f\n", total_t  );

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			if(trees[i][j].flag==0)                      
				printf("Not visit %d,%d\n",i,j);

		}
	fclose(fp);
	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);





	for(i=0;i<Level;i++)
		free(mapping[i]);
	free(mapping);

}

void leveldata_box_zordering(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level],int col)
{
	clock_t start_t, end_t, total_t;

	start_t = clock();
	int i,j,k;
	char filename[50];
	sprintf(filename,"Level_box_zordering_%d.dat",col);
	FILE *fp=fopen(filename,"w");

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
	for(i=0;i<Level;i++)
	{ 
		offset=0;
		for(j=0;j<box_cnt[i];j++)
		{
			int a=boxes[i][j].y2-boxes[i][j].y1;
			int b=boxes[i][j].x2-boxes[i][j].x1;
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
	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			fwrite(&trees[i][j].val,sizeof(double),1,fp);
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

	fclose(fp);
}



void leveldata_box_zordering_level(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level],int col)
{
	clock_t start_t, end_t, total_t;

	start_t = clock();
	int i,j,k;
	char filename[50];
	sprintf(filename,"Level_box_zordering_levelreordering_%d.dat",col);
	FILE *fp=fopen(filename,"w");
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
	for(i=0;i<Level;i++)
	{ 
		offset=0;
		for(j=0;j<box_cnt[i];j++)
		{
			int a=boxes[i][j].y2-boxes[i][j].y1;
			int b=boxes[i][j].x2-boxes[i][j].x1;
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

			offset+=box_size;
			free(z_index);
			free(amt_index);
		}

	}

	int ** mapping;
	mapping=malloc(Level*sizeof(* mapping));
	for(i=0;i<Level;i++)
		mapping[i]=malloc(cnt[i]*sizeof(int));
	for(i=Level-1;i>0;i--)
		for(j=0;j<cnt[i];j++)
		{


			int a=(int)trees[i][j].x/2;

			int b=(int)trees[i][j].y/2;
			mapping[i][j]=find_father(trees[i-1],cnt[i-1],a,b);
		}


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

	for(i=0;i<1;i++)
		for(j=0;j<cnt[i];j++)
		{
			struct  node *p=&trees[i][j];
			PrintTree(p,fp);

		}


	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			if(trees[i][j].flag==0)                      
				printf("Not visit %d,%d\n",i,j);

		}
	fclose(fp);
	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);
	for(i=0;i<Level;i++)
		free(mapping[i]);
	free(mapping);

}




int main()
{
	int i,j,cnt[Level],box_cnt[Level];
	struct datapoint** data;
	data=malloc(Level*sizeof(* data)); 
	struct box** boxes;
	boxes=malloc(Level*sizeof(* boxes));
	for(int col=0;col<18;col++){
		char filename[50];
		sprintf(filename,"datapoint_%d",col);


		FILE *fp=fopen(filename,"r");

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


		//       leveldata_row(data,cnt,boxes,box_cnt);
		//	leveldata_row_level(data,cnt,boxes,box_cnt);
		//leveldata_box(data,cnt,boxes,box_cnt,col);
		//leveldata_box_level(data,cnt,boxes,box_cnt,col);
		//	leveldata_row_zordering(data,cnt,boxes,box_cnt);
		//	leveldata_row_zordering_level(data,cnt,boxes,box_cnt);
		leveldata_box_zordering(data,cnt,boxes,box_cnt,col);
		//leveldata_box_zordering_level(data,cnt,boxes,box_cnt,col);
		for(i=0;i<Level;i++)	
			free(data[i]);
		for(i=0;i<Level;i++)
			free(boxes[i]);
		//	free(boxes);
		//	free(data);
	}
	return 1;
}
