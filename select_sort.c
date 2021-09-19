#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<sys/time.h>
#include<omp.h>
#define Size 10000
void swap(float *xp, float *yp)
{
    float temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
void selectionSort(float arr[], int n)
{
    int i, j, min_idx;
 
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        #pragma omp parallel 
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;
 
        // Swap the found minimum element with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}
 
/* Function to print an array */
void printArray(float arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
    {
        printf("%f \n", arr[i]);
    }
}
 
// Driver program to test above functions
int main()
{
    srand((unsigned int)time(NULL));
    struct timeval start, end;
    gettimeofday(&start, NULL);
    double store_time[8];
    float a = 10.0;
    float arr[Size] = {};
    for (int i=0;i<Size;i++)
    {
        arr[i] = ((float)rand()/(float)(RAND_MAX)) * a;
    }
    selectionSort(arr, Size);
    printf("Sorted array: \n");
    printArray(arr, Size);
    gettimeofday(&end, NULL);
    double delta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
    printf("Delta = %f \n",delta);  
    return 0;
}