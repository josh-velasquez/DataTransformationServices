#include <unistd.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

string toPigLatin(string text)
{
    return "testing pig";
}

int main(int argc, char *argv[])
{
    cout << toPigLatin("TESTING") << endl;
    return 0;
}