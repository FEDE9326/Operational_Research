#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

typedef struct graph *Graph;

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
void EDGEcopy(Edge a,Edge b);
Edge* EDGEget(Graph G,int *n);

Graph GRAPHinit(int,int);
Graph GRAPHinit_tsd(int);
void GRAPHinsertE(Graph,Edge);
void GRAPHremoveE(Graph,Edge);
void GRAPHfree(Graph);
void GRAPHprint(Graph);
int GRAPHisConnected(Graph G);
int GRAPHoutNodes(Graph G,int a);
int GRAPHinNodes(Graph G,int a);
void GRAPHrouteTraffic(Graph G, Graph T,Graph F);
Edge GRAPHmaxFlow(Graph G);
void GRAPHcopy(Graph G, Graph T);





#endif // GRAPH_H_INCLUDED
