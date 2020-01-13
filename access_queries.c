#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define Level 5
struct node_storage* fp_glob;
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
	int lvl;
	struct node *fchild;
	struct node *next;
};


struct node_storage{
	int x,y;
	int lvl;
	double val;
	int flag;
	int flag_block;
};
void PrintTree(struct node* p)
{
	if (p==NULL) 
		return;
	fp_glob->val=p->val;
	fp_glob->x=p->x;
	fp_glob->y=p->y;
	fp_glob->lvl=p->lvl;
	fp_glob->flag=0;
	fp_glob->flag_block=0;       
	//fp=fp+sizeof(struct node_storage);
	fp_glob++;
	//   printf("fp:%ld\n",fp_glob);
	p->flag=1;
	//	p->flag=1; 
	//  printf("%d\n",p->flag);
	if (p->fchild!=NULL) 
	{ PrintTree(p->fchild);}
	if (p->next!=NULL)
	{ PrintTree(p->next); } 


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


struct node_storage * leveldata_box(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
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
	struct node_storage*dataArray=malloc(datasize*sizeof(struct node_storage));
	int offset=0;

	/*	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{

		trees[i][j].x=data[i][j].a;
		trees[i][j].y=data[i][j].b;
		trees[i][j].val=data[i][j].val;
		trees[i][j].flag=1;
		trees[i][j].fchild=NULL;
		trees[i][j].next=NULL;
		trees[i][j].lvl=i;


		}*/
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Initial: %lf\n", total_t  );
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
				trees[i][offset+k].flag=0;
				trees[i][offset+k].fchild=NULL;
				trees[i][offset+k].next=NULL;
				trees[i][offset+k].lvl=i;
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
			dataArray[offset1].val=trees[i][j].val;
			dataArray[offset1].x=trees[i][j].x;
			dataArray[offset1].y=trees[i][j].y;
			dataArray[offset1].lvl=i;
			trees[i][j].flag=1;
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

	//	free(dataArray);
	return dataArray;
}



struct node_storage* leveldata_box_level(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
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
	struct node_storage*dataArray=malloc(datasize*sizeof(struct node_storage));

	int offset=0;

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Level_initial: %lf\n", total_t  );
	start_t=clock();
	/*
	   for(i=0;i<Level;i++)
	   for(j=0;j<cnt[i];j++)
	   {

	   trees[i][j].x=data[i][j].a;
	   trees[i][j].y=data[i][j].b;
	   trees[i][j].val=data[i][j].val;
	   trees[i][j].flag=1;
	   trees[i][j].fchild=NULL;
	   trees[i][j].next=NULL;


	   }*/
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Initial: %lf\n", total_t  );
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
				trees[i][offset+k].flag=0;
				trees[i][offset+k].fchild=NULL;
				trees[i][offset+k].next=NULL;
				trees[i][offset+k].lvl=i;
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
	fp_glob=dataArray;
	for(i=0;i<1;i++)
		for(j=0;j<cnt[i];j++)
		{
			struct  node *p=&trees[i][j];
			PrintTree(p);

		}

	//printf("vp:%ld,%ld\n",dataArray,fp_glob-dataArray);
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
	//free(dataArray);
	return dataArray;

}

int checkinclude(struct node_storage point, struct box *inq){
	int x=point.x>>point.lvl;
	int y=point.y>>point.lvl;
	//int x=point.x;
	//int y=point.y;
	//printf("%d,%d\n",x,y);
	if(x<inq->x1)
		return 0;
	if(x>inq->x2)
		return 0;
	if(y<inq->y1)
		return 0;
	if(y>inq->y2)
		return 0;
	return 1;

}

void pattern_box(struct node_storage *data, int cnt [Level],struct box *inq){
	//	printf("%d,%d,%d,%d\n",inq->x1,inq->x2,inq->y1,inq->y2);
	int i,j;
	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	int cnt1=0;
	for(i=0;i<datasize;i++)
	{

		if (checkinclude(data[i],inq))
		{
			data[i].flag=1;
			cnt1++;
		}
	}
	printf("%d ",cnt1);
}

int checkinclude_s(struct node_storage point, struct box *inq,int lev){
	if(point.lvl!=lev)
		return 0;
	int x=point.x;
	int y=point.y;
	//int x=point.x;
	//int y=point.y;
	//printf("%d,%d\n",x,y);
	if(x<inq->x1)
		return 0;
	if(x>inq->x2)
		return 0;
	if(y<inq->y1)
		return 0;
	if(y>inq->y2)
		return 0;
	return 1;

}

void pattern_box_s(struct node_storage *data, int cnt [Level],struct box *inq,int lev){
	//      printf("%d,%d,%d,%d\n",inq->x1,inq->x2,inq->y1,inq->y2);
	int i,j;
	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	int cnt1=0;
	for(i=0;i<datasize;i++)
	{

		if (checkinclude_s(data[i],inq,lev))
		{
			data[i].flag=1;
			cnt1++;
		}
	}
	printf("%d ",cnt1);
}



void flag_block_c(struct node_storage *data, int cnt [Level]){
	//      printf("%d,%d,%d,%d\n",inq->x1,inq->x2,inq->y1,inq->y2);
	int i,j;
	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	int cnt1=0;
	for(i=0;i<datasize;i++)
	{

		if (data[i].flag==1)
		{
			for(j=i-3;j<i+4;j++)
			{
				if(j>=0&&j<datasize)
					data[j].flag_block=1;

			}
		}
	}

	for(i=0;i<datasize;i++)
	{

		if (data[i].flag_block==1)
			cnt1++;
	}
	printf("%d ",cnt1);

}

void flag_block_init(struct node_storage *data, int cnt [Level]){
	//      printf("%d,%d,%d,%d\n",inq->x1,inq->x2,inq->y1,inq->y2);
	int i,j;
	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	int cnt1=0;
	for(i=0;i<datasize;i++)
	{
		data[i].flag=0;
		data[i].flag_block=0;
	}


}


int main()
{
	int i,j,cnt[Level],box_cnt[Level];
	struct datapoint** data;
	data=malloc(Level*sizeof(* data)); 
	struct box** boxes;
	boxes=malloc(Level*sizeof(* boxes));




	FILE *fp=fopen("datapoint_noghost.info","r");
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
	init_mapping(data,cnt,boxes,box_cnt);
	//	leveldata_box(data,cnt,boxes,box_cnt);

	struct node_storage* s_data;
	struct node_storage* s_data1;
	s_data=leveldata_box(data,cnt,boxes,box_cnt);
	s_data1=leveldata_box_level(data,cnt,boxes,box_cnt);


	//	struct box *inq=malloc(sizeof(struct box));

	struct box *inq;
	for(i=0;i<box_cnt[2];i++){
		inq=&boxes[2][i];
		inq->x1=inq->x1>>2;
		inq->y1=inq->y1>>2;
		inq->x2=inq->x2>>2;
		inq->y2=inq->y2>>2;

		pattern_box(s_data,cnt,inq);
		flag_block_c(s_data,cnt);
		flag_block_init(s_data,cnt);       

		pattern_box(s_data1,cnt,inq);
		flag_block_c(s_data1,cnt);
		flag_block_init(s_data1,cnt);
		printf("\n");
	}
	printf("row:\n");
	inq=malloc(sizeof(struct box));
	inq->x1=0;
	inq->x2=127;
	inq->y1=0;
	inq->y2=191;
	for(i=0;i<192;i++){
		inq->y1=i;
		inq->y2=i;
		pattern_box(s_data,cnt,inq);
		flag_block_c(s_data,cnt);
		flag_block_init(s_data,cnt);

		pattern_box(s_data1,cnt,inq);
		flag_block_c(s_data1,cnt);
		flag_block_init(s_data1,cnt);
		printf("\n");
	}

	printf("column:\n");
	inq=malloc(sizeof(struct box));
	inq->x1=0;
	inq->x2=0;
	inq->y1=0;
	inq->y2=191;
	for(i=0;i<128;i++){
		inq->x1=i;
		inq->x2=i;
		pattern_box(s_data,cnt,inq);
		flag_block_c(s_data,cnt);
		flag_block_init(s_data,cnt);

		pattern_box(s_data1,cnt,inq);
		flag_block_c(s_data1,cnt);
		flag_block_init(s_data1,cnt);
		printf("\n");
	}
	printf("Box:\n");

	for(i=0;i<box_cnt[4];i++){
		inq=&boxes[4][i];
		pattern_box_s(s_data,cnt,inq,4);
		flag_block_c(s_data,cnt);
		flag_block_init(s_data,cnt);

		pattern_box_s(s_data1,cnt,inq,4);
		flag_block_c(s_data1,cnt);
		flag_block_init(s_data1,cnt);
		printf("\n");
	}
	printf("row:\n");
	inq=malloc(sizeof(struct box));
	for(i=0;i<box_cnt[4];i++){
		inq->x1=(boxes[4][i].x1+boxes[4][i].x2)/2;
		inq->x2=boxes[4][i].x2;
		inq->y1=boxes[4][i].y1;
		inq->y2=boxes[4][i].y2;
		pattern_box_s(s_data,cnt,inq,4);
		flag_block_c(s_data,cnt);
		flag_block_init(s_data,cnt);

		pattern_box_s(s_data1,cnt,inq,4);
		flag_block_c(s_data1,cnt);
		flag_block_init(s_data1,cnt);
		printf("\n");
	}

	printf("column:\n");
	for(i=0;i<box_cnt[4];i++){
		inq->y1=(boxes[4][i].y1+boxes[4][i].y2)/2;
		inq->y2=boxes[4][i].y2;
		inq->x1=boxes[4][i].x1;
		inq->x2=boxes[4][i].x2;

		pattern_box_s(s_data,cnt,inq,4);
		flag_block_c(s_data,cnt);
		flag_block_init(s_data,cnt);

		pattern_box_s(s_data1,cnt,inq,4);
		flag_block_c(s_data1,cnt);
		flag_block_init(s_data1,cnt);
		printf("\n");
	}



	free(s_data);
	free(s_data1);


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
