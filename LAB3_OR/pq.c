#define LEFT(i)   ((i*2) + 1)
#define RIGHT(i) ((i*2) + 2)

#include "graph.h"


void Swap(Edge v[], int n1, int n2);
void Heapify(Edge A[], int i, int heapsize);

void Swap( Edge v[], int n1, int n2)
{
Edge temp;
EDGEcopy(&temp,&v[n1]);
EDGEcopy(&v[n1],&v[n2]);
EDGEcopy(&v[n2],&temp);
return;
}

void Heapify(Edge A[], int i, int heapsize)
{
int l, r, largest;
l = LEFT(i);
r = RIGHT(i);
if(l< heapsize && A[l].cost>A[i].cost)
    largest=l;
else
    largest = i;
if(r<heapsize && A[r].cost>A[largest].cost)
    largest=r;
if(largest!= i) {
Swap(A,i,largest);
Heapify(A,largest,heapsize);
}
return;
}

void BuildHeap (Edge A[], int heapsize){
int i;
for(i=(heapsize)/2-1; i >= 0; i--){
Heapify(A,i,heapsize);
}
return;
}

void HeapSort(Edge A[], int heapsize)
{
int i;
BuildHeap(A, heapsize);

for(i=heapsize-1; i > 0; i--) {
Swap(A,0,i);
heapsize--;
Heapify(A,0,heapsize);
}
return;
}




