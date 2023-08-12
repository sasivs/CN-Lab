#include<stdio.h>
#include<stdlib.h>

int NODES; 

struct node{
    int name;
    int* dv;
    int* next;
};

void distance_vector_routing(struct node* nodes){
    int updates = 0;
    do{
        updates = 0;
        for(int i=0; i<NODES; i++){
            for(int j=0; j<NODES; j++){
                for(int k=0; k<NODES; k++){
                    if (nodes[i].dv[j]>(nodes[i].dv[k]+nodes[k].dv[j])){
                        nodes[i].dv[j] = nodes[i].dv[k]+nodes[k].dv[j];
                        nodes[i].next[j] = k;
                        updates++;
                    }
                }
            }
        }
    }while(updates!=0);

    for (int i=0; i<NODES; i++){
        printf("Routing table at node %d\n", i);
        printf("Node\t\t Dist\t\t Next\n");
        for(int j=0; j<NODES; j++){
            printf("%d\t\t %d\t\t %d\n", nodes[j].name, nodes[i].dv[j], nodes[i].next[j]);
        }
        printf("=====================\n");
    }
}

int main(){
    printf("Enter the number of nodes: \n");
    scanf("%d", &NODES);
    struct node nodes[NODES];
    int cost[NODES][NODES];
    for (int i=0; i<NODES; i++){
        cost[i][i] = 0;
    }
    for (int i=0; i<NODES; i++){
        for(int j=0; j<i && j!=i; j++){
            printf("Cost (%d, %d): ", i,j);
            scanf("%d", &cost[i][j]);
            cost[j][i] = cost[i][j];
        }
    }
    for(int i=0; i<NODES; i++){
        nodes[i].name = i;
        nodes[i].dv = (int*)malloc(sizeof(int)*NODES);
        for(int j=0; j<NODES; j++) nodes[i].dv[j] = cost[i][j];
        nodes[i].next = (int*)malloc(sizeof(int)*NODES);
        for(int j=0; j<NODES; j++) nodes[i].next[j] = j;
    }
    distance_vector_routing(nodes);
    return 0;
}

