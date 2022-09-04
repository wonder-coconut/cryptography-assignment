#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>

using namespace std;

char shift_char_right(char ch, int shift)
{
    int lower,upper,ascii;
    if(isupper(ch))
        lower = 65;
    else
        lower = 97;
    
    upper = lower + 26;
    ascii = ch;
    if(ascii + shift - lower < 0)
        ascii = (ascii + shift - lower) % 26 + upper; 
    else
        ascii = (ascii + shift - lower) % 26 + lower;
    ch = ascii;
    
    return ch;

}
/*
string shift_right(string temp, int shift)
{  
}*/

int ceaser(int shift, int decode)
{
    ifstream infile;
    infile.open("process.txt");
    string temp1,temp2,cipher;

    cipher = "";

    while(getline(infile,temp1))
    {
        stringstream str(temp1);
        while(str)
        {
            if(str.eof() == 1)
                break;
            str >> temp2;

            for (int i = 0; i < temp2.length(); i++)
            {
                temp2[i] = shift_char_right(temp2[i], pow(-1,decode) * shift);
            }

            cipher = cipher + temp2 + " ";
        }
        cipher = cipher + "\n";
    }
    cout << cipher;
    return 1;
}

int vignere(string key, int decode)
{
    ifstream infile;
    infile.open("process.txt");
    string temp1,temp2,cipher;
    int keylower, keyupper, keyascii, shift;
    keylower = keyupper = shift = keyascii = 0;
    int keyindex = 0;

    while(getline(infile,temp1))
    {
        stringstream str(temp1);
        while(str)
        {
            if(str.eof() == 1)
                break;
            str >> temp2;
            
            for(int i = 0; i < temp2.length(); i++)
            {
                if(isupper(key[keyindex % key.length()]))
                    keylower = 65;
                else
                    keylower = 97;
                //keyupper = keylower + 26;

                shift = key[keyindex % key.length()] - keylower;

                temp2[i] = shift_char_right(temp2[i], pow(-1,decode) * shift);

                keyindex++;
            }
            cipher = cipher + temp2 + " ";
        }
        cipher = cipher + "\n";
    }
    cout << cipher;
    return 0;
}

int playfair(string key, int decode)
{
    cout << key;
    return 0;
}

int main()
{
    int ch,decode;
    cout << "1. Ceaser Cipher\n2. Vignere Cipher\n3. Playfair Cipher\nEnter your choice (1/2/3): ";
    cin >> ch;
    cout << "Encode or Decode? (0,1): ";
    cin >> decode;
    int shift;
    string key;

    switch (ch)
    {
        case 1:
            cout << "Enter shift value: ";
            cin >> shift;
            ceaser(shift, decode);
            break;
        
        case 2:
            cout << "Enter key: ";
            cin >> key;
            vignere(key, decode);
            break;
        
        case 3:
            cout << "Enter key: ";
            cin >> key;
            playfair(key, decode);
            break;
        
        default:
            cout << "Invalid input\n";
            break;
    }
}