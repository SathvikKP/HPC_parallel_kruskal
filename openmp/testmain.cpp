#include <iostream>
#include <omp.h>
#include "graphquicksort.h"
#include <fstream>
//#define n 100000
int arr[n];
int arr1[n];


struct Graph graph1;
struct Graph graph2;


int main(int argc,char* argv[])
{	
	int x,y,w;
	
	///////////Getting the input from a file///////////////
	
	char* inputfile = argv[1];
	std::fstream file(inputfile, std::ios_base::in);
	int V,E;
	file>>V>>E;
	graph1.V = V;
	graph1.E = E;
	graph2.V = V;
	graph2.E = E;
	
	
	for (int i=0;i<E;i++)
	{
		file>>x>>y>>w;
		
		graph1.edge[i].x = x;
		graph1.edge[i].y = y;
		graph1.edge[i].w = w;
		
		graph2.edge[i].x = x;
		graph2.edge[i].y = y;
		graph2.edge[i].w = w;
	}
	
	
	
	////////////////Parallel Execution/////////////////
	
	
	
	
	std::cout<<"Parallel Execuion \n\n";
	std::cout<<"Calling Parallel QuickSort\n";
	
	//printGraph(graph1);
	
	int start_s=clock();//start time
	int j = partition(graph1.edge,0,E-1);// returns the pivot element
	
	//quicksort(graph1.edge,0,E-1);
	
	#pragma omp parallel sections num_threads(2)
	{
		#pragma omp section
		{
			int tid;
			tid = omp_get_thread_num();
			printf("\n section 1 thread id : %d \n",tid);
        		quicksort(graph1.edge ,0, j - 1);//Thread 1
    		}
		#pragma omp section
		{
			int tid;
			tid = omp_get_thread_num();
			printf("\n section 2 thread id : %d \n",tid);
        		quicksort(graph1.edge, j + 1, E-1);//Thread 2
   		}
	}
	std::cout<<"Ended Sorting\n";
	
	//printGraph(graph1);
	
	long mincost = kruskals(graph1);
	int stop_s=clock();//end Time
	
	//printing results
	
	std::cout<<"Minimuim cost : "<<mincost<<"\n";
	printf("Time taken: %.6fs\n\n\n", (double)(stop_s - start_s)/CLOCKS_PER_SEC);
	
	
	
	
	
	
	/////////////////serial execution//////////////////
	
	



	std::cout<<"Serial Execution\n\n";
	std::cout<<"Calling Serial QuickSort\n"; 
	
	//printGraph(graph2);
	
	start_s=clock();//start time
	
	quickSortserial(graph2.edge,0,E-1);
	
	std::cout<<"Ended Sorting\n";
	
	//printGraph(graph2);
	
	mincost = kruskals(graph2);
	stop_s=clock();//end Time
	
	//printing results
	
	std::cout<<"Minimuim cost : "<<mincost<<"\n";
	printf("Time taken: %.6fs\n\n", (double)(stop_s - start_s)/CLOCKS_PER_SEC);
	
	
	

	/////////IGNORE////////////
	
	
}
