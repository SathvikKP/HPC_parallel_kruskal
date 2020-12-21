#include <iostream>
#define n 10000000
//int arr[n];
//int arr1[n];


struct Edge{
	int x;
	int y;
	int w;	
};

struct Graph{
	int V;
	int E;
	struct Edge* edge = (Edge*)malloc(n*sizeof(struct Edge));
	int mstCost;
};

struct subset{
	int parent;
	int rank;
};

long kruskals(struct Graph);

int find(struct subset*, int);

void Union(struct subset*, int, int);

void printGraph(Graph);

int partition(Edge[], int, int);

void quicksort(Edge[] , int, int);

void swap(int*,int*);

int partitionserial (Edge[], int, int);

void quickSortserial(Edge[], int, int);  
