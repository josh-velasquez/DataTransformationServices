
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <locale>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

using namespace std;

const int BUFFERSIZE = 2048;

struct Socket
{
    int socketVal;
    sockaddr_in address;
};

/**
 * Prints errors and exits program
*/
void errorEncountered(string type, string status, bool quit)
{
    cout << "Error encountered: " << type << endl;
    cout << "Status: " << status << endl;
    if (quit)
    {
        cout << "Exiting program..." << endl;
        exit(1);
    }
}

static void createUDPSocket(string targetIpAddress, int port, Socket &targetSocket)
{
    int socketVal;
    struct sockaddr_in address;
    struct sockaddr *server;

    // Set addresses to target ip and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(targetIpAddress.c_str());
    address.sin_port = htons(port);

    // Create socket for server
    if ((socketVal = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        errorEncountered("socket()", "Failed", true);
    }
    targetSocket.socketVal = socketVal;
    targetSocket.address = address;
}

static void processUserRequests(string userInput)
{
    char inBuffer[BUFFERSIZE];
}

static void startUpperService(int serverPort, string serverIp, string targetIpAddress, int port)
{
    struct sockaddr_in microService;
    struct sockaddr *server;
    int socketVal;

    if ((socketVal = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        errorEncountered("socket()", "Failed", true);
    }

    microService.sin_family = AF_INET;
    microService.sin_port = htons(serverPort);

    if (inet_pton(AF_INET, serverIp.c_str(), &microService.sin_addr) == 0)
    {
        errorEncountered("inet_pton()", "Failed", true);
    }
    char inBuffer[BUFFERSIZE];
    while (true)
    {
        bzero(inBuffer, BUFFERSIZE);
    }
}

string toUpper(string text)
{
    string newString = "";
    locale loc;
    for (int i = 0; i < text.length(); ++i)
        newString += toupper(text[i], loc);
    return newString;
}

int main(int argc, char *argv[])
{
    cout << toUpper("testing") << endl;
    return 0;
}