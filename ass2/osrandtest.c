#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

double chisquaretest(int *sequence)
{
    int len = 5000;
    int rangeL = 1;
    int rangeU = 200;
    int n = 100;
    int freq[n];

    double res = 0;

    for (int i = 0; i < n; i++)
    {
        freq[i] = 0;
    }

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (sequence[i] <= (j + 1) * (rangeU - rangeL + 1)/n)
            {
                freq[j]++;
                break;
            }
        }
    }

    /*for (int i = 0; i < n; i++)
    {
        printf("%d\n",freq[i]);
    }*/
    

    for (int i = 0; i < n; i++)
    {
        res += pow((1.0 * freq[i] - len/n),2)/(len/n);
    }

    return res;
}

int main()
{
    int len = 5000;

    double criticalchi95_left = 74.2219;
    double criticalchi95_right = 129.5612;
    
    double criticalchi99_left = 67.3276;
    double criticalchi99_right = 140.1695;
    
    printf("Critical values for 95%% confidence: %lf %lf\n",criticalchi95_left,criticalchi95_right);
    printf("Critical values for 99%% confidence: %lf %lf\n",criticalchi99_left,criticalchi99_right);

    srand(time(NULL));
    int seedarray[13];

    for (int i = 0; i < 13; i++)
    {
        seedarray[i] = rand();
    }

    for (int i = 0; i < 13; i++)
    {
        printf("-*-*-*-*-*   TEST NO. %d   -*-*-*-*-*\n",(i+1));

        int* sequence = (int*)malloc(len*sizeof(int));

        srand(seedarray[i]);

        for (int i = 0; i < len; i++)
        {
            sequence[i] = rand() % 200 + 1;
        }

        double res = chisquaretest(sequence);
        free(sequence);

        printf("%lf\n",res);

        if(res <= criticalchi95_left || res >= criticalchi95_right)
            printf("(95%%) not random\n");
        else
            printf("(95%%) random\n");
        

        if(res <= criticalchi99_left || res >= criticalchi99_right)
            printf("(99%%) not random\n");
        else
            printf("(99%%) random\n");
    }
}