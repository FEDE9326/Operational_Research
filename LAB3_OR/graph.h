#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

typedef struct graph *Graph;

struct graph{
int V;
int E;
int **adj;
int *pre,*post,*cc,*st,*va;
int time;
};

typedef struct{
int v;
int w;
int cost;
}Edge;

Edge EDGE(int,int,int);

Graph GRAPHinit_b(int);
Graph GRAPHinit_tsd(int);
void GRAPHinsertE(Graph,Edge);
void GRAPHremoveE(Graph,Edge);
void GRAPHfree(Graph);
void GRAPHprint(Graph);
void INITvisit(Graph G);
void CLEANvisit(Graph G);
int GRAPHisConnected(Graph G);



#endif // GRAPH_H_INCLUDED
