#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

typedef struct graph *Graph;

long int seed;

struct graph{
int V;
int E;
float **adj;
int *father,*visited,*weight,*va;
int time;
};

typedef struct{
int v;
int w;
float cost;
}Edge;

Edge EDGE(int,int,float);
Edge* EDGEget(Graph G,int *n);
void EDGEcopy(Edge *a,Edge *b);
Edge* EdgegetIN(Graph G,int a,int *n);
Edge* EdgegetOUT(Graph G,int a,int *n);

Graph GRAPHinit(int,int);
Graph GRAPHinit_tsd(int);
void GRAPHinsertE(Graph,Edge);
void GRAPHremoveE(Graph,Edge);
void GRAPHfree(Graph);
void GRAPHprint(Graph);
void GRAPHprintonfile(Graph G);
int GRAPHisConnected(Graph G);
int GRAPHoutNodes(Graph G,int a);
int GRAPHinNodes(Graph G,int a);
void GRAPHrouteTraffic(Graph G, Graph T,Graph F);
Edge GRAPHmaxFlow(Graph G);
void GRAPHcopy(Graph G, Graph T);

Graph GRAPHinitManhattan(int n,int delta,Graph T);
void verifyTraffic(Graph G,Graph T);
void exchangeNodes(Graph G,int v,int w);


#endif // GRAPH_H_INCLUDED
