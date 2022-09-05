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

int ceaser(int shift, int decode)
{
    //sanity checks:
    //text is only alphabet
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
    //sanity checks:
    //key and text contains only alphabets
    //key is only lowercase
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

char calc_omit(string key)
{   //todo
    return 'j';
}

char calc_junk(string plaintext)
{
    //todo
    return 'x';
}

void lower(string *plaintext)
{
    for (int i = 0; i < plaintext->length(); i++)
    {
        if(isupper((*plaintext)[i]))
            (*plaintext)[i] += 32;
    }
}

string playfair_encrypt(string duo, string grid)
{
    string cipherduo = "  ";
    int i,j,i1,i2,j1,j2,temp;
    i = grid.find(duo[0]);
    i1 = i/5;
    i2 = i%5;
    j = grid.find(duo[1]);
    j1 = j/5;
    j2 = j%5;

    cout << duo << ":\t" << "(" << i1 << "," << i2 << "), (" << j1 << "," << j2 << ")\n";

    if(i2 == j2)
    {
        i1 = (i1 + 1) % 5;
        j1 = (j1 + 1) % 5;
    }
    else if(i1 == j1)
    {
        i2 = (i2 + 1) % 5;
        j2 = (j2 + 1) % 5;
    }
    else
    {
        temp = i2;
        i2 = j2;
        j2 = temp;
    }

    cipherduo[0] = grid[i1 * 5 + i2];
    cipherduo[1] = grid[j1 * 5 + j2];
    cout << cipherduo << ":\t" << "(" << i1 << "," << i2 << "), (" << j1 << "," << j2 << ")\n- - - - - - - \n";
    return duo;
}

int playfair(string key, int decode)
{
    //sanity checks:
    //key is not longer than 25 unique characters
    //omit is not part of key
    
    ifstream infile;
    infile.open("process.txt");
    char omit, junk;
    omit = calc_omit(key);

    string keysquare = genkeysquare(key,omit);

    string temp,plaintext, cipher;
    while(infile)
    {
        if(infile.eof() == 1)
            break;
        infile >> temp;
        plaintext += temp;
    }
    lower(&plaintext);

    junk = calc_junk(plaintext);

    string bifurcated_text = "";
    for (int i = 0; i < plaintext.length(); i+=2)
    {
        temp = plaintext.substr(i,2);
        if(temp.length() == 1)
            temp += junk;
        else if(temp[0] == temp[1])
        {
            temp[1] = junk;
            temp += temp[0];
            temp += junk; //figure out how to do in a single line
        }
        bifurcated_text += temp;
    }
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << keysquare[i*5 + j] << " ";
        }
        cout << endl;
    }
    
    for (int i = 0; i < bifurcated_text.length(); i+=2)
    {
        temp = bifurcated_text.substr(i,2);
        temp = playfair_encrypt(temp,keysquare);
    }
    
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