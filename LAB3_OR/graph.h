#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

typedef struct graph *Graph;

struct graph{
int V;
int E;
int **adj;
};

typedef struct{
int v;
int w;
int cost;
}Edge;

Edge EDGE(int,int,int);

Graph GRAPHinit_b(int);
Graph GRAPHinit_f(int);
void GRAPHinsertE(Graph,Edge);
void GRAPHremoveE(Graph,Edge);
void GRAPHfree(Graph);
void GRAPHprint(Graph);



#endif // GRAPH_H_INCLUDED
