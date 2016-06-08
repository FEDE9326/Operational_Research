#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "pq.h"
#include "random.h"
#include <math.h>
#include <time.h>

#define N 16
#define delta 4

int verify_constraints_delta(Graph G);
float extract(int m);


int main()
{
    Edge e1,e2;
    time_t t;
    Graph b1,b2;
    Graph tsd;
    Graph f,f1;

    int indice,k,step;
    int maxiter;
    int stop,n1,n2;
    float valp,valn,p,lambda,n,lambda2;


    tsd=GRAPHinit_tsd(N);


    printf("Generating Manhattan solution...\n");
    b1=GRAPHinitManhattan(N,delta,tsd);
    GRAPHprint(b1);
    FILE *fp;
    fp=fopen("3_4.txt","a+");
    f=GRAPHinit(N,0);
    GRAPHrouteTraffic(b1,tsd,f);
    e1=GRAPHmaxFlow(f);
    printf("Max flow at %d %d: %f\n",e1.v,e1.w,e1.cost);

    //stop=(float)sqrt(N);
    stop=N*(N-1);
    lambda=(double)N/10;
    lambda2=(double)N/200;
    printf("lambda=%f\n",lambda);


    printf("Improving the solution with Meathauristics approach...\n");
    indice=0;
    k=1;
    maxiter=N*N;

    b2=GRAPHinit(N,0);
    GRAPHcopy(b2,b1);


    do{
        n1=(int)uniform(0,N,&seed);
        n2=(int)uniform(0,N,&seed);
        exchangeNodes(b2,n1,n2);
        f1=GRAPHinit(N,0);
        GRAPHrouteTraffic(b2,tsd,f1);
        e2=GRAPHmaxFlow(f1);
        if(e2.cost<e1.cost){
            GRAPHcopy(b1,b2);
            GRAPHcopy(f,f1);
            EDGEcopy(&e1,&e2);
            //printf("Better solution %d %d %f\n",e1.v,e1.w,e1.cost);
            step=k;
            indice=0;
            fprintf(fp,"%f\n",e2.cost);
        }else{
            srand((unsigned)time(&t));
            //p=log(1-(float)(k+1)/maxiter)/(-lambda);
            valp=uniform(0,1,&seed);
            //valn=uniform(0,1,&seed);
            //valp=(float)rand()/RAND_MAX;
            valn=(float)rand()/RAND_MAX;
            p=log(1-valp)/(-lambda);
            n=log(1-valn)/(-lambda2*k);
            //printf("%d %d\n",k,maxiter);
            //printf("Per entrare %f>%f?\n",n,p);
            if(n>p){
                GRAPHcopy(b1,b2);
                GRAPHcopy(f,f1);

                //printf("Worst solution with p=%f %d %d %f\n",p,e2.v,e2.w,e2.cost);
                fprintf(fp,"%f\n",e2.cost);
            }else{
                indice++;
                fprintf(fp,"%f\n",e1.cost);
            }


        }
         k++;


    }while(indice<stop);

    printf("Best solution step %d with max flow at %d %d: %f\n",step,e1.v,e1.w,e1.cost);
    fclose(fp);

    GRAPHfree(f);
    GRAPHfree(b1);
    //GRAPHfree(b2);
    GRAPHfree(tsd);


    return 0;

}

/*float extract(int m){

    return lambda*exp((-lambda)*m);

}
*/










