#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Size 10000
int main(int argc, char *argv[])
{
    srand((unsigned int)time(NULL));

    float a = 5.0;
    float arr[Size] = {};
    for (int i=0;i<Size;i++)
    {
        arr[i] = ((float)rand()/(float)(RAND_MAX)) * a;
    }

    for (int i = 0;i<Size;i++)
    {
        printf("%f \n",arr[i]);
    }
    return 0;
}