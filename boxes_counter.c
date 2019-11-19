#include <stdio.h>
#include <stdlib.h>
#define Level 5 
struct datapoint{
	int a,b;
	double val;
};

void stat(struct datapoint **data, int cnt [Level],int li, int hi)
{
	int com_cnt=0;
	int i,j; 
	//printf("count= %d %d\n", cnt[li],cnt[hi]);
	char filename[50];
	sprintf(filename,"delta_%d_%d",li,hi);
	FILE *fp=fopen(filename,"w");
	for(i=0;i<cnt[li];i++)
		for(j=0;j<cnt[hi];j++)
		{
			if(data[li][i].a==data[hi][j].a/2&&data[li][i].b==data[hi][j].b/2)
			{
				com_cnt++;
				break;
			}
		}

	printf("boxes ratio= %f\n", ((double)com_cnt)/cnt[li]);
	fclose(fp);
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
	for(i=0;i<Level-1;i++)
		stat(data,cnt,i,i+1);
	//        leveldata(data,cnt);
	for(i=0;i<Level;i++)	
		free(data[i]);
	free(data);
	return 1;
}
