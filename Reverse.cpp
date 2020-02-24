
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

string toReverse(string text)
{
    reverse(text.begin(), text.end());
    return text;
}

int main(int argc, char *argv[])
{
    cout << toReverse("TESTING") << endl;
    return 0;
}