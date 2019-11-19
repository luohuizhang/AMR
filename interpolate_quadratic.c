#include <stdio.h>
#include <stdlib.h>
#define Level 5 
struct datapoint{
	int a,b;
	double val;
};
double find(struct datapoint *data,int size,int a, int b)
{
	int i;
	for(i=0;i<size;i++)
		if(data[i].a==a&&data[i].b==b)
			return data[i].val;
	printf("do not find (%d,%d)\n",a,b);
	return -1;
}

void stat(struct datapoint **data, int cnt [Level],int li, int mid,int hi,int hh)
{
	int com_cnt=0;
	int i,j,k,l; double delta;
	char filename[50];
	sprintf(filename,"new_delta_%d_%d_%d_%d",li,mid,hi,hh);
	FILE *fp=fopen(filename,"w");
	for(l=0;l<cnt[hh];l++)
	{
		for(k=0;k<cnt[hi];k++)
			if(data[hi][k].a==data[hh][l].a/2&&data[hi][k].b==data[hh][l].b/2)

			{
				break;
			}

		for(j=0;k<cnt[mid];j++)
			if(data[mid][j].a==data[hh][l].a/4&&data[mid][j].b==data[hh][l].b/4)

			{
				break;
			}

		for(i=0;i<cnt[li];i++)
			if(data[li][i].a==data[hh][l].a/8&&data[li][i].b==data[hh][l].b/8)

			{
				break;
			}

		if(k>=cnt[hi]||j>=cnt[mid]||i>=cnt[li])
		{
			printf("Cannot find the position of Level i+1 from Level i\n");
			exit(0);
		}
		//	printf("%d %d %lf %lf %lf\n", data[hi][k].a,data[hi][k].b,data[li][i].val,data[mid][j].val,data[hi][k].val);
		int x,y;
		double t1,t2,t3,t4;
		x=data[hh][l].a%2;
		y=data[hh][l].b%2;
		t1=data[hi][k].val;
		t2=data[hi][k].val;
		if(x!=0)
			t2=find(data[hi],cnt[hi],data[hi][k].a+1,data[hi][k].b);
		t3=data[hi][k].val;
		if(x!=0&&y!=0)
			t3=find(data[hi],cnt[hi],data[hi][k].a+1,data[hi][k].b+1);
		t4=data[hi][k].val;
		if(y!=0)
			t4=find(data[hi],cnt[hi],data[hi][k].a,data[hi][k].b+1);
		double temp1=t1+(t4-t1)*y/2;
		double temp2=t2+(t3-t2)*y/2;
		double val1=temp1+(temp2-temp1)*x/2;

		x=data[hh][l].a%4;
		y=data[hh][l].b%4;

		t1=data[mid][j].val;
		t2=data[mid][j].val;
		if(x!=0)
			t2=find(data[mid],cnt[mid],data[mid][j].a+1,data[mid][j].b);
		t3=data[mid][j].val;
		if(x!=0&&y!=0)
			t3=find(data[mid],cnt[mid],data[mid][j].a+1,data[mid][j].b+1);
		t4=data[mid][j].val;
		if(y!=0)
			t4=find(data[mid],cnt[mid],data[mid][j].a,data[mid][j].b+1);
		temp1=t1+(t4-t1)*y/4;
		temp2=t2+(t3-t2)*y/4;
		double val2=temp1+(temp2-temp1)*x/4;


		x=data[hh][l].a%8;
		y=data[hh][l].b%8;

		t1=data[li][i].val;
		t2=data[li][i].val;
		if(x!=0)
			t2=find(data[li],cnt[li],data[li][i].a+1,data[li][i].b);
		t3=data[li][i].val;
		if(x!=0&&y!=0)
			t3=find(data[li],cnt[li],data[li][i].a+1,data[li][i].b+1);
		t4=data[li][i].val;
		if(y!=0)
			t4=find(data[li],cnt[li],data[li][i].a,data[li][i].b+1);
		temp1=t1+(t4-t1)*y/8;
		temp2=t2+(t3-t2)*y/8;
		double val3=temp1+(temp2-temp1)*x/8;
		delta=3*val1-3*val2+val3-data[hh][l].val;
		//delta=data[li][i].val-data[hi][k].val;
		if(abs(delta)>abs(0.2*data[hh][l].val))
		delta=0.2*data[hh][l].val;
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
	for(i=0;i<Level-3;i++)
		stat(data,cnt,i,i+1,i+2,i+3);
	//      leveldata(data,cnt);
	for(i=0;i<Level;i++)	
		free(data[i]);
	free(data);
	return 1;
}
