#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include<omp.h>
#include<sys/time.h>
#define Size 10000

struct Compare { int val; int index; };
#pragma omp declare reduction(maximum : struct Compare : omp_out = omp_in.val > omp_out.val ? omp_in : omp_out)

void selectionsort(float* arr, int size)
{
    for (int i = size - 1; i > 0; --i)
    {
        struct Compare max;
        max.val = arr[i];
        max.index = i;
        #pragma omp parallel for reduction(maximum:max)
        for (int j = i - 1; j >= 0; --j)
        {
            if (arr[j] > max.val)
            {
                max.val = arr[j];
                max.index = j;
            }
        }
        int tmp = arr[i];
        arr[i] = max.val;
        arr[max.index] = tmp;
    }
}

int main(int argc,char *argv[])
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
    };
    selectionsort(arr, 10);

    for (int i = 0; i < Size; i++)
        printf("%f\n", arr[i]);
    gettimeofday(&end, NULL);
    double delta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
    printf("Delta = %f \n",delta);  
    return 0;
}