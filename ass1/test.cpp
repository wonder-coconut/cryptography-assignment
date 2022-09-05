#include <iostream>
#include <bits/stdc++.h>
#include <string>

using namespace std;


string genkeysquare(string key, char omit)
{
    int keyindex = 0;
    string keysquare = "";
    char keyfill = 'a';
    for (int i = 0; i < 25;)
    {
        if(keyindex < key.length())
        {
            if(keysquare.find(key[keyindex]) > keysquare.length())
            {
                keysquare += key[keyindex++];
                i++;
            }
            else
                keyindex++;
        }
        else
        {
            if(keysquare.find(keyfill) > keysquare.length() && keyfill != omit)
            {
                keysquare += keyfill++;
                i++;
            }
            else
                keyfill++;
        }
    }
    
    return keysquare;
}

int main()
{
    string key = "aabababbasbd";
    char omit = 'b';
    string keysquare = genkeysquare(key, omit);

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            cout << keysquare[i*5 + j] << " ";
        }
        cout << endl;
    }
}