#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#define N 20

int main()
{

    Graph b;
    b=GRAPHinit_b(N);
    Graph tsd;
    tsd=GRAPHinit_tsd(N);

    int a=GRAPHisConnected(b);

    printf("Number of tree %d \n",a);

    GRAPHprint(b);

    //full mesh
    //route traffic shortest path
    //calc fmax
    //verify constraint a)delta respected b)connectivity b)better than previous










    GRAPHfree(b);
    GRAPHfree(tsd);
    return 0;

}
