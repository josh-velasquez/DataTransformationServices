
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <locale>

using namespace std;

string toUpper(string text)
{
    string newString = "";
    locale loc;
    for (int i = 0; i < text.length(); ++i)
        newString += toupper(text[i], loc);
    return newString;
}