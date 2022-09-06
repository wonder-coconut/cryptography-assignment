#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>

using namespace std;

char shift_char_right(char ch, int shift)
{//shifts a character to ascii left or right by specified value
    int lower,upper,ascii;
    if(isupper(ch))
        lower = 65;
    else
        lower = 97;
    
    upper = lower + 26;
    ascii = ch;
    if(ascii + shift - lower < 0)//cyclic shift
        ascii = (ascii + shift - lower) % 26 + upper; 
    else
        ascii = (ascii + shift - lower) % 26 + lower;
    ch = ascii;
    
    return ch;

}

int ceaser(int shift, int decode)
{//ceaser cipher implementation
    //sanity checks:
    //text is only alphabet
    ifstream infile;
    infile.open("process.txt");
    string temp1,temp2,cipher;

    cipher = "";

    while(getline(infile,temp1))//parse line
    {
        stringstream str(temp1);
        while(str)
        {
            if(str.eof() == 1)
                break;
            str >> temp2; //parse token, ' ' delimiter

            for (int i = 0; i < temp2.length(); i++)
                temp2[i] = shift_char_right(temp2[i], pow(-1,decode) * shift);//encrypt/decrypt

            cipher = cipher + temp2 + " ";
        }
        cipher = cipher + "\n";
    }
    cout << cipher << endl;
    return 1;
}

int vignere(string key, int decode)
{//vignere cipher implementation
    //sanity checks:
    //key and text contains only alphabets
    //key is only lowercase
    ifstream infile;
    infile.open("process.txt");
    string temp1,temp2,cipher;
    int keylower, keyupper, keyascii, shift, keyindex;
    keylower = keyupper = shift = keyascii = keyindex = 0;

    while(getline(infile,temp1))//parse line
    {
        stringstream str(temp1);
        while(str)
        {
            if(str.eof() == 1)
                break;
            str >> temp2;//parse token, ' ' delimiter
            
            for(int i = 0; i < temp2.length(); i++)
            {
                if(isupper(key[keyindex % key.length()]))
                    keylower = 65;
                else
                    keylower = 97;

                shift = key[keyindex % key.length()] - keylower; //shift based on key alphabet position

                temp2[i] = shift_char_right(temp2[i], pow(-1,decode) * shift);//encrypt/decrypt

                keyindex++;
            }
            cipher = cipher + temp2 + " ";
        }
        cipher = cipher + "\n";
    }
    cout << cipher << endl;
    return 1;
}

string genkeysquare(string key, char omit)
{//generate logical 5*5 key grid for playfair, stored as a continuous string variable
    int keyindex = 0;
    string keysquare = "";
    char keyfill = 'a';
    for (int i = 0; i < 25;)
    {
        if(keyindex < key.length())//until end of key
        {
            if(keysquare.find(key[keyindex]) > keysquare.length() && key[keyindex] != omit)//duplication
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

char calc_omit(string key, string plaintext)
{//calculate optimal character to omit in keysquare, default is  'j'
    char omit = 'j';

    if(key.find(omit) > key.length() && plaintext.find(omit) > plaintext.length())//character does not exist in both key and plaintext
        return omit;
    
    for (char ch = 'a'; ch < 'z'; ch++)
    {
        if(key.find(ch) > key.length() && plaintext.find(ch) > plaintext.length()) 
        {
            omit = ch;
            break;
        }
    }
    return omit;
}

char calc_junk(string plaintext)
{//get optimal junk character, default is 'x'
    char junk = 'x';

    if(plaintext.find(junk) > plaintext.length())//character does not exist in plaintext
        return junk;
    
    for (char ch = 'a'; ch < 'z'; ch++)
    {
        if(plaintext.find(ch) > plaintext.length())
        {
            junk = ch;
            break;
        }
    }
    
    return junk;
}

void lower(string *plaintext)
{//convert a string to lowercase
    for (int i = 0; i < plaintext->length(); i++)
    {
        if(isupper((*plaintext)[i]))
            (*plaintext)[i] += 32;
    }
}

string playfair_process(string duo, string grid, int decode)
{//encrypt/decrypt a duo of characters with the playfair cipher
    string process_duo = "  ";
    int i,j,i1,i2,j1,j2,temp,shift;
    i = grid.find(duo[0]);
    i1 = i/5;
    i2 = i%5;//x and y coordinates from single index
    j = grid.find(duo[1]);
    j1 = j/5;
    j2 = j%5;
    shift = pow(-1,decode) * 1;

    if(i2 == j2)//same column
    {
        i1 = (((i1 + shift) < 0)? (i1 + shift) % 5 + 5 : (i1 + shift) % 5);//cyclic shift
        j1 = (((j1 + shift) < 0)? (j1 + shift) % 5 + 5 : (j1 + shift) % 5);
    }
    else if(i1 == j1)//same row
    {
        i2 = (((i2 + shift) < 0)? (i2 + shift) % 5 + 5 : (i2 + shift) % 5);
        j2 = (((j2 + shift) < 0)? (j2 + shift) % 5 + 5 : (j2 + shift) % 5);
    }
    else//box generation
    {
        temp = i2;
        i2 = j2;
        j2 = temp;
    }

    process_duo[0] = grid[i1 * 5 + i2];
    process_duo[1] = grid[j1 * 5 + j2];

    return process_duo;
}

int playfair(string key, int decode)
{//implement playfair cipher
    //sanity checks:
    //key is not longer than 25 unique characters
    
    ifstream infile;
    infile.open("process.txt");
    char omit, junk;
    string keysquare;

    string temp,plaintext, cipher;

    while(infile)
    {
        if(infile.eof() == 1)
            break;
        infile >> temp;
        plaintext += temp; //get plaintext with no whitespaces
    }
    lower(&plaintext);


    omit = calc_omit(key,plaintext);
    junk = calc_junk(plaintext);
    keysquare = genkeysquare(key,omit);

    cout << "\nOmit: " << omit << "\nJunk: " << junk << "\nKeysquare:\n";

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << keysquare[i*5 + j] << ' ';
        }
        cout << endl;
    }
    cout << endl;

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
        bifurcated_text += temp;//logical division of plaintext into sets of two, getting rid of duplicates within the duo
    }
    
    for (int i = 0; i < bifurcated_text.length(); i+=2)
    {
        temp = bifurcated_text.substr(i,2);
        temp = playfair_process(temp,keysquare,decode);//encrypt/decrypt
        cipher += temp;
    }
    
    cout << cipher << endl;
    return 1;
}

int main()
{
    int ch,decode;
    cout << "NOTE: input file only accepts alphabets. ";
    cout << "Multi line texts with white spaces are maintained in ceaser and vignere ciphers.";
    cout << "\n\n\n1. Ceaser Cipher\n2. Vignere Cipher\n3. Playfair Cipher\nEnter your choice (1/2/3): ";
    cin >> ch;
    cout << "\nEncode or Decode? (0,1): ";
    cin >> decode;
    int shift;
    string key;

    switch (ch)
    {
        case 1:
            cout << "\nEnter shift value: ";
            cin >> shift;
            ceaser(shift, decode);
            break;
        
        case 2:
            cout << "\nEnter key: ";
            cin >> key;
            vignere(key, decode);
            break;
        
        case 3:
            cout << "\nEnter key: ";
            cin >> key;
            playfair(key, decode);
            break;
        
        default:
            cout << "Invalid input\n";
            break;
    }
}