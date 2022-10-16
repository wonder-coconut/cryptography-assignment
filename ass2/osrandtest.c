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

double kstest(double *sequence)
{
    int len = 30;
    int rangeL = 0;
    int rangeU = 20;

    double res1,res2 = 0.0;
    double max = 0;

    sort(sequence, len);

    for (int i = 0; i < len; i++)
    {
        double fyk_1 = (i)/(len * 1.0);
        double cdf = sequence[i]/(rangeU - rangeL);
        double fyk = (i+1)/(len * 1.0);
        double a = fabs(fyk_1 - cdf);
        double b = fabs(cdf - fyk);

        max = (max < a)? a : ((max < b)? b : max);

        //printf("%d.\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",i+1,sequence[i],fyk_1,cdf,fyk,a,b);
    }

    return max;
}

void driver(int test)
{
    int len;
    double quantile_95_left,quantile_95_right,quantile_99_left,quantile_99_right;
    if(!test)
    {
        len = 5000;

        quantile_95_left = 74.2219;
        quantile_95_right = 129.5612;
        quantile_99_left = 67.3276;
        quantile_99_right = 140.1695;
    }
    else
    {
        len = 30;
        
        quantile_95_left = 0;
        quantile_95_right = 0.24170;
        quantile_99_left = 0;
        quantile_99_right = 0.28988;
    }
    
    printf("Critical values for 95%% confidence: %lf %lf\n",quantile_95_left,quantile_95_right);
    printf("Critical values for 99%% confidence: %lf %lf\n",quantile_99_left,quantile_99_right);

    srand(time(NULL));
    int seedarray[13];

    for (int i = 0; i < 13; i++)
        seedarray[i] = rand();

    for (int i = 0; i < 13; i++)
    {
        printf("-*-*-*-*-*   TEST NO. %d   -*-*-*-*-*\n",(i+1));
        double res = 0;
        srand(seedarray[i]);

        switch (test)
        {
            case 0:
                int* chisequence = (int*)malloc(len*sizeof(int));
                for (int i = 0; i < len; i++)
                    chisequence[i] = rand() % 200 + 1;
                res = chisquaretest(chisequence);
                free(chisequence);
                break;

            case 1:
                double* kssequence = (double*)malloc(len*sizeof(double));
                for (int i = 0; i < len; i++)
                    kssequence[i] = (float)rand()/(RAND_MAX * 1.0) * 20;
                res = kstest(kssequence);
                free(kssequence);
                break;

            default:
                break;
        }
        
        printf("Test statistic: %lf\n",res);

        if(res <= quantile_95_left || res >= quantile_95_right)
            printf("(95%%) not random\n");
        else
            printf("(95%%) random\n");
        

        if(res <= quantile_99_left || res >= quantile_99_right)
            printf("(99%%) not random\n");
        else
            printf("(99%%) random\n");
    }
}

int main()
{
    printf("1. Chi Square Test (two tailed)\n2. Kolmogorov Smirnov Test (right tail)\nEnter your choice:");
    int test = 0;
    scanf("%d",&test);
    test--;
    driver(test);
}