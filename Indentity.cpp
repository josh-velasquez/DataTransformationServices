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
    string newString = "";
    locale loc;
    for (int i = 0; i < text.length(); ++i)
        newString += toupper(text[i], loc);
    return newString;
}

void startIdentityMicroService(string serverIp, int port)
{
    cout << "#########################################" << endl;
    cout << "\tIdentity Micro Service" << endl;
    cout << "#########################################" << endl;
    int clientSocket, bytesSent, bytesRecv;
    struct sockaddr_in server, client;
    char inBuffer[BUFFERSIZE], outBuffer[BUFFERSIZE];

    if ((clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        cout << "socket() failed" << endl;
    }
    memset((char *)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY); // Change later

    if (bind(clientSocket, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        cout << "bind() failed" << endl;
    }
    while (true)
    {
        cout << "Waiting for client requests..." << endl;
        bytesRecv = recvfrom(clientSocket, inBuffer, BUFFERSIZE, 0, (struct sockaddr *)&client, (socklen_t *)&server);
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
        bytesSent = sendto(clientSocket, outBuffer, BUFFERSIZE, 0, (struct sockaddr *)&client, sizeof(server));
        if (bytesSent < 0)
        {
            cout << "send() failed" << endl;
            exit(1);
        }
        cout << "Response sent to client." << endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <Server Ip> <Target Port>" << endl;
        exit(1);
    }
    startIdentityMicroService(argv[1], atoi(argv[2]));
    return 0;
}