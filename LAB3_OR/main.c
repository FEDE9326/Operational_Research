#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#define N 5

/*problema connessione grafo*/
int main()
{
    Edge e;
    Graph b1,b2;
    b1=GRAPHinit(N,1);
    b2=GRAPHinit(N,1);
    Graph tsd;
    tsd=GRAPHinit_tsd(N);
    Graph f;
    f=GRAPHinit(N,0);
    int flag=0;

    GRAPHrouteTraffic(b1,tsd,f);


    do{
    e=GRAPHmaxFlow(f);
    GRAPHcopy(b2,b1);
    GRAPHremoveE(b2,e);
    GRAPHprint(b2);
    getchar();
    if(GRAPHisConnected(b2)){
        f=GRAPHinit(N,0);
        GRAPHrouteTraffic(b2,tsd,f);
        GRAPHcopy(b1,b2);
    }else{
    flag=1;
    }

    }while(flag==0);

    printf("Final topology\n");
    GRAPHprint(b1);
    printf("Final flow\n");
    GRAPHprint(f);
    e=GRAPHmaxFlow(f);
    printf("Max flow at %d %d: %f\n",e.v,e.w,e.cost);

    GRAPHfree(f);
    GRAPHfree(b1);
    GRAPHfree(tsd);

    return 0;

}
