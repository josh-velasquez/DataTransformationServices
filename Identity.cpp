
/**
 * Joshua Velasquez
 * February 28, 2020
 * This micro service returns the server request as is
*/
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

const int BUFFERSIZE = 2048;

string toIdentity(string text)
{
    return text;
}

void startIdentityMicroService(string serverIp, int port)
{
    int clientSocket, bytesSent, bytesRecv;
    struct sockaddr_in serverAddress, clientAddress;
    char inBuffer[BUFFERSIZE], outBuffer[BUFFERSIZE];
    socklen_t sockLen;
    cout << "#########################################" << endl;
    cout << "\tIdentity Micro Service" << endl;
    cout << "#########################################" << endl;

    if ((clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        cout << "socket() failed" << endl;
        exit(1);
    }
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // Change later
    serverAddress.sin_port = htons(port);

    if (bind(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        cout << "bind() failed" << endl;
    }

    sockLen = sizeof(clientAddress);
    while (true)
    {
        cout << "\n\nWaiting for client requests..." << endl;
        bytesRecv = recvfrom(clientSocket, inBuffer, BUFFERSIZE, 0, (struct sockaddr *)&clientAddress, &sockLen);
        if (bytesRecv < 0)
        {
            cout << "recv() failed" << endl;
            exit(1);
        }
        cout << "Client request received..." << endl;
        cout << "Modifying response..." << endl;
        string response = toIdentity(inBuffer);
        strcpy(outBuffer, response.c_str());
        cout << "Sending response to client..." << endl;
        bytesSent = sendto(clientSocket, outBuffer, BUFFERSIZE, 0, (struct sockaddr *)&clientAddress, sizeof(serverAddress));
        if (bytesSent < 0)
        {
            cout << "send() failed" << endl;
            exit(1);
        }
        cout << "Response sent to client." << endl;
        cout << "Response: " << outBuffer << endl;
    }
}

int main(int argc, char *argv[])
{
    cout << argv[0] << endl;
    cout << argv[1] << endl;
    cout << argv[2] << endl;
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <Server Ip> <Target Port>" << endl;
        exit(1);
    }
    startIdentityMicroService(argv[1], atoi(argv[2]));
    return 0;
}