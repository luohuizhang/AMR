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


double find(struct datapoint *data,int size,int a, int b)
{
	int i;
	for(i=0;i<size;i++)
		if(data[i].a==a&&data[i].b==b)
			return data[i].val;
	printf("do not find (%d,%d)\n",a,b);
	return -1;
}

void leveldata_box(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level],int col)
{
	//clock_t start_t, end_t; double total_t;

	//start_t = clock();
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
	//end_t = clock();

	//total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	//printf("Row-major: %f\n", total_t  );
}

void constant(struct datapoint **data, int cnt [Level],int col)
{
	int i,j,i1; double delta;
	for(i1=0;i1<Level-1;i1++)
	{
		int com_cnt=0;
		int li=i1;
		int hi=li+1;
		printf("count= %d %d\n", cnt[li],cnt[hi]);
		char filename[50];
		sprintf(filename,"delta_%d_%d.dat_%d",li,hi,col);
		FILE *fp=fopen(filename,"w");

		for(j=0;j<cnt[hi];j++)
			for(i=0;i<cnt[li];i++)
			{
				if(data[li][i].a==data[hi][j].a/2&&data[li][i].b==data[hi][j].b/2)
				{
					//	printf("%d %d %lf, %d %d %lf\n", data[li][i].a,data[li][i].b,data[li][i].val,data[hi][j].a,data[hi][j].b,data[hi][j].val);
					int x,y;
					x=data[hi][j].a%2;
					y=data[hi][j].b%2;
					double t1=data[li][i].val;
					double t2=data[li][i].val;
					if(x!=0)
						t2=find(data[li],cnt[li],data[li][i].a+1,data[li][i].b);
					double t3=data[li][i].val;
					if(x!=0&&y!=0)
						t3=find(data[li],cnt[li],data[li][i].a+1,data[li][i].b+1);

					double t4=data[li][i].val;
					if(y!=0)
						t4=find(data[li],cnt[li],data[li][i].a,data[li][i].b+1);
					double temp1=t1+(t4-t1)*y/2;
					double temp2=t2+(t3-t2)*y/2;
					double temp3=temp1+(temp2-temp1)*x/2;

					delta=data[hi][j].val-temp3;
					// if(abs(delta)>=abs(0.1*data[hi][j].val))
					//    delta=(0.1*data[hi][j].val);

					//if(abs(delta)<=abs(0.1*data[hi][j].val))
					{
						fwrite(&delta,sizeof(double),1,fp);
						com_cnt++;
					}
					break;
				}
			}

		printf("com_cnt= %d\n", com_cnt);
		fclose(fp);
	}
}

void linear(struct datapoint **data, int cnt [Level],int col)
{
	int i,j,k,i1; double delta;
	for(i1=0;i1<Level-2;i1++)
	{
		int li=i1;
		int mid=li+1;
		int hi=mid+1; 
		int com_cnt=0;
		printf("count= %d %d\n", cnt[li],cnt[hi]);
		char filename[50];
		sprintf(filename,"delta_%d_%d_%d.dat_%d",li,mid,hi,col);
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
                //if(abs(delta)>abs(0.1*data[hi][k].val))
                //      delta=0.1*data[hi][k].val;
                fwrite(&delta,sizeof(double),1,fp);
                com_cnt++;



        }

		printf("com_cnt= %d\n", com_cnt);
		fclose(fp);
	}
}

void quadratic(struct datapoint **data, int cnt [Level],int col)
{
	int i,j,k,l, i1; double delta;
	for(i1=0;i1<Level-3;i1++)
	{
		int li=i1;
		int mid=li+1;
		int hi=mid+1;
		int hh=hi+1; 
		int com_cnt=0;
		char filename[50];
		sprintf(filename,"delta_%d_%d_%d_%d.dat_%d",li,mid,hi,hh,col);
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
			//	if(abs(delta)>abs(0.1*data[hh][l].val))
			//		delta=0.1*data[hh][l].val;
			fwrite(&delta,sizeof(double),1,fp);
			com_cnt++;

		}
		printf("com_cnt= %d\n", com_cnt);
		fclose(fp);
	}
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

		leveldata_box(data,cnt,boxes,box_cnt,col);


		constant(data,cnt,col);
		linear(data,cnt,col);
//		quadratic(data,cnt,col);


		for(i=0;i<Level;i++)	
			free(data[i]);
		for(i=0;i<Level;i++)
			free(boxes[i]);
		//	free(boxes);
		//	free(data);
	}
	return 1;


}
