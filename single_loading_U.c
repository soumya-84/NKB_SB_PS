#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define sigma 0.225

int main()
{
int preced_int=0;
double a=0;double b=0,c=0;
double U=0,t=0;
FILE *fp = fopen("time_UI.txt","w");
for(double U=1;U>0;U-=0.000001)
{
double A=log(fabs((U*U)-U+sigma));
double B=log(fabs( (2*U)-1-(2*(sqrt(0.25-sigma))) )) /(2*sqrt(0.25-sigma));
double C=log(fabs( (2*U)-1+(2*(sqrt(0.25-sigma))) )) /(2*sqrt(0.25-sigma));
double D=( log(fabs(1+(2*sqrt(0.25-sigma))))-log(fabs(1-(2*sqrt(0.25-sigma)))) )/(2*sqrt(0.25-sigma))-log(fabs(sigma));
t=-(0.5 * (A+B-C+D));

a=t;
if(b<a)
{
    if(t>=preced_int){
                    fprintf(fp,"%0.15lf %0.15lf\n",t,U);
                    preced_int=(int)t+1;
                    }
}
else{if(b!=0){break;}}
b=a;

/*
b=t;
c=b-a;
if(c==0){printf("time is %.15lf , u = %.15f  D= %0.15lf\n",t,U,D);}*/
//printf("time is %.15lf , u = %.15f  D= %0.15lf\n",t,U,D);
//fprintf(fp,"%0.15lf %0.15lf\n",t,U);
t=0;A=0;B=0;C=0;
}

}
