#include<iostream>
#include <omp.h>
#include "graphquicksort.h"


//Union function to check if two nodes belong to same subset i.e, if they have same parent.
void Union(struct subset* subsets,int x, int y)
{
	int xroot = find(subsets,x);
	int yroot = find(subsets,y);
	
	if (subsets[xroot].rank < subsets[yroot].rank)
	{
		subsets[xroot].parent = yroot;
	}
	else if (subsets[xroot].rank > subsets[yroot].rank)
	{
		subsets[yroot].parent = xroot;
	}
	else
	{
		subsets[xroot].parent = xroot;
		subsets[xroot].rank++;
	}
}


//Finding the root of a node using find function
int find(struct subset* subsets, int i)
{
	if (subsets[i].parent != i)
	{
		subsets[i].parent = find(subsets,subsets[i].parent);
	}
	return subsets[i].parent;
}

 //main kruskals implementation
long kruskals(struct Graph graph)
{
	int V = graph.V;
	int E = graph.E;
	struct Edge* result = (struct Edge*) malloc(V*sizeof(Edge));
	struct subset* subsets = (struct subset*)malloc(V * sizeof(struct subset));
	for (int i=0;i<V;i++)
	{
		subsets[i].parent = i;
		subsets[i].rank = 0;
	}
	int e=0,i=0;
	
	//main kruskal algo
	while( e < V-1 && i < E) 
	{
		struct Edge next_edge = graph.edge[i++];
		int x = find(subsets, next_edge.x);
		int y = find(subsets, next_edge.y);
		if (x!=y)
		{
			result[e++] = next_edge;
			Union(subsets,x,y);
		}
	}
	long mincost=0;
	for (int i=0;i<e;i++)
	{
		//std::cout<<result[i].x<<" "<<result[i].y<<" "<<result[i].w<<"\n";
		mincost+=result[i].w;
	}
	return mincost;

}



//printing graph for debug purposes
void printGraph(Graph graph)
{
	std::cout<<graph.V<<" "<<graph.E<<"\n";
	for (int i=0;i<graph.E;i++)
	{
		std::cout<<graph.edge[i].x<<" "<<graph.edge[i].y<<" "<<graph.edge[i].w<<"\n";
	}
}  
   
   

//obtain pivot element using partition for parallel quicksort 
int partition(Edge edge[], int low, int high){
	int i, j, key;
	Edge temp;
	key = edge[low].w; 
	i= low + 1;
	j= high;
	//std::cout<<"\nInside partition\n";
	while(1){
		while(i < high && key >= edge[i].w)
    			i++;
		while(key < edge[j].w)
    			j--;
		if(i < j){
			/*temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;*/
			temp.x = edge[i].x;
			temp.y = edge[i].y;
			temp.w = edge[i].w;
			
			edge[i].x = edge[j].x;
			edge[i].y = edge[j].y;
			edge[i].w = edge[j].w;
			
			edge[j].x = temp.x;
			edge[j].y = temp.y;
			edge[j].w = temp.w;
			
		}
		else{
			/*
			temp= arr[low];
			arr[low] = arr[j];
			arr[j]= temp;
			return(j);
			*/
			temp.x = edge[low].x;
			temp.y = edge[low].y;
			temp.w = edge[low].w;
			
			edge[low].x = edge[j].x;
			edge[low].y = edge[j].y;
			edge[low].w = edge[j].w;
			
			edge[j].x = temp.x;
			edge[j].y = temp.y;
			edge[j].w = temp.w;
			return(j);
			
		}
	}
}

// The main function that implements Parallel QuickSort
void quicksort(Edge edge[], int low, int high) //int arr[]
{
	int j;

	if(low < high){
		j = partition(edge, low, high);//arr
		
		//changing here
		/*
		#pragma omp parallel sections num_threads(8)
		{
		
			#pragma omp section
			{
				int tid;
				tid = omp_get_thread_num();
				if (tid ==5)
				printf("\n section thread id : %d \n",tid);
				quicksort(edge, low, j - 1); //arr
			}
			#pragma omp section
			{
				int tid;
				tid = omp_get_thread_num();
				if (tid==6)
				printf("\n section thread id : %d \n",tid);
				quicksort(edge, j + 1, high);//arr
			}
		}
		*/
		
		quicksort(edge, low, j - 1); //arr
		quicksort(edge, j + 1, high);//arr
		

	}
}

//parallel code ends



//serial code begins


// A utility function to swap two elements  
void swap(int* a, int* b)  
{  
    int t = *a;  
    *a = *b;  
    *b = t;  
}  
  
//partition function for serial implementation

int partitionserial (Edge edge[], int low, int high)  
{  
    int pivot = edge[high].w; 
    int i = (low - 1); // Index of smaller element  
    Edge temp;
    for (int j = low; j <= high - 1; j++)  
    {  
        // If current element is smaller than the pivot  
        if (edge[j].w < pivot) //arr[j]  
        {  
            i++; // increment index of smaller element  
            //swap(&arr[i], &arr[j]);
            temp.x = edge[i].x;
            temp.y = edge[i].y;
            temp.w = edge[i].w;
            
            edge[i].x = edge[j].x;
            edge[i].y = edge[j].y;
            edge[i].w = edge[j].w;
            
            edge[j].x = temp.x;
            edge[j].y = temp.y;
            edge[j].w = temp.w;
            
            
              
        }  
    }  
    //swap(&arr[i + 1], &arr[high]);  
    
    temp.x = edge[i+1].x;
    temp.y = edge[i+1].y;
    temp.w = edge[i+1].w;
            
    edge[i+1].x = edge[high].x;
    edge[i+1].y = edge[high].y;
    edge[i+1].w = edge[high].w;
            
    edge[high].x = temp.x;
    edge[high].y = temp.y;
    edge[high].w = temp.w;
    
    
    return (i + 1);  
}  
  
// Main quicksort function for serial execution
void quickSortserial(Edge edge[], int low, int high)  
{  
    if (low < high)  
    {  
        /* pi is partitioning index, arr[p] is now  
        at right place */
        int pi = partitionserial(edge, low, high);  
  
        // Separately sort elements before  
        // partition and after partition  
        quickSortserial(edge, low, pi - 1);  
        quickSortserial(edge, pi + 1, high);  
    }  
}  



///serial code ends


