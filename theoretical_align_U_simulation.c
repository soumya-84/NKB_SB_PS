#include<stdio.h>
#include<stdlib.h>
int main()
{
double t=0,t_avl=0,U_sim=0;
    double time[500]={0};
    double surv_frac_sim[500]={0};
    double t_prev=0,loop=0,time_add=0;

    FILE *fp=fopen("time_U2_0.01_new.txt","r");
    FILE *fp2=fopen("time_U2_0.01_trunc.txt","w");
    while(2)
{
    fscanf(fp,"%lf %lf %lf\n",&t_avl,&t,&U_sim);
    if(t_avl<t_prev){time_add+=(t_prev);t_prev;printf("%lf final time is %lf,time add is %lf\n",loop,t_prev,time_add);loop++;}
    fprintf(fp2,"%lf %lf\n",t_avl+time_add,U_sim);
    t_prev=t_avl;




    if(feof(fp))break;
}

}
