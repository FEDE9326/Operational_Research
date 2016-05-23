#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "pq.h"

#define N 40
#define delta 4


int verify_constraints_delta(Graph G);


int main()
{
    Edge e1,e2,*listEdges,*l1,*l2;
    Graph b1,b2;
    b1=GRAPHinit(N,1);
    b2=GRAPHinit(N,1);
    Graph tsd;
    tsd=GRAPHinit_tsd(N);
    Graph f,f1;
    f=GRAPHinit(N,0);
    f1=GRAPHinit(N,0);
    int indice,trovato;
    int n,n1,n2;

    GRAPHrouteTraffic(b1,tsd,f);
    int nodo=0;
    do{
        indice=0;
        // Per ogni nodo fa in modo che rispetti la constraint sui delta in ingresso
        while(GRAPHinNodes(b1,nodo)>2*delta){
        //fa l'elenco dei link che entrano nel nodo ordinandoli per traffico crescente
            l1=EdgegetIN(f,nodo,&n1);
            HeapSort(l1,n1);
            e1=l1[indice];
            GRAPHcopy(b2,b1);
            GRAPHremoveE(b2,e1);
            // se il grafo rimane connessso dopo aver rimosso il link meno usato il traffico viene ridistribuito
            // e si rifa il giro, in caso contrario si passa a provare il link successivo
            if(GRAPHisConnected(b2)){
                f=GRAPHinit(N,0);
                GRAPHrouteTraffic(b2,tsd,f);
                GRAPHcopy(b1,b2);
            }else{
            indice++;
            }
        }
        indice=0;
        // Per ogni nodo fa in modo che rispetti la constraint sui delta in uscita
         while(GRAPHoutNodes(b1,nodo)>2*delta){
            l1=EdgegetOUT(f,nodo,&n1);
            HeapSort(l1,n1);
            e1=l1[indice];
            GRAPHcopy(b2,b1);
            GRAPHremoveE(b2,e1);
            // se il grafo rimane connessso dopo aver rimosso il link meno usato il traffico viene ridistribuito
            // e si rifa il giro, in caso contrario si passa a provare il link successivo
            if(GRAPHisConnected(b2)){
                f=GRAPHinit(N,0);
                GRAPHrouteTraffic(b2,tsd,f);
                GRAPHcopy(b1,b2);
            }else{
            indice++;
            }
        }

        nodo++;


    }while(nodo<N);

    //GRAPHprint(b1);
    f=GRAPHinit(N,0);
    GRAPHrouteTraffic(b1,tsd,f);
    e1=GRAPHmaxFlow(f);
    //printf("Max flow at %d %d: %f\n",e1.v,e1.w,e1.cost);

    //Una volta che la constraint sui delta viene rispettata tenta di eliminare il più congestionato

    do{
        listEdges=EDGEget(f,&n);
        HeapSort(listEdges,n);
            indice=n-1;
            trovato=0;
            do{
            //sceglie il link meno usato
            e1=listEdges[indice];
            GRAPHcopy(b2,b1);
            GRAPHremoveE(b2,e1);
            if(GRAPHisConnected(b2)){
            //se il grafico rimane connesso opo aver rimosso il link si ricalcola il traffico
                f1=GRAPHinit(N,0);
                GRAPHrouteTraffic(b2,tsd,f1);
                e2=GRAPHmaxFlow(f1);
                //printf("e1:%f e2:%f\n",e1.cost,e2.cost);
                if(e2.cost<e1.cost){
                    printf("migliorato %f\n",e2.cost);
                    GRAPHcopy(b1,b2);
                    GRAPHcopy(f,f1);
                    trovato=1;
                }else{
                indice--;
                }
            }else{
            indice--;
            }

            }while(trovato==0 && indice>=0);
    }while(trovato==1);

    //printf("Final topology\n");
    //GRAPHprint(b1);
    e1=GRAPHmaxFlow(f);
    printf("Max flow at %d %d: %f\n",e1.v,e1.w,e1.cost);

    //FILE *fp;
    //p=fopen("3_2_heu.txt","a+");
    //fprintf(fp,"N : %d \t Delta : %d",N,delta);
    //GRAPHprintonfile(b1);
    //fprintf(fp,"\nHeuristic :Max flow at %d %d: %f\n",e1.v,e1.w,e1.cost);
    //fprintf(fp,"%d,%d,%f\n",N,delta,e1.cost);
    Graph r;
    r=GRAPHinit(N,1);
    Graph r2;
    r2=GRAPHinit(N,1);

    /*printf("Random topology\n");
    GRAPHprint(b1);
    e1=GRAPHmaxFlow(f);
    printf("Max flow at %d %d: %f\n",e1.v,e1.w,e1.cost);
*/





// RANDOM TOPOLOGY
    nodo=0;
    do{
        indice=0;
        // Per ogni nodo fa in modo che rispetti la constraint sui delta in ingresso
        while(GRAPHinNodes(r,nodo)>delta){
        //fa l'elenco dei link che entrano nel nodo ordinandoli per traffico crescente
            l1=EdgegetIN(f,nodo,&n1);
            //HeapSort(l1,n1);
            indice=random()%n1;
            e1=l1[indice];
            GRAPHcopy(r2,r);
            GRAPHremoveE(r2,e1);
            // se il grafo rimane connessso dopo aver rimosso il link meno usato il traffico viene ridistribuito
            // e si rifa il giro, in caso contrario si passa a provare il link successivo
            if(GRAPHisConnected(r2)){
                f=GRAPHinit(N,0);
                GRAPHrouteTraffic(r2,tsd,f);
                GRAPHcopy(r,r2);
            }
        }
        indice=0;
        // Per ogni nodo fa in modo che rispetti la constraint sui delta in uscita
         while(GRAPHoutNodes(r,nodo)>delta){
            l1=EdgegetOUT(f,nodo,&n1);
            //HeapSort(l1,n1);
            indice=random()%n1;
            e1=l1[indice];
            GRAPHcopy(r2,r);
            GRAPHremoveE(r2,e1);
            // se il grafo rimane connessso dopo aver rimosso il link meno usato il traffico viene ridistribuito
            // e si rifa il giro, in caso contrario si passa a provare il link successivo
            if(GRAPHisConnected(r2)){
                f=GRAPHinit(N,0);
                GRAPHrouteTraffic(r2,tsd,f);
                GRAPHcopy(r,r2);
            }
        }

        nodo++;


    }while(nodo<N);
    e1=GRAPHmaxFlow(f);
    printf("Max flow at %d %d: %f\n",e1.v,e1.w,e1.cost);
    //GRAPHprint(r);

    //GRAPHprintonfile(r);
    //fprintf(fp,"\nRandom : Max flow at %d %d: %f\n",e1.v,e1.w,e1.cost);
    //fp=fopen("3_2_rand.txt","a+");
    //fprintf(fp,"N : %d \t Delta : %d",N,delta);
    //GRAPHprintonfile(b1);
    //fprintf(fp,"\nHeuristic :Max flow at %d %d: %f\n",e1.v,e1.w,e1.cost);
    //fprintf(fp,"%d,%d,%f\n",N,delta,e1.cost);

    GRAPHfree(f);
    GRAPHfree(b1);
    GRAPHfree(b2);
    GRAPHfree(tsd);
    GRAPHfree(r);
    GRAPHfree(r2);
    //fclose(fp);

    return 0;

}

//torna 1 se non verificato
/*int verify_constraints_delta(Graph G){
    int i,flag=0;

    for(i=0;i<N && flag==0;i++){
        if(GRAPHoutNodes(G,i)>=delta || GRAPHinNodes(G,i)>=delta)
        flag=1;
    }
    return flag;
}
*/









