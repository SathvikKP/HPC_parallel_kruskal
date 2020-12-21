#include<iostream>
//#define n 100000000
#define n 100000000
//int arr[n];
//int arr1[n];
/* This function takes first element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
   
   
   
   
   
   
   
//parallel code begins   


int partition(int arr[], int low, int high){
	int i, j, temp, key;
	key = arr[low];
	i= low + 1;
	j= high;
	while(1){
		while(i < high && key >= arr[i])
    			i++;
		while(key < arr[j])
    			j--;
		if(i < j){
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
		else{
			temp= arr[low];
			arr[low] = arr[j];
			arr[j]= temp;
			return(j);
		}
	}
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quicksort(int arr[], int low, int high)
{
	int j;

	if(low < high){
		j = partition(arr, low, high);

		quicksort(arr, low, j - 1);
		quicksort(arr, j + 1, high);

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
  
/* This function takes last element as pivot, places  
the pivot element at its correct position in sorted  
array, and places all smaller (smaller than pivot)  
to left of pivot and all greater elements to right  
of pivot */
int partitionserial (int arr[], int low, int high)  
{  
    int pivot = arr[high]; // pivot  
    int i = (low - 1); // Index of smaller element  
  
    for (int j = low; j <= high - 1; j++)  
    {  
        // If current element is smaller than the pivot  
        if (arr[j] < pivot)  
        {  
            i++; // increment index of smaller element  
            swap(&arr[i], &arr[j]);  
        }  
    }  
    swap(&arr[i + 1], &arr[high]);  
    return (i + 1);  
}  
  
/* The main function that implements QuickSort  
arr[] --> Array to be sorted,  
low --> Starting index,  
high --> Ending index */
void quickSortserial(int arr[], int low, int high)  
{  
    if (low < high)  
    {  
        /* pi is partitioning index, arr[p] is now  
        at right place */
        int pi = partitionserial(arr, low, high);  
  
        // Separately sort elements before  
        // partition and after partition  
        quickSortserial(arr, low, pi - 1);  
        quickSortserial(arr, pi + 1, high);  
    }  
}  





///serial code ends

















//main function

/*

int main()
{	
	for(int i=0;i<n;i++){
		arr[i]=rand()%n;//filling random value
		arr1[i]=arr[i];
	}
	int start_s=clock();//start time
	int j = partition(arr,0,n-1);// returns the pivot element
		#pragma omp parallel sections
		{
			#pragma omp section
			{
        			quicksort(arr,0, j - 1);//Thread 1
    			}
			#pragma omp section
			{
        			quicksort(arr, j + 1, n-1);//Thread 2
   			}
		}
	int stop_s=clock();//end Time
	printf("Time taken: %.6fs\n", (double)(stop_s - start_s)/CLOCKS_PER_SEC);
	
	start_s=clock();//start time
	quickSortserial(arr1,0,n-1);
	stop_s=clock();//end Time
	printf("Time taken: %.6fs\n", (double)(stop_s - start_s)/CLOCKS_PER_SEC);
	
	
}*/
