#include <stdlib.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>

using namespace std;

const int BUFFERSIZE = 2048;

void startClientServer(string serverIp, int port)
{
    int serverSocket, bytesRecv, bytesSent;
    struct sockaddr_in serverAddress;
    char inBuffer[BUFFERSIZE], outBuffer[BUFFERSIZE];

    if ((serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        cout << "socket() failed" << endl;
        exit(1);
    }
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr(serverIp.c_str());

    if (connect(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        cout << "connect() failed" << endl;
        exit(1);
    }

    while (strncmp(outBuffer, "3", 1) != 0)
    {
        memset(&inBuffer, 0, BUFFERSIZE);
        memset(&outBuffer, 0, BUFFERSIZE);
        bytesRecv = recv(serverSocket, (char *)&inBuffer, BUFFERSIZE, 0);
        if (bytesRecv <= 0)
        {
            cout << "error" << endl;
        }
        cout << inBuffer << endl;
        fgets(outBuffer, BUFFERSIZE, stdin);
        bytesSent = send(serverSocket, (char *)&outBuffer, BUFFERSIZE, 0);
        if (bytesSent < 0)
        {
            cout << "error" << endl;
        }
        memset(&inBuffer, 0, BUFFERSIZE);
        bytesRecv = recv(serverSocket, (char *)&inBuffer, BUFFERSIZE, 0);
        cout << inBuffer << endl;
        }
    close(serverSocket);
}

int main(int argc, char *argv[])
{
    startClientServer(argv[1], atoi(argv[2]));
    return 0;
}