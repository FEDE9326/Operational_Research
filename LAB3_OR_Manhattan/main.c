#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "pq.h"
#include "random.h"

#define N 16
#define delta 4


int verify_constraints_delta(Graph G);


int main()
{
    Edge e1,e2,*listEdges;
    Graph b1,b2;

    Graph tsd;
    tsd=GRAPHinit_tsd(N);
    b1=GRAPHinitManhattan(N,delta,tsd);
    b2=GRAPHinitManhattan(N,delta,tsd);
    Graph f,f1;
    f=GRAPHinit(N,0);
    f1=GRAPHinit(N,0);
    int indice,trovato;
    int n;

    printf("Generating Manhattab solution...\n");

    GRAPHprint(b1);

    f=GRAPHinit(N,0);
    GRAPHrouteTraffic(b1,tsd,f);
    e1=GRAPHmaxFlow(f);
    printf("Max flow at %d %d: %f\n",e1.v,e1.w,e1.cost);

    //Una volta che la constraint sui delta viene rispettata tenta di eliminare il più congestionato
    printf("Improving the solution...\n");
    do{
        listEdges=EDGEget(f,&n);
        HeapSort(listEdges,n);
            indice=n-1;
            trovato=0;
            do{
            //sceglie il link meno usato
            e1=listEdges[indice];
            GRAPHcopy(b2,b1);
            GRAPHremoveE(b2,e1);
            if(GRAPHisConnected(b2)){
            //se il grafico rimane connesso opo aver rimosso il link si ricalcola il traffico
                f1=GRAPHinit(N,0);
                GRAPHrouteTraffic(b2,tsd,f1);
                e2=GRAPHmaxFlow(f1);
                //printf("e1:%f e2:%f\n",e1.cost,e2.cost);
                if(e2.cost<e1.cost){
                    printf("migliorato %f\n",e2.cost);
                    GRAPHcopy(b1,b2);
                    GRAPHcopy(f,f1);
                    trovato=1;
                }else{
                indice--;
                }
            }else{
            indice--;
            }

            }while(trovato==0 && indice>=0);
    }while(trovato==1);

    e1=GRAPHmaxFlow(f);
    printf("Max flow at %d %d: %f\n",e1.v,e1.w,e1.cost);

    GRAPHfree(f);
    GRAPHfree(b1);
    GRAPHfree(b2);
    GRAPHfree(tsd);


    return 0;

}











