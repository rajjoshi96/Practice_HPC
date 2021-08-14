#include<stdio.h>
// int swap(int *a,int *b){
//     int t;
//     t = *a;
//     *a = *b;
//     *b = t;
// }
// int pivot_last(int array[], int low, int high) {
// 	int pivot = array[high];
// 	int i = (low - 1);
 
// 	for (int j = low; j < high; j++) {
// 		if (array[j] < pivot) {
// 		    swap(&array[++i], &array[j]);
// 		}
// 	}
 
// 	swap(&array[i + 1], &array[high]);
// 	return (i + 1);
// }

// int pivot_median(int arra[],int low,int high){
//     int pivot;
//     int mid = (high + low)/ 2;
//     if(arra[mid] < arra[low])
//     {
//         swap(&arra[mid],&arra[low]);
//     }
//     if(arra[high] < arra[low])
//     {
//         swap(&arra[high], &arra[low]);
//     }
//     if(arra[high]< arra[mid])
//     {
//         swap(&arra[mid],&arra[high]);
//     }
//     swap(&arra[mid],&arra[high-1]);
//     pivot = arra[high-1];
//     return pivot_last(arra, low,high);
// }
// int quick(int a[], int low, int high){
//     if(low< high)
//     {
//         int pi = pivot_median(a , low, high);
//         pivot_median(a ,low,pi-1);
//         pivot_median(a, pi + 1, high);
//     }
// }
// int main()
// {
//     int arr[]={12,56,78,45,999,414,333,2,8558,38,98,9434313};
//     int size = sizeof(arr)/sizeof(arr[0]);
//     printf("Before Sorting array: \n");
//     for(int i = 0;i < size;i++){
//         printf("%d \t", arr[i]);
//     }
//     printf("\n");
//     quick(arr,0,size-1);
//     printf("After quick sort with Median \n");
//     for(int i=0;i<size;i++)
//     {
//         printf("%d \t", arr[i]);
//     }
//     getchar();
//     return 0;
// }



#include <stdio.h>
#include <stdlib.h>
 
void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}
 
int partition_pivot_last(int array[], int low, int high) {
	int pivot = array[high];
	int i = (low - 1);
 
	for (int j = low; j < high; j++) {
		if (array[j] < pivot) {
		swap(&array[++i], &array[j]);
		}
	}
 
	swap(&array[i + 1], &array[high]);
	return (i + 1);
}
 
// int partition_pivot_first(int array[], int low, int high) {
// 	int pivot = array[low];
// 	int i = (low + 1);
 
// 	for (int j = low + 1; j <= high; j++) {
// 		if (array[j] < pivot) {
// 		if (j != i) {
// 		swap(&array[i], &array[j]);
// 		}
// 		i++;
// 		}
// 	}
 
// 	swap(&array[i - 1], &array[low]);
// 	return (i - 1);
// }
 
// int partition_pivot_random(int array[], int low, int high) {
// 	int pivot;
// 	int n = rand();
// 	pivot = low + n % (high - low + 1); // Randomizing the pivot
// 	return partition_pivot_last(array, low, high);
// }
 
int partition_pivot_median(int array[], int low, int high) {
	
	int pivot;
	int mid = (low + high) / 2;
	if (array[mid] < array[low]) 
		swap(&array[mid], &array[low]);
	if (array[high] < array[low])
		swap(&array[high], &array[low]);
	if (array[high] < array[mid])
		swap(&array[high], &array[mid]);
	swap(&array[mid], &array[high-1]);
	
	pivot = array[high-1];
 
	return partition_pivot_last(array, low, high);
}
 
void quickSort(int array[], int low, int high) {	
	if (low < high) {
		//int pi = partition_pivot_first(array, low, high);
		//int pi = partition_pivot_last(array, low, high);
		//int pi = partition_pivot_random(array, low, high);
		int pi = partition_pivot_median(array, low, high);
 
		// Sort the elements on the left of pivot
		quickSort(array, low, pi - 1);
 
		// Sort the elements on the right of pivot
		quickSort(array, pi + 1, high);
	}
}
 
int main(void) {
	int array[] = {12,56,78,45,999,414,333,2,8558,38,98,9434313};
	int size = sizeof(array) / sizeof(array[0]);
	for (int i = 0; i < size; i++)
		printf("|%d", array[i]);
	printf("\n");
 
	quickSort(array, 0, size - 1);
 
	printf("\n");
	for (int i = 0; i < size; i++)
		printf("|%d \t", array[i]);
 
	//getchar();
	return 0;
}