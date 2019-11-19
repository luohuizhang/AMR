#include <stdio.h>
#include <stdlib.h>
#define Level 5 
struct datapoint{
	int a,b;
	double val;
};

void stat(struct datapoint **data, int cnt [Level],int li, int mid,int hi)
{
	int com_cnt=0;
	int i,j,k; double delta;
	printf("count= %d %d\n", cnt[li],cnt[hi]);
	char filename[50];
	sprintf(filename,"delta_%d_%d_%d",li,mid,hi);
	FILE *fp=fopen(filename,"w");
	for(k=0;k<cnt[hi];k++)
	{
		for(j=0;j<cnt[mid];j++)
			if(data[mid][j].a==data[hi][k].a/2&&data[mid][j].b==data[hi][k].b/2)
				break;

		for(i=0;i<cnt[li];i++)
			if(data[li][i].a==data[mid][j].a/2&&data[li][i].b==data[mid][j].b/2)

				break;
		if(j>=cnt[mid]||i>=cnt[li])
		{
			printf("Cannot find the position of Level i+1 from Level i\n");
			exit(0);
		}

		//      printf("%d %d %lf %lf %lf\n", data[hi][k].a,data[hi][k].b,data[li][i].val,data[mid][j].val,data[hi][k].val);
		delta=2*data[mid][j].val-data[li][i].val-data[hi][k].val;
		//delta=data[li][i].val-data[hi][k].val;
		if(abs(delta)>abs(0.5*data[hi][k].val))
			delta=0.5*data[hi][k].val;
		fwrite(&delta,sizeof(double),1,fp);
		com_cnt++;



	}
	printf("com_cnt= %d\n", com_cnt);
	fclose(fp);
}
void leveldata(struct datapoint **data, int cnt [Level])
{
	int i,j; 
	for(i=0;i<Level;i++)
	{
		char filename[50];
		sprintf(filename,"Level_%d.dat",i);
		FILE *fp=fopen(filename,"w");
		for(j=0;j<cnt[i];j++)
		{
			fwrite(&data[i][j].val,sizeof(double),1,fp);
		}

		fclose(fp);
	}
}
int main()
{
	int i,j,cnt[Level];
	struct datapoint** data;
	data=malloc(Level*sizeof(* data)); 
	FILE *fp=fopen("datapoint.dat","r");
	for(i=0;i<Level;i++)
	{
		fread(&cnt[i],sizeof(int),1,fp);
		printf("count= %d\n", cnt[i]);
		data[i]=malloc(cnt[i]*sizeof(struct datapoint));
		fread(data[i],sizeof(struct datapoint),cnt[i],fp);
		//		for(j=0;j<cnt[i];j++)
		//			printf("%d %d %lf\n", data[i][j].a,data[i][j].b,data[i][j].val);
	}
	fclose(fp);
	//	int li=0,hi=1;
	//	stat(data,cnt,li,hi);
	//	li=0,hi=2;
	//	stat(data,cnt,li,hi);
	//	li=1,hi=2;
	//	stat(data,cnt,li,hi);
	//	int	li=3,hi=4;
	//	stat(data,cnt,li,hi);
	//	li=3,hi=5;
	//	stat(data,cnt,li,hi);
	for(i=0;i<Level-2;i++)
		stat(data,cnt,i,i+1,i+2);
	//      leveldata(data,cnt);
	for(i=0;i<Level;i++)	
		free(data[i]);
	free(data);
	return 1;
}
