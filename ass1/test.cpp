#include <iostream>
#include <bits/stdc++.h>
#include <string>

using namespace std;

int main()
{
    string s = "abc";
    int i = 4;
    cout << s[i % s.length()] - 97;    
}