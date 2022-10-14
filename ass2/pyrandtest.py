
import random

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

randsequence = []
seedlist = []

i = 0

while(i < 13):
    seedlist.append(random.random()*200)
    i = i + 1

len = 5000

criticalchi95_left = 74.2219
criticalchi95_right = 129.5612

criticalchi99_left = 67.3276
criticalchi99_right = 140.1695

print("Critical values for 95% confidence: ",criticalchi95_left,criticalchi95_right)
print("Critical values for 99% confidence: ",criticalchi99_left,criticalchi99_right)

c = 0
for seed in seedlist:

    random.seed(seed)
    randsequence = []

    print(f"-*-*-*-*-*   TEST NO. {c + 1}    -*-*-*-*-*")
    i = 0

    while(i < len):
        randsequence.append(random.randint(1,200))
        i = i + 1

    res = chisquaretest(randsequence)
    c += 1
    print(res)

    if(res <= criticalchi95_left or res >= criticalchi95_right):
        print("(95%) not random")
    else:
        print("(95%) random")
        

    if(res <= criticalchi99_left or res >= criticalchi99_right):
        print("(99%) not random")
    else:
        print("(99%) random")