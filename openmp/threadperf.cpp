#include <iostream>
#include <omp.h>
#include <unistd.h>
#include "graphquicksort.h"
#include <fstream>
//#define n 100000
int arr[n];
int arr1[n];


struct Graph graph1;
struct Graph graph2;
struct Graph graph3;
struct Graph graph4;

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
	graph3.V = V;
	graph3.E = E;
	graph4.V = V;
	graph4.E = E;
	
	
	for (int i=0;i<E;i++)
	{
		file>>x>>y>>w;
		
		graph1.edge[i].x = x;
		graph1.edge[i].y = y;
		graph1.edge[i].w = w;
		
		graph2.edge[i].x = x;
		graph2.edge[i].y = y;
		graph2.edge[i].w = w;
		
		graph3.edge[i].x = x;
		graph3.edge[i].y = y;
		graph3.edge[i].w = w;
		
		graph4.edge[i].x = x;
		graph4.edge[i].y = y;
		graph4.edge[i].w = w;
	}
	
	
	
	////////////////Parallel Execution/////////////////
	
	
	
	
	std::cout<<"Parallel Execuion using 2 threads \n\n";
	std::cout<<"Calling Parallel QuickSort\n";
	
	//printGraph(graph1);
	
	int start_s=clock();//start time
	int j1,j2,j11,j12,j21,j22;
	int j = partition(graph1.edge,0,E-1);// returns the pivot element
	
	#pragma omp parallel sections num_threads(2)
	{
		#pragma omp section
		{	/*
			int tid;
			tid = omp_get_thread_num();
			printf("\n section 1 thread id : %d \n",tid);*/
        		quicksort(graph1.edge ,0, j - 1);//Thread 1
    		}
		#pragma omp section
		{	/*
			int tid;
			tid = omp_get_thread_num();
			printf("\n section 2 thread id : %d \n",tid);*/
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
	
	
	//sleep(1);
	
	
	
	//////////////////4 threads//////////////////////
	
	
	
	std::cout<<"Parallel Execuion using 4 threads \n\n";
	std::cout<<"Calling Parallel QuickSort\n";
	
	//printGraph(graph1);
	
	start_s=clock();//start time
	j = partition(graph3.edge,0,E-1);// returns the pivot element
	
	j1 = partition(graph3.edge,0,j);
	j2 = partition(graph3.edge,j,E-1);
	#pragma omp parallel sections num_threads(4)
	{
		#pragma omp section
		{	/*
			int tid;
			tid = omp_get_thread_num();
			printf("\n section 1 thread id : %d \n",tid);*/
        		quicksort(graph3.edge ,0, j1 - 1);//Thread 1
    		}
		#pragma omp section
		{	/*
			int tid;
			tid = omp_get_thread_num();
			printf("\n section 2 thread id : %d \n",tid);*/
        		quicksort(graph3.edge, j1 + 1, j-1);//Thread 2
   		}
   		#pragma omp section
		{	/*
			int tid;
			tid = omp_get_thread_num();
			printf("\n section 3 thread id : %d \n",tid);*/
        		quicksort(graph3.edge ,j, j2 - 1);//Thread 3
    		}
		#pragma omp section
		{	/*
			int tid;
			tid = omp_get_thread_num();
			printf("\n section 4 thread id : %d \n",tid);*/
        		quicksort(graph3.edge, j2 + 1, E-1);//Thread 4
   		}
	}
	std::cout<<"Ended Sorting\n";
	
	//printGraph(graph1);
	
	mincost = kruskals(graph3);
	stop_s=clock();//end Time
	
	
	//printing results
	
	std::cout<<"Minimuim cost : "<<mincost<<"\n";
	printf("Time taken: %.6fs\n\n\n", (double)(stop_s - start_s)/CLOCKS_PER_SEC);
	
	
	
	
	//sleep(1);
	
	/////////parallel execution using 8 threads ////////////
	
	
	
	
	
	
	std::cout<<"Parallel Execuion using 8 threads \n\n";
	std::cout<<"Calling Parallel QuickSort\n";
	
	//printGraph(graph1);
	
	start_s=clock();//start time
	j = partition(graph4.edge,0,E-1);// returns the pivot element
	
	j1 = partition(graph4.edge,0,j);
	j2 = partition(graph4.edge,j,E-1);
	
	j11 = partition(graph4.edge,0,j1);
	j12 = partition(graph4.edge,j1,j);
	j21 = partition(graph4.edge,j,j2);
	j22 = partition(graph4.edge,j2,E-1);
	
	#pragma omp parallel sections num_threads(8)
	{
		#pragma omp section
		{	/*
			int tid;
			tid = omp_get_thread_num();
			printf("\n section 1 thread id : %d \n",tid);*/
        		quicksort(graph4.edge ,0, j11 - 1);//Thread 1
    		}
		#pragma omp section
		{/*
			int tid;
			tid = omp_get_thread_num();
			printf("\n section 2 thread id : %d \n",tid);*/
        		quicksort(graph4.edge, j11 + 1, j1-1);//Thread 2
   		}
   		#pragma omp section
		{/*
			int tid;
			tid = omp_get_thread_num();
			printf("\n section 3 thread id : %d \n",tid);*/
        		quicksort(graph4.edge ,j1, j12 - 1);//Thread 3
    		}
		#pragma omp section
		{/*
			int tid;
			tid = omp_get_thread_num();
			printf("\n section 4 thread id : %d \n",tid);*/
        		quicksort(graph4.edge, j12 + 1, j-1);//Thread 4
   		}
   		#pragma omp section
		{/*
			int tid;
			tid = omp_get_thread_num();
			printf("\n section 5 thread id : %d \n",tid);*/
        		quicksort(graph4.edge ,j, j21 - 1);//Thread 5
    		}
		#pragma omp section
		{/*
			int tid;
			tid = omp_get_thread_num();
			printf("\n section 6 thread id : %d \n",tid);*/
        		quicksort(graph4.edge, j21 + 1, j2-1);//Thread 6
   		}
   		#pragma omp section
		{/*
			int tid;
			tid = omp_get_thread_num();
			printf("\n section 7 thread id : %d \n",tid);*/
        		quicksort(graph4.edge ,j2, j22 - 1);//Thread 7
    		}
		#pragma omp section
		{/*
			int tid;
			tid = omp_get_thread_num();
			printf("\n section 8 thread id : %d \n",tid);*/
        		quicksort(graph4.edge, j22 + 1, E-1);//Thread 8
   		}
	}
	std::cout<<"Ended Sorting\n";
	
	//printGraph(graph1);
	
	mincost = kruskals(graph4);
	stop_s=clock();//end Time
	
	
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
