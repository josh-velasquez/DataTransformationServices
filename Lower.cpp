#include <unistd.h>
#include <stdio.h>
#include <string>
#include <locale>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

const int BUFFERSIZE = 2048;

string toLower(string text)
{
    string newString = "";
    locale loc;
    for (int i = 0; i < text.length(); ++i)
        newString += tolower(text[i], loc);
    return newString;
}

void startLowerMicroService(string serverIp, int port)
{
    cout << "#########################################" << endl;
    cout << "\nLower Micro Service" << endl;
    cout << "#########################################" << endl;
    int serverSocket, bytesSent, bytesRecv;
    char inBuffer[BUFFERSIZE], outBuffer[BUFFERSIZE];
    struct sockaddr_in serverAddress;
    if ((serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        cout << "socket() failed" << endl;
        exit(1);
    }
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr(serverIp.c_str());

    cout << "Connecting to server..." << endl;
    if (connect(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        cout << "connect() failed" << endl;
        exit(1);
    }
    cout << "Connected to server." << endl;
    cout << "Receiving request from server..." << endl;
    bytesRecv = recv(serverSocket, inBuffer, BUFFERSIZE, 0);
    if (bytesRecv < 0)
    {
        cout << "recv() failed" << endl;
        exit(1);
    }
    cout << "Server request received." << endl;
    string response = toLower(inBuffer);
    strcpy(outBuffer, response.c_str());
    cout << "Sending response to server..." << endl;
    bytesSent = send(serverSocket, outBuffer, BUFFERSIZE, 0);
    if (bytesSent < 0)
    {
        cout << "send() failed" << endl;
        exit(1);
    }
    cout << "Response sent to server." << endl;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <Server Ip> <Target Port>" << endl;
        exit(1);
    }
    startLowerMicroService(argv[1], atoi(argv[2]));
    return 0;
}