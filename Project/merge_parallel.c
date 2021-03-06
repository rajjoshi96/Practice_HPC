

#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include<sys/time.h>
#include<omp.h>
#define Size 100000

// function to sort the subsection a[i .. j] of the array a[]
void merge_sort(int i, int j, float a[], float aux[]) {
    if (j <= i) {
        return;     // the subsection is empty or a single element
    }
    int mid = (i + j) / 2;
    int pointer_left = i;       // pointer_left points to the beginning of the left sub-array
    int pointer_right = mid + 1;        // pointer_right points to the beginning of the right sub-array
    int k;      // k is the loop counter

        #pragma omp parallel
        {
            #pragma omp sections
            {
                #pragma omp section
                {
                    merge_sort(i, mid, a, aux);     // sort the left sub-array recursively
                }
                #pragma omp section
                {
                    merge_sort(mid + 1, j, a, aux);     // sort the right sub-array recursively
                }
            }

        }
        // left sub-array is a[i .. mid]
        // right sub-array is a[mid + 1 .. j]
        
        //merge_sort(i, mid, a, aux);     // sort the left sub-array recursively
        //merge_sort(mid + 1, j, a, aux);     // sort the right sub-array recursively



        // we loop from i to j to fill each element of the final merged array
            #pragma omp critical
            {
            for (k = i; k <= j; k++) 
            {
                if (pointer_left == mid + 1) {      // left pointer has reached the limit
                    aux[k] = a[pointer_right];
                    pointer_right++;
                } else if (pointer_right == j + 1) {        // right pointer has reached the limit
                    aux[k] = a[pointer_left];
                    pointer_left++;
                } else if (a[pointer_left] < a[pointer_right]) {        // pointer left points to smaller element
                    aux[k] = a[pointer_left];
                    pointer_left++;
                } else {        // pointer right points to smaller element
                    aux[k] = a[pointer_right];
                    pointer_right++;
                }
            }

            for (k = i; k <= j; k++) {      //creating duplicate copy of array
                a[k] = aux[k];
            }
            }   
}


int main() {
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
    float aux[Size]={};
    float n=Size;
    merge_sort(0, n - 1, arr, aux);
    printf("Printing the sorted array:\n");
    for (int i = 0; i < n; i++){
        printf("%f \n", arr[i]);
    }
    gettimeofday(&end, NULL);
    double delta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
    printf("Delta = %f \n",delta); 
    return 0;
}