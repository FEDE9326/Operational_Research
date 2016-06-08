#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "pq.h"
#include <time.h>
#include <math.h>
#include "random.h"

#define FLT_MAX 1000

float **MATRIXint_tsd(int r,int c);
float **MATRIXint_b(int r,int c);
int *VETint(int r,int val);
void dfs(Graph G,int v);
static void CLEANvisit(Graph G);
static void INITvisit(Graph G);
float assignTraffic(Graph G,Graph T,Graph F,int s,int j);
long int se=868920;
time_t t;

Edge EDGE(int v,int w,float cost){

    Edge e;
    e.v=v;
    e.w=w;
    e.cost=cost;
    return e;
}

void EDGEcopy(Edge *a,Edge *b){

    a->v=b->v;
    a->w=b->w;
    a->cost=b->cost;

}

Edge* EdgegetIN(Graph G,int a,int *n){

    Edge *e;
    int i,j=0,cont=0;

    for(i=0;i<G->V;i++){
        if(G->adj[i][a]!=0)
        cont++;
    }

    *n=cont;
    e=malloc(cont*sizeof(Edge));

    for(i=0;i<G->V;i++){
        if(G->adj[i][a]!=0){
            e[j]=EDGE(i,a,G->adj[i][a]);
            j++;
        }
    }

    return e;

}

Edge* EdgegetOUT(Graph G,int a,int *n){

    Edge *e;
    int i,j=0,cont=0;

    for(i=0;i<G->V;i++){
        if(G->adj[a][i]!=0)
        cont++;
    }

    *n=cont;
    e=malloc(cont*sizeof(Edge));

    for(i=0;i<G->V;i++){
        if(G->adj[a][i]!=0){
            e[j]=EDGE(a,i,G->adj[a][i]);
            j++;
        }
    }

    return e;

}

Edge* EDGEget(Graph G, int *n){

    int i,j,cont=0,k=0;
    Edge *e,a;

    for(i=0;i<G->V;i++){
        for(j=0;j<G->V;j++){
            if(G->adj[i][j]!=0)
                cont++;
        }}
    *n=cont;

    e=malloc(cont*sizeof(Edge));

    for(i=0;i<G->V;i++){
        for(j=0;j<G->V;j++){
            if(G->adj[i][j]!=0){
                a=EDGE(i,j,G->adj[i][j]);
                e[k]=a;
                k++;
            }
        }}
    return e;

}

float **MATRIXint(int r,int c,int value){
    int i,j;
    float **t;
    t=malloc(r*sizeof(float*));
    for(i=0;i<r;i++)
        t[i]=malloc(c*sizeof(float));
    for(i=0;i<r;i++)
        for(j=0;j<c;j++){
            if(i==j)
                t[i][j]=0;
            else
                t[i][j]=value;
        }

    return t;
}

float **MATRIXint_tsd(int r,int c){
    srand((unsigned)time(&t));
    int i,j;
    float **t;
    float f;
    long int seed=rnd32(se);
    t=malloc(r*sizeof(float*));
    for(i=0;i<r;i++)
        t[i]=malloc(c*sizeof(float));
    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
        {
            if(i!=j)
            //
            {
                f=uniform01(&seed);
                if(f>0.0)
                t[i][j]=((float)rand())/RAND_MAX+0.5;
                else
                t[i][j]=((float)rand()/RAND_MAX)*10+5;
            }

            else
            {
            t[i][j]=0;
            //printf("%f",t[i][j]);
            }


        }
        printf("\n");
    return t;
}
Graph GRAPHinit(int n,int value){
    Graph G;
    G=malloc(sizeof(struct graph));
    G->V=n;
    G->E=0;
    G->va=VETint(n,0);
    G->adj=MATRIXint(n,n,value);
    return G;
}

int *VETint(int r,int val){
    int i;
    int *q;
    q=malloc(r*sizeof(int));
    for(i=0;i<r;i++){
        q[i]=val;
    }
    return q;
}

Graph GRAPHinit_tsd(int n){
    Graph G;
    G=malloc(sizeof(struct graph));
    G->V=n;
    G->E=0;
    G->va=VETint(n,0);
    G->adj=MATRIXint_tsd(n,n);
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
        printf("%d ",(int)G->adj[i][j]);
    printf("\n");
    }
}

void GRAPHprintonfile(Graph G){
    int i,j;
    FILE *f;
    f=fopen("3_1.txt","a+");
    for(i=0;i<G->V;i++){
        for(j=0;j<G->V;j++)
        fprintf(f,"%d ",(int)G->adj[i][j]);
    fprintf(f,"\n");
    }
    fprintf(f,"\n\n");
}

//torna 1 se il grafo BIDIREZIONALE è connesso
int GRAPHisConnected(Graph G){

    int somma=0,i,j,flag=0;

    for(j=0;j<G->V && flag==0;j++){
    somma=0;
    G->va=VETint(G->V,0);

    dfs(G,j);

    for(i=0;i<G->V;i++){
        if(G->va[i]==1)
            somma++;
    }

    if(somma!=G->V)
        flag=1;

    }

    return !flag;

}


void dfs(Graph G,int v){
    int i;
    G->va[v]=1;
    for(i=0;i<G->V;i++){
        if(G->adj[v][i] && !G->va[i])
            dfs(G,i);
    }
}


int GRAPHoutNodes(Graph G,int a){
    int cont=0;
    int i;

    for(i=0;i<G->V;i++){
    if(G->adj[a][i]==1)
    cont++;
    }
    return cont;
}


int GRAPHinNodes(Graph G,int a){
    int cont=0;
    int i;

    for(i=0;i<G->V;i++){
    if(G->adj[i][a]==1)
    cont++;
    }
    return cont;
}

static void INITvisit(Graph G) {
    int v;

    G->father = malloc (G->V * sizeof(int));
    G->visited = malloc (G->V * sizeof(int));
    G->weight = malloc (G->V * sizeof(float));

    G->time = 0;

    for (v=0; v < G->V; v++)
    {
        G->father[v] = -1;
        G->visited[v] = 0;
        G->weight[v] = FLT_MAX;
    }
}

void GRAPHShortestPathBF(Graph G, int start)
{
   int i, j, k, again, nNodes=G->V;
   float newdist, currdist;

   INITvisit(G);

   G->weight[start] = 0;
   G->father[start] = start;

   again = 1;
   for (k=0; k<nNodes && again; k++) {
      again = 0;
      for (i=0; i<nNodes; i++) {
         currdist = G->weight[i];
         if (currdist != FLT_MAX) {
            for (j=0; j<nNodes; j++) {
               if (G->adj[i][j]) { /* se esiste l'arco */
                  /* calcolo della nuova distanza ... */
                  newdist = currdist + G->adj[i][j];
                  /* ... e relax sul nodo di arrivo */
                  if (newdist < G->weight[j]) {
                     G->weight[j] = newdist;
                     G->father[j] = i;
                     again = 1;
                  }
               }
            }
         }
      }
   }

}

float assignTraffic(Graph G,Graph T,Graph F,int s,int j){

    int i;

    for(i=0;i<G->V;i++){

        if(G->father[i]==j && i!=s){
            F->adj[j][i]+=assignTraffic(G,T,F,s,i);
        }
    }

    F->adj[G->father[j]][j]+=T->adj[s][j];

    return T->adj[s][j];

}

void CLEANvisit(Graph G) {
    free(G->father);
    G->father = NULL;
    free(G->visited);
    G->visited = NULL;
    free(G->weight);
    G->weight = NULL;
}

void GRAPHrouteTraffic(Graph G,Graph T,Graph F){

    int i;

    for(i=0;i<G->V;i++){

    GRAPHShortestPathBF(G,i);
    assignTraffic(G,T,F,i,i);
    CLEANvisit(G);
    }

}

Edge GRAPHmaxFlow(Graph G){

    int i,j;
    Edge e;
    e=EDGE(0,0,0);
    for(i=0;i<G->V;i++){
        for(j=0;j<G->V;j++){
            if(G->adj[i][j]>e.cost){
            e=EDGE(i,j,G->adj[i][j]);
        }}}
    return e;
}

void GRAPHcopy(Graph G, Graph T){

    int i,j;

    for(i=0;i<G->V;i++){
        for(j=0;j<G->V;j++){
            G->adj[i][j]=T->adj[i][j];
            }
    }

}







