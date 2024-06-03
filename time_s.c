#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define sigma 0.01

int main()
{
    double t=0,U=0,t_prev=0,U_prev=1;int loop_count=0;

int time_base=0,time=0;
FILE *fp=fopen("input.txt","r");
FILE *fp2=fopen("output.txt","w");
while(2)
{
    fscanf(fp,"%lf %lf\n",&t,&U);
    //printf("%lf %lf\n",t,U);
    if(t>time_base)
    {
    fprintf(fp2,"%lf %lf\n",t,fabs(U-U_prev));
    t_prev=t;U_prev=U;
    printf("%d %lf %lf|\n",time_base,t,U);
    time_base=floor(t)+1;

    }

    if(feof(fp))break;
}


}
