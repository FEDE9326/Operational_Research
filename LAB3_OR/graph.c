#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <math.h>

int **MATRIXint_f(int r,int c);
int **MATRIXint_b(int r,int c);

Edge EDGE(int v,int w,int cost){
    Edge e;
    e.v=v;
    e.w=w;
    e.cost=cost;
    return e;
}

int **MATRIXint_b(int r,int c){
    int i,j;
    int **t;
    t=malloc(r*sizeof(float*));
    for(i=0;i<r;i++)
        t[i]=malloc(c*sizeof(float));
    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
            t[i][j]=abs(i-j);
    return t;
}

int **MATRIXint_f(int r,int c){
    int i,j;
    int **t;
    t=malloc(r*sizeof(float*));
    for(i=0;i<r;i++)
        t[i]=malloc(c*sizeof(float));
    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
            t[i][j]=(float)random()/8;
    return t;
}
Graph GRAPHinit_b(int n){
    Graph G;
    G=malloc(sizeof(struct graph));
    G->V=n;
    G->E=0;
    G->adj=MATRIXint_b(n,n);
    return G;
}

Graph GRAPHinit_f(int n){
    Graph G;
    G=malloc(sizeof(struct graph));
    G->V=n;
    G->E=0;
    G->adj=MATRIXint_f(n,n);
    return G;
}

void GRAPHinsertE(Graph G,Edge e){
    int v,w;
    v=e.v;
    w=e.w;
    if (G->adj[v][w]==0){
        G->adj[v][w]=e.cost;
        G->E++;
    }
}
void GRAPHremoveE(Graph G,Edge e){
    int v,w;
    v=e.v;
    w=e.w;
    if (G->adj[v][w]!=0){
        G->adj[v][w]=0;
        G->E--;
    }
}

void GRAPHfree(Graph G){
int i;
for(i=0;i<G->V;i++){
    free(G->adj[i]);
}
free(G->adj);
free(G);
}

void GRAPHprint(Graph G){
    int i,j;

    for(i=0;i<G->V;i++){
        for(j=0;j<G->V;j++)
        printf("%d ",G->adj[i][j]);
    printf("\n");
    }
}
