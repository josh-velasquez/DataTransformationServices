#include <stdlib.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <string.h>

using namespace std;

const int BUFFERSIZE = 2048;

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

/**
 * Prints user options
*/
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

/**
 * Sends client request to server
*/
void sendRequestToServer(int port, string message, string microservice)
{
    int serverSocket, bytesSent, bytesRecv;
    struct sockaddr_in serverAddress;
    char inBuffer[10 * BUFFERSIZE], outBuffer[10 * BUFFERSIZE];

    if ((serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        errorEncountered("socket()", "Failed", true);
    }
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    cout << "\nConnecting to server..." << endl;
    if (connect(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        errorEncountered("connect()", "Failed", true);
    }
    cout << "Connected to server." << endl;
    cout << "Sending request to server..." << endl;
    string request = message + '\n' + microservice;
    strcpy(outBuffer, (char *)request.c_str());
    bytesSent = send(serverSocket, outBuffer, BUFFERSIZE, 0);
    if (bytesSent < 0)
    {
        errorEncountered("send()", "Failed", true);
    }
    cout << "Request sent." << endl;
    cout << "Waiting for server response..." << endl;
    bytesRecv = recv(serverSocket, inBuffer, BUFFERSIZE, 0);
    if (bytesRecv < 0)
    {
        errorEncountered("recv()", "Failed", true);
    }
    cout << "Server response received." << endl;
    cout << "\nServer response: " << inBuffer << endl;
    close(serverSocket);
}

/**
 * Starts the client server and prompts the user for actions
*/
void startClientServer(int port)
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
            sendRequestToServer(port, userMessage, microService);
        }
        else if (userChoice == "3")
        {
            cout << "Exiting program...\n"
                 << endl;
            break;
        }
        else
        {
            cout << "\nInvalid input." << endl;
        }
    }
}

int main(int argc, char *argv[])
{
    switch (argc)
    {
    case 1:
        // Default is port 8080
        startClientServer(8080);
        break;
    case 2:
        startClientServer(atoi(argv[1]));
        break;
    default:
        cout << "Usage: " << argv[0] << "<Target Port>" << endl;
        exit(1);
    }
    return 0;
}