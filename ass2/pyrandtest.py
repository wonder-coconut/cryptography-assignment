
import random

def sort(randsequence, len):
    
    i = 0
    while(i < len):
        j = 0
        while(j < len):
            if(randsequence[i] < randsequence[j]):
                temp = randsequence[i]
                randsequence[i] = randsequence[j]
                randsequence[j] = temp
            j += 1
        i += 1

def chisquaretest(randsequence):
    
    len = 5000
    rangeL = 1
    rangeU = 200
    n = 100
    freq = []

    res = 0.0

    i = 0
    while(i < n):
        freq.append(0)
        i += 1
    
    j = 0
    i = 0
    while(i < len):
        j = 0
        while(j < n):
            if(randsequence[i] <= (j + 1) * (rangeU - rangeL + 1)/n):
                freq[j] += 1
                break

            j += 1
        i += 1
    
    i = 0

    while(i < n):
        res += pow((1.0 * freq[i] - len/n),2)/(len/n)
        i += 1

    return res
#end of function

def kstest(randsequence):
    len = 30
    rangeL = 0
    rangeU = 20

    max = 0

    sort(randsequence, len)

    i = 0
    
    while(i < len):
        fyk_1 = (i)/(len * 1.0)
        cdf = randsequence[i]/(rangeU - rangeL)
        fyk = (i+1)/(len * 1.0)
        a = abs(fyk_1 - cdf)
        b = abs(cdf - fyk)

        max = a if (max < a) else (b if (max < b) else max)

        #print(f"{i}\t{randsequence[i]}\t{fyk_1}\t{cdf}\t{fyk}\t{a}\t{b}\t")
        
        i += 1

    return max

def driver(test):
    randsequence = []
    seedlist = []

    i = 0

    while(i < 13):
        seedlist.append(random.random()*200)
        i = i + 1
    
    if(test == 0):
        len = 5000

        quantile_95_left = 74.2219
        quantile_95_right = 129.5612
        quantile_99_left = 67.3276
        quantile_99_right = 140.1695
    else:
        len = 30

        quantile_95_left = 0
        quantile_95_right = 0.24170
        quantile_99_left = 0
        quantile_99_right = 0.28988


    print("Critical values for 95% confidence: ",quantile_95_left,quantile_95_right)
    print("Critical values for 99% confidence: ",quantile_99_left,quantile_99_right)

    c = 0
    for seed in seedlist:

        random.seed(seed)
        randsequence = []

        print(f"-*-*-*-*-*   TEST NO. {c + 1}    -*-*-*-*-*")
        i = 0

        match test:
            case 0:
                while(i < len):
                    randsequence.append(random.randint(1,200))
                    i += 1
                res = chisquaretest(randsequence)
            case 1:
                while(i < len):
                    randsequence.append(random.uniform(0,20))
                    i += 1
                res = kstest(randsequence)
        
        c += 1
        
        print(res)

        if(res <= quantile_95_left or res >= quantile_95_right):
            print("(95%) not random")
        else:
            print("(95%) random")


        if(res <= quantile_99_left or res >= quantile_99_right):
            print("(99%) not random")
        else:
            print("(99%) random")

driver(1)