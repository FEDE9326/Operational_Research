#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "pq.h"
#include "random.h"
#include <math.h>

#define N 16
#define delta 4
#define lambda 20


int verify_constraints_delta(Graph G);
float extract(int m);


int main()
{
    Edge e1,e2,*listEdges;

    Graph b1,b2;
    Graph tsd;
    Graph f,f1;

    int indice,k,step;
    int n,stop,n1,n2;
    float val,p;

    tsd=GRAPHinit_tsd(N);

    printf("Generating Manhattan solution...\n");
    b1=GRAPHinitManhattan(N,delta,tsd);
    GRAPHprint(b1);

    f=GRAPHinit(N,0);
    GRAPHrouteTraffic(b1,tsd,f);
    e1=GRAPHmaxFlow(f);
    printf("Max flow at %d %d: %f\n",e1.v,e1.w,e1.cost);

    //stop=(int)sqrt(N);
    stop=N;
    //Una volta che la constraint sui delta viene rispettata tenta di eliminare il più congestionato
    printf("Improving the solution with Meathauristics approach...\n");
    indice=0;
    k=0;

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
            printf("Better solution %d %d %f\n",e1.v,e1.w,e1.cost);
            step=k;
        }else{
            val=extract(k);
            printf("val=%f\n",val);
            p=1-exp((-lambda)*val);
            if(uniform01(&seed)<p){
                GRAPHcopy(b1,b2);
                GRAPHcopy(f,f1);

                printf("Worst solution with p=%f %d %d %f\n",p,e2.v,e2.w,e2.cost);
            }else{
                indice++;
            }
            k++;

        }

    }while(indice<stop);

    printf("Best solution step %d with max flow at %d %d: %f\n",step,e1.v,e1.w,e1.cost);


    GRAPHfree(f);
    GRAPHfree(b1);
    GRAPHfree(b2);
    GRAPHfree(tsd);


    return 0;

}

float extract(int m){

    return lambda*exp((-lambda)*m);

}











