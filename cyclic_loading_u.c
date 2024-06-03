#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{


    double t_ser=0,t_avl=0,U_sim=0;
    double time[500]={0};
    double surv_frac_sim[500]={0};
    double t_prev=0,loop=0;
    FILE *fp2=fopen("L=100000_time_simulation_U_0.01.txt","r");
    while(2)
{
    fscanf(fp2,"%lf %lf %lf\n",&t_ser,&t_avl,&U_sim);
    if(t_avl<t_prev){time[(int)loop]=t_prev;printf("%lf final time is %lf\n",loop,t_prev);loop++;}
    t_prev=t_avl;




    if(feof(fp2))break;
}




double a=0;double b=0,c=1;
double U=1,t=0;
double time_U_prev=0;
double U_step[50000]={0};
FILE *fp = fopen("time_U_0.01_new.txt","w");
double sigma_L=0;
double sigma_R=1;
double sigma=0.01;
double load=0;
int i=0;
U=1;
//int i =0;
for( i=0;i<1000;i++)
{c=1;
     for(int n=0;n<i;n++)
    {
        c=c*U_step[n];
    }load+=(c*0.01);printf("\nU%lf",U);

    if(i>0)
    {
    sigma_L=(sigma/(U));/*printf("sigma_L is %lf\n",sigma_L)*/
    sigma=(sigma/(U)) +0.01;printf("sigma is %lf\n",sigma);
    t=0;a=0;b=0;
    }

printf("\n%d----U-%lf,load-%lf\n",i,U,sigma*c);
printf("[%lf,%lf]-%lf,critical%lf\n\n",sigma_L,sigma_R,sigma,sigma_R*sigma_R/(4*(sigma_R-sigma_L)));

if((sigma)>sigma_R*sigma_R/(4*(sigma_R-sigma_L))){printf("hi_________");break;}
    for( U=1;U>0.1;U-=0.00001)
    {   double A=sigma_R-sigma_L;
        double B=sigma_R/(sigma_R-sigma_L);
        double C=sigma/(sigma_R-sigma_L);

        double D=log(fabs((U*U)*A-(sigma_R*U)+sigma));
        double E = ( ( B/(2*sqrt((B*B/4)-C)))*log(fabs((2*U-B-2*(sqrt((B*B/4)-C)))))) - ( ( B/(2*sqrt((B*B/4)-C)))*log(fabs((2*U-B+2*(sqrt((B*B/4)-C))))));
        double F=log(fabs(A-(sigma_R)+sigma));
        double G = ((B/(2*sqrt((B*B/4)-C)))*log(fabs((2-B-2*(sqrt((B*B/4)-C)))))) - ((B/(2*sqrt((B*B/4)-C)))*log(fabs((2-B+2*(sqrt((B*B/4)-C))))));

        t=-0.5*(D+E-F-G);

        a=t;
        if(b<a)
        {
        if(time[i]>t)
        {fprintf(fp,"%0.15lf %0.15lf %0.15lf\n",t,t+time_U_prev,U*c);
        }

        else{if(b!=0){break;}}
        b=a;

        t=0;A=0;B=0;C=0;D=0;E=0;F=0;G=0;
    }c=U;U_step[i]=U;time_U_prev+=b;printf("time is %lf c is %lf ",t,c);

}
printf("applied load is %lf",load);
}
