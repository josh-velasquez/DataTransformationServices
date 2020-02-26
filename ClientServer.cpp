#include <stdlib.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>

using namespace std;

const int BUFFERSIZE = 2048;

string printUserOptions()
{
    string userChoice;
    cout
        << "\nWhat would you like to do?\n"
        << "\t1. Enter a message\n"
        << "\t2. Run microservice(s)\n"
        << "\t3. Exit program\n"
        << ">> ";
    getline(cin, userChoice, '\n');
    return userChoice;
}

void sendRequestToServer(string serverIp, int port, string message, string microservice)
{
    int serverSocket, bytesSent, bytesRecv;
    struct sockaddr_in serverAddress;
    char inBuffer[10 * BUFFERSIZE], outBuffer[10 * BUFFERSIZE];

    if ((serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
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
    cout << "Sending request to server..." << endl;
    string request = message + '\n' + microservice;
    strcpy(outBuffer, (char *)request.c_str());
    bytesSent = send(serverSocket, outBuffer, BUFFERSIZE, 0);
    if (bytesSent < 0)
    {
        cout << "send() failed" << endl;
        exit(1);
    }
    cout << "Request sent." << endl;
    cout << "Waiting for server response..." << endl;
    bytesRecv = recv(serverSocket, inBuffer, BUFFERSIZE, 0);
    if (bytesRecv < 0)
    {
        cout << "recv() failed" << endl;
        exit(1);
    }
    cout << "Server response received." << endl;
    cout << inBuffer << endl;
    close(serverSocket);
}

void startClientServer(string serverIp, int port)
{
    cout << "\n##############################################"
         << "\n#        Data Transformation Services        #"
         << "\n##############################################\n\n";
    string userMessage, microService;
    string userChoice;
    while (userChoice != "3")
    {
        userChoice = printUserOptions();
        if (userChoice == "1")
        {
            cout << "Enter your message: ";
            getline(cin, userMessage, '\n');
            cout << "Message saved." << endl;
        }
        else if (userChoice == "2")
        {
            cout << "Enter the microservice(s) you want to run your message on: ";
            getline(cin, microService, '\n');
            sendRequestToServer(serverIp, port, userMessage, microService);
        }
        else if (userChoice == "3")
        {
            cout << "Exiting program..." << endl;
            break;
        }
        else
        {
            cout << "\n\nInvalid input." << endl;
        }
    }
}

int main(int argc, char *argv[])
{
    startClientServer(argv[1], atoi(argv[2]));
    return 0;
}