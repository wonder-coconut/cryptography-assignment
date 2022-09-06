#include <iostream>
#include <bits/stdc++.h>
#include <string>

using namespace std;

string genkeysquare(string key, char omit)
{//generate logical 5*5 key grid for playfair, stored as a continuous string variable
    int keyindex = 0;
    string keysquare = "";
    char keyfill = 'a';

    cout << "Omit: " << omit << endl;

    for (int i = 0; i < 25;)
    {
        if(keyindex < key.length())//until end of key
        {
            cout << keyindex << " " << (key[keyindex]==omit) << "\t" << key[keyindex] << " " << omit << endl;
            if(keysquare.find(key[keyindex]) > keysquare.length() && key[keyindex] != omit)//duplicatoin
            {
                keysquare += key[keyindex++];
                i++;
            }
            else
                keyindex++;
        }
        else
        {
            if(keysquare.find(keyfill) > keysquare.length() && keyfill != omit)//duplication, avoid omit character
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
    string s = genkeysquare("abcdefghijklmnopqrstuvwxyz",'j');
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << s[i*5+j] << ' ';
        }
        cout << endl;
    }
}