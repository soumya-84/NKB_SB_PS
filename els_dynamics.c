/*code generating the simulation data for redistribution steps ELS*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"ran2.c"
#define system 25000

long sd=9862384731;
int main()
{

double thres[system]={0},load=0,load_bundle=0;
double min=0,load_redistribution_increment=0;
int broken=0,intact=0,min_pos=0,block_intact=0,avl_broken=0,event=0,w_max_event=0,limit_event_block=0,max=0,gr_broken=0;
int time_avl=0;
min=thres[0];
int i=0,j=0;
int iterations=5;
int count=0;
double lambda=1.5;
//FILE *fp=fopen("time_simulation_exponential_1000_1.txt","w");
FILE *fp=fopen("Output.txt","w");
for(j=0;j<iterations;j++)///averaging starts
{printf("iterations is %d\n",j);

load=0;load_bundle=0;min=0;load_redistribution_increment=0;broken=0;intact=0;block_intact=0;min_pos=0;avl_broken=0;event=0;gr_broken=0;


for( i=0;i<system;i++){thres[i]=ran2(&sd);/*printf("%lf||",thres[i]);*/}/*piece of code to choose threshold distribution*/

min=thres[0];
for( i=0;i<system;i++)
{//if(thres[i]==0){printf("minpos is %d",i);}
    if(thres[i]<min)
    {
        min=thres[i];
        min_pos=i;
    }
}

load=min;
intact=system;

while(2)//event_count
{///////printf("\navalanche started\n");

    event++;
    time_avl=0;
    avl_broken=0;
    load=min;

    load_bundle=load*intact;
    //fprintf(fp,"%lf(%d) ",load*intact/system,intact);
    while(broken<system)//redistribution
    {
        broken=0;intact=0;

        for( i=0;i<system;i++)
        {if(thres[i]>0)
           if(thres[i]<=load)
            {
            broken++;
            thres[i]=0;
            }else{intact++;}
        }
        time_avl++;

        //printf("%d %d\n",time_avl,broken);

        gr_broken+=broken;
        //printf("%d||",gr_broken);
        avl_broken+=broken;

        if(broken==0||intact==0){fprintf(fp,"%lf %d %d\n",load*intact/system,time_avl,broken);/*printf("broken condition executed");*/break;}
        //printf("%d %d %d\n",time_avl,avl_broken,gr_broken);
        load_redistribution_increment=0;
        load_redistribution_increment=(load*(double)broken)/(double)intact;
        //printf("load increment is %lf\n",load_redistribution_increment);
        load+=load_redistribution_increment;
        //printf("load redistribution check is %lf",load_bundle/(double)intact);
        {
          fprintf(fp,"%lf %d %d\n",load*intact/system,time_avl,broken);
        }

    }//load redistribution ends
//fprintf(fp2,"%d %d %d\n",event,avl_broken,time_avl);
        //if(event>=1)break;
        if(intact==0)break;

        min=2;
        for( i=0;i<system;i++)
        {
            if((thres[i]<min)&&thres[i]!=0)
            {
                min=thres[i];
                min_pos=i;
            }
        }

//printf("min_load is %lf",min);

        load=min;//quasi_static loading
        //load+=0.01;//Descrete loading

}//ending of each iteration


 }//averaging ends

fclose(fp);
//printf("gross broken is %d \n",gr_broken);

}
