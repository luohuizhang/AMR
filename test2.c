#include <stdio.h>
#include <stdlib.h>
struct datapoint{
	int a,b;
	double val;
};

void stat(struct datapoint **data, int cnt [6],int li, int mid,int hi)
{
	int com_cnt=0;
	int i,j,k;
       FILE *fp1,*fp2,*fp3;
       fp1=fopen("level_data_1","w");
       fp2=fopen("level_data_2","w");
       fp3=fopen("level_data_3","w");
	printf("count= %d %d %d\n", cnt[li],cnt[mid],cnt[hi]);
	for(i=0;i<cnt[li];i++)
		for(j=0;j<cnt[mid];j++)
			if(data[li][i].a==data[mid][j].a&&data[li][i].b==data[mid][j].b)
				for(k=0;k<cnt[hi];k++)
				{
					if(data[li][i].a==data[mid][j].a&&data[li][i].b==data[mid][j].b&&data[li][i].a==data[hi][k].a&&data[li][i].b==data[hi][k].b)
					{

						printf("%d %d %lf %lf %lf\n", data[li][i].a,data[li][i].b,data[li][i].val,data[mid][j].val,data[hi][k].val);
                                                fwrite(&data[li][i].val,sizeof(double),1,fp1); 
                                                fwrite(&data[mid][j].val,sizeof(double),1,fp2); 
                                                fwrite(&data[hi][k].val,sizeof(double),1,fp3); 
						com_cnt++;
					}
				}

	printf("com_cnt= %d\n", com_cnt);
        fclose(fp1);
        fclose(fp2);
        fclose(fp3);
}

int main()
{
	int i,j,cnt[6];
	struct datapoint** data;
	data=malloc(6*sizeof(* data)); 
	FILE *fp=fopen("datapoint.dat","r");
	for(i=0;i<6;i++)
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
//	int	li=0,mid=1,hi=2;
//	stat(data,cnt,li,mid,hi);
int	li=3,mid=4,hi=5;
	stat(data,cnt,li,mid,hi);
	for(i=0;i<6;i++)	
		free(data[i]);
	free(data);
	return 1;
}
