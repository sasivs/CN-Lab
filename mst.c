#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>
#include<stdbool.h>

typedef struct Node Node;
typedef struct Adj Adj;

struct Node {
    int weight;
    Adj** adjacent;
    bool visited;
};

struct Adj{
    Node* node;
    int cost;
};



int main(){
    int v;
    printf("Enter number of vertices: ");
    scanf("%d", &v);
    Node** graph = (Node**)malloc(sizeof(Node*)*v);
    for (int i=0; i<v; i++){
        graph[i] = (Node*)malloc(sizeof(Node));
        int adj;
        printf("Enter number of adjacent vertices\n");
        scanf("%d", &adj);
        Adj** adjac = (Adj**)malloc(sizeof(Adj*)*adj); 
        graph[i]->adjacent = adjac; 
    }

    for (int i=0; i<v; i++){
        int n_adj = sizeof(graph[i]->adjacent)/sizeof(graph[i]->adjacent[0]);
        int adj, cost;
        for (int j=0; j<n_adj; j++){
            graph[i]->adjacent[j] = (Adj*)malloc(sizeof(Adj));
            printf("Enter adjacent vertex to vertex %d\n",i);
            scanf("%d", &adj);
            graph[i]->adjacent[j]->node = graph[adj];
            printf("Enter cost of vertex from %d to %d\n",i, adj);
            scanf("%d", &cost);
            graph[i]->adjacent[j]->cost = cost;
        }
    }
    return 0;
}