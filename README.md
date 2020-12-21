# HPC_parallel_kruskal

Files:

1. generateip.cpp

	//argument is filename to store the input
	
	//used for generating graphs with given V,E of format
	
	V E
	
	i i+1 w
	
	i+1 i+2 w
	
	i+2 i+3 w
	
	....
	
	
	
2. graphquicksort.h

	//contains function declarations and data structures
	
3. graphquicksort.cpp

	//contains function definitions for the functions in headerfile
	
4. testmain.cpp 

	//main function to run
	
	//provide input stored in file as argument
	
	
5. threadperf.cpp

	//same main function implemented for N=2,4 and 8 threads
	
	//provide input stored in file as argument
	
	
	
commands:

\>g++ -fopenmp graphquicksort.cpp testmain.cpp -o run

\>./run inputs/vertexcount<>

\>g++ -fopenmp graphquicksort.cpp threadperf.cpp -o runthread

\>./runthread inputs/vertexcount<>








