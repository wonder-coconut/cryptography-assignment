#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

void swap(double *a, double *b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}

void sort(double *sequence, int len)
{
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            if(sequence[i] < sequence[j])
                swap(&sequence[i], &sequence[j]);
        }
    }
}

int main()
{
    double *sequence = (double*)malloc(5 * sizeof(double));
    for (int i = 0; i < 5; i++)
    {
        sequence[i] = (float)rand()/(RAND_MAX * 1.0) * 20;
        printf("%lf ",sequence[i]);
    }
    printf("\n");
    sort(sequence, 5);
    for (int i = 0; i < 5; i++)
    {
        printf("%lf ",sequence[i]);
    }
    
}