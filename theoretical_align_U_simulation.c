#include<stdio.h>
#include<stdlib.h>
int main()
{
    //Declaration of variables
    double t=0,t_avl=0,U_sim=0;
    double time[500]={0};
    double surv_frac_sim[500]={0};
    double t_prev=0,loop=0,time_add=0;

    FILE *fp=fopen("time_U_0.01_new.txt","r");
    FILE *fp2=fopen("time_U_0.01_trunc.txt","w");
    /*Block of code align the data of U for numerically solving equation with the time of U for simulation data.*/
    while(2)
    {
        fscanf(fp,"%lf %lf %lf\n",&t_avl,&t,&U_sim);
        if(t_avl<t_prev){time_add+=(t_prev);t_prev;loop++;}
        fprintf(fp2,"%lf %lf\n",t_avl+time_add,U_sim);
        t_prev=t_avl;
        if(feof(fp))break;
    }

}
