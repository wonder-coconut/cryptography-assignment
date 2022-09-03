#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>

using namespace std;

string shift_right(string temp, int shift)
{
    int lower = 0;
    int ascii = 0;
    for (int i = 0; i < temp.length(); i++)
    {
        if(isupper(temp[i]))
            lower = 65;
        else
            lower = 97;
        
        ascii = temp[i];
        ascii = (ascii + shift - lower) % 26 + lower;
        temp[i] = ascii;
    }
    return temp;    
}

int ceaser(int shift)
{
    ifstream infile;
    infile.open("process.txt");
    string temp1,temp2,cipher;
    
    int lower = 0;
    cipher = "";

    while(getline(infile,temp1))
    {
        stringstream str(temp1);
        while(str)
        {
            if(str.eof() == 1)
                break;
            str >> temp2;
            temp2 = shift_right(temp2,shift);
            cipher = cipher + temp2 + " ";
        }
        cipher = cipher + "\n";
    }
    cout << cipher;
    return 0;
}

int vignere(string key)
{
    cout << key;
    return 0;
}

int playfair(string key)
{
    cout << key;
    return 0;
}

int main()
{
    int ch;
    cout << "1. Ceaser Cipher\n2. Vignere Cipher\n3. Playfair Cipher\nEnter your choice (1/2/3): ";
    cin >> ch;
    int shift;
    string key;

    switch (ch)
    {
        case 1:
            cout << "Enter shift value: ";
            cin >> shift;
            ceaser(shift);
            break;
        
        case 2:
            cout << "Enter key: ";
            cin >> key;
            vignere(key);
            break;
        
        case 3:
            cout << "Enter key: ";
            cin >> key;
            playfair(key);
            break;
        
        default:
            cout << "Invalid input\n";
            break;
    }
}