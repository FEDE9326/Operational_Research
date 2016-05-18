#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "pq.h"

#define N 6
#define delta 3

int verify_constraints_delta(Graph G);


int main()
{
    Edge e1,e2,*listEdges;
    Graph b1,b2;
    b1=GRAPHinit(N,1);
    b2=GRAPHinit(N,1);
    Graph tsd;
    tsd=GRAPHinit_tsd(N);
    Graph f;
    f=GRAPHinit(N,0);
    int indice,trovato;
    int n;

    GRAPHrouteTraffic(b1,tsd,f);
    e1=GRAPHmaxFlow(f);
    printf("Initial max flow at %d %d: %f\n",e1.v,e1.w,e1.cost);


    do{
        listEdges=EDGEget(f,&n);

        HeapSort(listEdges,n);

        indice=n-1;
        //indice=0;
        trovato=0;

        do{
        e1=listEdges[indice];
        GRAPHcopy(b2,b1);
        GRAPHremoveE(b2,e1);
        if(GRAPHisConnected(b2)){
            f=GRAPHinit(N,0);
            GRAPHrouteTraffic(b2,tsd,f);
            e2=GRAPHmaxFlow(f);
            if(e2.cost<e1.cost || verify_constraints_delta(b1)){
                if(verify_constraints_delta(b1))
                printf("flusso dentro ciclo %f\n",e2.cost);
            //if(e2.cost<e1.cost){
                GRAPHcopy(b1,b2);
                trovato=1;
            }else{
            indice--;
            //indice++;
            }
        }else{
        //indice ++;
        indice--;
        }

        }while(trovato==0 && indice>=0);


    }while(trovato==1);

    printf("Final topology\n");
    GRAPHprint(b1);
    e1=GRAPHmaxFlow(f);
    printf("Max flow at %d %d: %d\n",e1.v,e1.w,(int)e1.cost);
    printf("Random topology\n");
    GRAPHprint(b1);
    e1=GRAPHmaxFlow(f);
    printf("Max flow at %d %d: %d\n",e1.v,e1.w,(int)e1.cost);

    GRAPHfree(f);
    GRAPHfree(b1);
    GRAPHfree(b2);
    GRAPHfree(tsd);

    return 0;

}

//torna 1 se non verificato
int verify_constraints_delta(Graph G){
    int i,flag=0;

    for(i=0;i<N && flag==0;i++){
        if(GRAPHoutNodes(G,i)>=delta || GRAPHinNodes(G,i)>=delta)
        flag=1;
    }
    return flag;
}






