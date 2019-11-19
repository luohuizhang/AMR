#include <stdio.h>
#include <stdlib.h>
#define Level 5 
struct datapoint{
	int a,b;
	double val;
};
struct box{
int x1,y1;
int x2,y2;

};
void stat(struct datapoint **data, int cnt [Level],int li, int hi)
{
	int com_cnt=0;
	int i,j; double delta;
	printf("count= %d %d\n", cnt[li],cnt[hi]);
	char filename[50];
	sprintf(filename,"Mapping_%d_%d",li,hi);
	FILE *fp=fopen(filename,"w");
	for(j=0;j<cnt[hi];j++)
		for(i=0;i<cnt[li];i++)
		{
			if(data[li][i].a==data[hi][j].a/2&&data[li][i].b==data[hi][j].b/2)
			{
				//printf("%d %d %lf, %d %d %lf\n", data[li][i].a,data[li][i].b,data[li][i].val,data[hi][j].a,data[hi][j].b,data[hi][j].val);
				fwrite(&i,sizeof(int),1,fp);

				com_cnt++;
				break;
			}
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

/*int main()
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
		//for(j=0;j<cnt[i];j++)
			//printf("%d %d %lf\n", data[i][j].a,data[i][j].b,data[i][j].val);
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
	//	leveldata(data,cnt);
	for(i=0;i<Level;i++)	
		free(data[i]);
	free(data);
	return 1;
}
*/
int main()
{
        int i,j,cnt[Level],box_cnt[Level];
        struct datapoint** data;
        data=malloc(Level*sizeof(* data));
        struct box** boxes;
        boxes=malloc(Level*sizeof(* boxes));

        FILE *fp=fopen("datapoint.dat","r");

        for(i=0;i<Level;i++)
        {
                fread(&cnt[i],sizeof(int),1,fp);
                printf("data count= %d\n", cnt[i]);
                //fread(&box_cnt[i],sizeof(int),1,fp);
                //printf("box_cnt= %d\n", box_cnt[i]);
                //boxes[i]=malloc(box_cnt[i]*sizeof(struct box));
                //fread(boxes[i],sizeof(struct box),box_cnt[i],fp);
                data[i]=malloc(cnt[i]*sizeof(struct datapoint));
                fread(data[i],sizeof(struct datapoint),cnt[i],fp);
                //for(j=0;j<cnt[i];j++)
                //      printf("%d %d %lf\n", data[i][j].a,data[i][j].b,data[i][j].val);
        }
        fclose(fp);
        //      leveldata_box(data,cnt);
        //      leveldata_row(data,cnt);

        //      leveldata_row(data,cnt,boxes,box_cnt);
        //      leveldata_row_level(data,cnt,boxes,box_cnt);
        //      leveldata_box(data,cnt,boxes,box_cnt);
//     leveldata_box_level(data,cnt,boxes,box_cnt);
        //      leveldata_row_zordering(data,cnt,boxes,box_cnt);
        //      leveldata_row_zordering_level(data,cnt,boxes,box_cnt);
        //      leveldata_box_zordering(data,cnt,boxes,box_cnt);
        //      leveldata_box_zordering_level(data,cnt,boxes,box_cnt);
 for(i=0;i<Level-1;i++)
                stat(data,cnt,i,i+1);

        for(i=0;i<Level;i++)
                free(data[i]);
        //for(i=0;i<Level;i++)
          //      free(boxes[i]);
        free(boxes);
        free(data);
        return 1;
}

