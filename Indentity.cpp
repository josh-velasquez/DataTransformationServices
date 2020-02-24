#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

string toIdentity(string text)
{
    return text;
}
int main(int argc, char *argv[])
{
    cout << toIdentity("TESTING") << endl;
    return 0;
}