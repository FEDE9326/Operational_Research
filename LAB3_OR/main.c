#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "pq.h"

#define N 10
#define delta 4


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
    int flag=0,indice,trovato;
    int n;

    GRAPHrouteTraffic(b1,tsd,f);


    do{
        listEdges=EDGEget(f,&n);

        indice=0;
        trovato=0;

        do{
        e1=listEdges[indice];
        GRAPHcopy(b2,b1);
        GRAPHremoveE(b2,e1);
        if(GRAPHisConnected(b2)){
            f=GRAPHinit(N,0);
            GRAPHrouteTraffic(b2,tsd,f);
            e2=GRAPHmaxFlow(f);
            if(e2.cost<e1.cost){
                GRAPHcopy(b1,b2);
                trovato=1;
            }else{
            indice++;
            }
        }

        }while(trovato==0 && indice<n);


    }while(flag==0);

    printf("Final topology\n");
    GRAPHprint(b2);
    //printf("Final flow\n");
    //GRAPHprint(f);
    //e=GRAPHmaxFlow(f);
    //printf("Max flow at %d %d: %f\n",e.v,e.w,e.cost);

    GRAPHfree(f);
    GRAPHfree(b2);
    GRAPHfree(tsd);

    return 0;

}

//torna 1 se verificato
int verify_constraints_delta(Graph G){
    int i,flag=0;

    for(i=0;i<N && flag==0;i++){
        if(GRAPHoutNodes(G,i)>=delta || GRAPHinNodes(G,i)>=delta)
        flag=1;
    }
    return !flag;
}



