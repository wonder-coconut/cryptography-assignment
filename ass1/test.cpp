#include <iostream>
#include <bits/stdc++.h>
#include <string>

using namespace std;


void lower(string *plaintext)
{
    for (int i = 0; i < plaintext->length(); i++)
    {
        if(isupper((*plaintext)[i]))
            (*plaintext)[i] += 32;
    }   
}

int main()
{
    string str;
    str = "aBcD";
    lower(&str);
    cout << str;
}