#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

double eng_dist[] = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06996, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074 }; 

void swap(string *s1, string *s2)
{
	string temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

void sort(string s[], int len)
{
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			int a = stoi(s[i].substr(2,s[i].length() - 2));
			int b = stoi(s[j].substr(2,s[j].length() - 2));
			if(a > b)
				swap(&s[i],&s[j]);
		}
	}
}

int shiftcipher_cryptanalysis()
{

}

int main()
{
    ifstream infile;
    infile.open("process.txt");
    string cipher;

    getline(infile,cipher);

    int max_ngrams = 50;
    string ngrams[max_ngrams];
    string ngram1,ngram2;
    ngram1 = ngram2 = "";
    int keyrangel,keyrangeu,distance,ngram_i;
    keyrangel = 4;
    keyrangeu = 25;
    distance = ngram_i = 0;
    
    for (int i = 0; i < cipher.length(); i++)
    {
        distance = 0;
        ngram1 = cipher.substr(i,3);
        for (int j = i+1; j < cipher.length(); j++)
        {
            ngram2 = cipher.substr(j,3);
            if(ngram2.compare(ngram1) == 0)
            {
                distance = j - i;
                break;
            }
        }
        if(distance != 0)
            ngrams[ngram_i++] = ngram1 + to_string(distance);

        if(ngram_i >= max_ngrams)
            break;
    }

    int ngraph[max_ngrams][keyrangeu - keyrangel];

    for (int i = 0; i < max_ngrams; i++)
    {
        distance = stoi(ngrams[i].substr(3));
        
        for (int j = keyrangel; j <= keyrangeu; j++)
        {
            if(distance % j == 0)
                ngraph[i][j - 4] = 1;
            else
                ngraph[i][j - 4] = 0;
        }
    }
    int factor_count, maxfactor_count, keylen;
    factor_count = maxfactor_count = keylen = 0;

    for(int i = 0; i < keyrangeu - keyrangel ; i++)
    {
        factor_count = 0;
        for (int j = 0; j < max_ngrams; j++)
        {
            if(ngraph[j][i] == 1)
                factor_count++;
        }
        if(factor_count > maxfactor_count)
        {
            maxfactor_count = factor_count;
            keylen = i + 4;
        }
    }

    cout << "Key length: " << keylen << endl;
    string subcipher = "";

    for (int i = 0; i < keylen; i++)
    {
        for (int j = 0; j < cipher.length(); j += keylen)
        {
            subcipher += cipher[j];
        }
        cout << subcipher << endl;
    }
    
}