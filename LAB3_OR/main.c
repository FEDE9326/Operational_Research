#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#define N 24

int main()
{

    Graph b;
    b=GRAPHinit_b(N);
    Graph f;
    f=GRAPHinit_f(N);
    Graph c;
    GRAPHprint(b);
    GRAPHprint(f);

    //full mesh
    //route traffic shortest path
    //calc fmax
    //verify constraint a)delta respected b)connectivity b)better than previous










    GRAPHfree(b);
    GRAPHfree(f);
    return 0;

}
