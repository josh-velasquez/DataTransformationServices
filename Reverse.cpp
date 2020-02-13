
#include <unistd.h>
#include <stdio.h>
#include <string>

using namespace std;

string toReverse(string text)
{
    reverse(text.begin(), text.end());
    return text;
}