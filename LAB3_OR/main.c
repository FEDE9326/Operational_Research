#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "pq.h"

#define N 10
#define delta 4

void MergeSort(Edge A[], int p, int r,int max);
void bubblesort(Edge v[], int n);
int verify_constraints_delta(Graph G);


int main()
{
    Edge e1,e2,*listEdges;
    Graph b1,b2;
    b1=GRAPHinit(N,1);
    b2=GRAPHinit(N,1);
    Graph tsd;
    tsd=GRAPHinit_tsd(N);
    Graph f;
    f=GRAPHinit(N,0);
    int indice,trovato;
    int n,i;

    GRAPHrouteTraffic(b1,tsd,f);


    do{
        listEdges=EDGEget(f,&n);

        HeapSort(listEdges,n);

        indice=n-1;
        trovato=0;

        do{
        e1=listEdges[indice];
        GRAPHcopy(b2,b1);
        GRAPHremoveE(b2,e1);
        if(GRAPHisConnected(b2)){
            f=GRAPHinit(N,0);
            GRAPHrouteTraffic(b2,tsd,f);
            e2=GRAPHmaxFlow(f);
            if(e2.cost<e1.cost || verify_constraints_delta(b1)){
                GRAPHcopy(b1,b2);
                trovato=1;
            }else{
            indice--;
            }
        }

        }while(trovato==0 && indice>=0);


    }while(trovato==1);

    printf("Final topology\n");
    GRAPHprint(b2);
    //printf("Final flow\n");
    //GRAPHprint(f);
    //e=GRAPHmaxFlow(f);
    //printf("Max flow at %d %d: %f\n",e.v,e.w,e.cost);

    GRAPHfree(f);
    GRAPHfree(b2);
    GRAPHfree(tsd);

    return 0;

}

//torna 1 se verificato
int verify_constraints_delta(Graph G){
    int i,flag=0;

    for(i=0;i<N && flag==0;i++){
        if(GRAPHoutNodes(G,i)>=delta || GRAPHinNodes(G,i)>=delta)
        flag=1;
    }
    return flag;
}

/*void Merge(Edge A[], int p, int q, int r,int max) {
  int i, j, k;
  Edge B[max];

  i = p;
  j = q+1;
  k = 0;
  while (i<=q && j<=r) {
    if (A[i].cost<A[j].cost) {
      B[k]=EDGE(A[i].v,A[i].w,A[i].cost);
      i++;
    } else {
      B[k]=EDGE(A[j].v,A[j].w,A[j].cost);
      j++;
    }
    k++;
  }
  while (i<=q) {
    B[k]=EDGE(A[i].v,A[i].w,A[i].cost);
    i++;
    k++;
  }
  while (j<=r) {
    B[k]=EDGE(A[j].v,A[j].w,A[j].cost);
    j++;
    k++;
  }
  for (k=p; k<=r; k++)
    EDGEcopy(A[k],B[k-p]);
  return;
}

void MergeSort(Edge A[], int p, int r,int max) {
  int q;

  if (p<r) {
    q = (p+r)/2;
    MergeSort(A, p, q,max);
    MergeSort(A, q+1, r,max);
    Merge(A, p, q, r,max);
  }
  return;
}
*/

void bubblesort(Edge v[], int n) {
int i,k;
Edge temp;
temp=EDGE(0,0,0);

for(i = 0; i<n-1; i++) {
 for(k = 0; k<n-1-i; k++) {
         if(v[k].cost < v[k+1].cost) {

          EDGEcopy(&temp,&v[k]);
          EDGEcopy(&v[k],&v[k+1]);
          EDGEcopy(&v[k+1],&temp);

         }
 }
}
}




