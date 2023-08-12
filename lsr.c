#include<stdio.h>
#include<stdlib.h>

#define INF 1000000000

int NODES; 

int getMinimumNode(int* array, int n, int* visited){
    int minIndex=-1, minCost=999999999;
    for(int i=1; i<n; i++){
        if (!visited[i] && array[i]<minCost){
            minCost = array[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void dijkstra(int cost[NODES][NODES]){
    int visited[NODES];
    int parent[NODES];
    int weights[NODES];
    for(int i=0; i<NODES; i++){ weights[i] = INF; visited[i]=0;}
    weights[0] = 0;
    parent[0] = 0;
    visited[0] = 1;
    for(int i=0; i<NODES; i++){
        if (!visited[i] && ((cost[0][i]+weights[0])<weights[i])){
            weights[i] = (cost[0][i]+weights[0]);
            parent[i] = 0;
        }
    }
    int next;
    while((next=getMinimumNode(weights, NODES, visited))!=-1){
        visited[next]=1;
        for(int i=0; i<NODES; i++){
            if (!visited[i] && ((cost[next][i]+weights[next])<weights[i])){
                weights[i] = (cost[next][i]+weights[next]);
                parent[i] = next;
            }
        }
    }
    printf("Node\t Parent\t Weights\n");
    for(int i=0; i<NODES; i++){
        printf("%d \t%d\t %d\n", i, parent[i], weights[i]);
    }
}


int main(){
    printf("Enter the number of nodes: \n");
    scanf("%d", &NODES);
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
    dijkstra(cost);
    return 0;
}
