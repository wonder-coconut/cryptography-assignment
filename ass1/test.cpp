#include <iostream>
#include <bits/stdc++.h>
#include <string>

using namespace std;

string genkeysquare(string key, char omit)
{//generate logical 5*5 key grid for playfair, stored as a continuous string variable
    int keyindex = 0;
    string keysquare = "";
    char keyfill = 'a';
    for (int i = 0; i < 25;)
    {
        if(keyindex < key.length())//until end of key
        {
            if(keysquare.find(key[keyindex]) > keysquare.length())//duplicatoin
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
    string s = genkeysquare("blah",'j');
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << s[i*5+j] << ' ';
        }
        cout << endl;
        
    }
    
}