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
void assignTraffic(Graph G,Graph T,Graph F,int s,int j);
float assignRandomNumber();
float** getManhattan(Graph T,int n,int delta);

long int seed=868920;

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
    srand((unsigned)time(NULL));
    int i,j;
    float **t;
    t=malloc(r*sizeof(float*));
    for(i=0;i<r;i++)
        t[i]=malloc(c*sizeof(float));
    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
        {
            if(i!=j)
            //
            t[i][j]=uniform(1,10,&seed);//assignRandomNumber();
            else
            t[i][j]=0;

        }
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

Graph GRAPHinitManhattan(int n,int delta,Graph T){
    Graph G;
    G=malloc(sizeof(struct graph));
    G->V=n;
    G->E=0;
    G->va=VETint(n,0);
    G->adj=getManhattan(T,n,delta);
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
        printf("%.2f ",G->adj[i][j]);
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

/*float assignTraffic(Graph G,Graph T,Graph F,int s,int j){

    int i;

    for(i=0;i<G->V;i++){

        if(G->father[i]==j && i!=s){
            F->adj[j][i]+=assignTraffic(G,T,F,s,i);
        }
    }

    F->adj[G->father[j]][j]+=T->adj[s][j];

    return T->adj[s][j];

}*/

void assignTraffic(Graph G,Graph T,Graph F,int s,int j){

    int i;

    for(i=0;i<G->V;i++){

        if(G->father[i]==j && i!=s){
            assignTraffic(G,T,F,s,i);
        }
    }

    F->adj[G->father[j]][j]+=T->adj[s][j];

    return;

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

float assignRandomNumber(){

    float a;

    a=((float)rand())/RAND_MAX;

    if(a>0.1)
        return (float)uniform(0.5,1.5,&seed);
    else
        return (float)uniform(5,15,&seed);

}

/*int** Manhattan(int n){
    int i,j,delta=4;
    int **matrix;

    matrix=malloc(delta*sizeof(int*));
    for(i=0;i<n;i++)
    matrix[i]=malloc(delta*sizeof(int));

    for(i=0;i<delta;i++)
        for(j=0;j<delta;j++)
            matrix[i][j]=0;


   for(i=0;i<delta;i++){
    for(j=0;j<delta;j++){

        if(j+1<delta)
        matrix[i][j+1]=1;
        if(j-1>0)
        matrix[i][j-1]=1;
        if(i-1>0)
        matrix[i-1][j]=1;
        if(i+1<delta)
        matrix[i+1][j]=1;
        if(i==0){
        matrix[delta][j]=1;
        matrix[j][delta]=1;
        }
        if(j==0){
        matrix[i][delta]=1;
        matrix[delta][i]=1;
        }




   }}

   return matrix;
}
*/

float** getManhattan(Graph T,int n,int delta){

    float **matrix;
    int vett[n];
    int i,j,k;
    Edge *e;
    Edge ed;
    e=malloc((n*(n-1)/2)*sizeof(Edge));

    //GRAPHprint(T);

    for(i=0;i<n;i++)
        vett[i]=delta;

    matrix=malloc(n*sizeof(float*));
    for(i=0;i<n;i++){
        matrix[i]=malloc(n*sizeof(float));
        for(j=0;j<n;j++){
            matrix[i][j]=0;
        }
    }
    k=0;

    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            e[k]=EDGE(i,j,T->adj[i][j]+T->adj[j][i]);
            //printf("Inserito arco %d %d: %f\n",i,j,T->adj[i][j]+T->adj[j][i]);
            k++;

    }}



    HeapSort(e,n*(n-1)/2);

    i=k-1;

    do{

    ed=e[i];
    //printf("Considered arc %d %d: %f\n",ed.v,ed.w,ed.cost);
    if(vett[ed.v]>0 && vett[ed.w]>0){

    matrix[ed.v][ed.w]=1;
    matrix[ed.w][ed.v]=1;
    //printf("Added arc %d %d\n",ed.v,ed.w);
    vett[ed.v]--;
    vett[ed.w]--;

    }
    i--;

    }while(i>0);


    return matrix;

}

void verifyTraffic(Graph G,Graph T){

float s1=0,s2=0;
int i,j;

for(i=0;i<G->V;i++)
    for(j=0;j<T->V;j++){
        s1+=G->adj[i][j];
        s2+=T->adj[i][j];
        }

    printf("s1=%f\n",s1);
    printf("s2=%f\n",s2);


}

void exchangeNodes(Graph G,int v,int w){

    int i;

    int vettv[G->V];
    int vettw[G->V];

    for(i=0;i<G->V;i++){
        vettv[i]=G->adj[v][i];


    }

    for(i=0;i<G->V;i++){
        vettw[i]=G->adj[w][i];


    }


    for(i=0;i<G->V;i++){
        G->adj[v][i]=vettw[i];
        G->adj[i][v]=vettw[i];
        G->adj[w][i]=vettv[i];
        G->adj[i][w]=vettv[i];
    }

    if(G->adj[v][v]==1){
        G->adj[v][v]=0;
        G->adj[w][w]=0;
        G->adj[v][w]=1;
        G->adj[w][v]=1;}

    return;
}





