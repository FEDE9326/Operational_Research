#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#define N 20

int main()
{
    Edge e;
    Graph b;
    b=GRAPHinit(N,1);
    Graph tsd;
    tsd=GRAPHinit_tsd(N);
    Graph f;
    f=GRAPHinit(N,0);

    GRAPHrouteTraffic(b,tsd,f);
    e=GRAPHmaxFlow(f);


    printf("Number of tree %d \n",GRAPHisConnected(b));
    printf("Max flow at %d %d: %f",e.v,e.w,e.cost);

    GRAPHprint(b);

    //full mesh
    //route traffic shortest path
    //calc fmax
    //verify constraint a)delta respected b)connectivity b)better than previous










    GRAPHfree(b);
    GRAPHfree(tsd);
    return 0;

}