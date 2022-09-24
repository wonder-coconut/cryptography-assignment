#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

void initialize_dist(double arr[26])
{
    for (int i = 0; i < 26; i++)
        arr[i] = 0.0;
}

int main()
{
    ifstream infile;
    infile.open("process.txt");
    string cipher;
    char ch;
    
    getline(infile,cipher);

    double cipher_dist[26];
    initialize_dist(cipher_dist);
    double increment = 1.0/cipher.length();

    double eng_dist[] = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06996, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074 }; 

    for (int i = 0; i < cipher.length(); i++)
    {
        ch = cipher[i];
        cipher_dist[ch - 65] += increment;
    }
    
    double eng_max,cipher_max;
    int eng_max_i,cipher_max_i;
    eng_max = cipher_max = eng_max_i = cipher_max_i = 0;

    for (int i = 0; i < 26; i++)
    {
        if(eng_max < eng_dist[i])
        {
            eng_max = eng_dist[i];
            eng_max_i = i;
        }
        if(cipher_max < cipher_dist[i])
        {
            cipher_max = cipher_dist[i];
            cipher_max_i = i;
        }
    }

    int shift = (cipher_max_i - eng_max_i) > 0 ? cipher_max_i - eng_max_i : cipher_max_i - eng_max_i + 26;

    cout << shift << endl;
}