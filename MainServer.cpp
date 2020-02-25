#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <arpa/inet.h>

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

/**
 * Creates a socket for the parameters
*/
static void createSocket(string targetIpAddress, int port, Socket &targetSocket, int socketType)
{
    int socketVal;
    struct sockaddr_in address;

    // Set addresses to target ip and port
    address.sin_family = AF_INET;
    // address.sin_addr.s_addr = inet_addr(targetIpAddress.c_str());
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);

    // Create socket for server
    if ((socketVal = socket(AF_INET, SOCK_STREAM, socketType)) < 0)
    {
        errorEncountered("socket()", "Failed", true);
    }
    targetSocket.socketVal = socketVal;
    targetSocket.address = address;
}

/**
 * Starts the microservices servers by invoking a shell script
*/
static void startMicroServices()
{
    system("./StartMicroServices.sh");
}

string runIdentityMicroService()
{
    return "";
}

string runReverseMicroService()
{
    return "";
}

string runUpperMicroService()
{
    return "";
}

string runLowerMicroService()
{
    return "";
}

string runCaesarMicroService()
{
    return "";
}

string runCustomMicroService()
{
    return "";
}

char *processMicroServiceRequests(char *userChoice, char *userMessage)
{
    string choice, message, newUserMessage, num;
    choice += userChoice;
    message += userMessage;
    for (int i = 0; i < strlen(userChoice); i++)
    {
        num = userChoice[i];
        if (num == "1")
        {
            newUserMessage = runIdentityMicroService();
        }
        else if (num == "2")
        {
            newUserMessage = runReverseMicroService();
        }
        else if (num == "3")
        {
            newUserMessage = runUpperMicroService();
        }
        else if (num == "4")
        {
            newUserMessage = runLowerMicroService();
        }
        else if (num == "5")
        {
            newUserMessage = runCaesarMicroService();
        }
        else if (num == "6")
        {
            newUserMessage = runCustomMicroService();
        }
    }
    char charMessage[newUserMessage.size() + 1];
    strcpy(charMessage, newUserMessage.c_str());
    return charMessage;
}

void sendMicroServiceResponseToClient(int clientSocket, string message)
{
    int bytesSent;
    char outBuffer[BUFFERSIZE];
    strcpy(outBuffer, message.c_str());
    cout << "Forwarding microservice response to client..." << endl;
    bytesSent = send(clientSocket, outBuffer, BUFFERSIZE, 0);
    if (bytesSent < 0)
    {
        cout << "send() failed" << endl;
    }
}

void processClientRequest(int clientSocket, string userInput)
{
    // Split user input by \n

    // First line is message
    // Second is microserver
    string microservices;
    char microservice;
    string newUserMessage;
    for (int i = 0; i < microservices.length; i++)
    {
        microservice = microservices[i];
        if (microservice == '1')
        {
            newUserMessage = runIdentityMicroService();
        }
        else if (microservice == '2')
        {
            newUserMessage = runReverseMicroService();
        }
        else if (microservice == '3')
        {
            newUserMessage = runUpperMicroService();
        }
        else if (microservice == '4')
        {
            newUserMessage = runLowerMicroService();
        }
        else if (microservice == '5')
        {
            newUserMessage = runCaesarMicroService();
        }
        else if (microservice == '6')
        {
            newUserMessage = runCustomMicroService();
        }
    }

    sendMicroServiceResponseToClient(clientSocket, newUserMessage);
}

void processClient(int clientSocket)
{
    char inBuffer[BUFFERSIZE], outBuffer[BUFFERSIZE], savedMessage[BUFFERSIZE];
    int bytesRecv, bytesSent;
    cout << "Waiting for client request..." << endl;
    bytesRecv = recv(clientSocket, (char *)&inBuffer, BUFFERSIZE, 0);
    if (bytesRecv < 0)
    {
        cout << "recv() failed" << endl;
    }
    cout << "Client request received." << endl;
    cout << inBuffer << endl;
    processClientRequest(clientSocket, inBuffer);
}

void startDataTransformationServer(string targetIpAddress, int port)
{
    int dataSocket;
    cout << "\n########################################################################\n"
         << endl;
    cout << "Creating server socket..." << endl;
    Socket proxy = Socket();
    // Create a TCP connection with client
    createSocket(targetIpAddress, port, proxy, IPPROTO_TCP);
    cout << "Binding sockets.." << endl;
    if (bind(proxy.socketVal, (struct sockaddr *)&proxy.address, sizeof(struct sockaddr_in)) < 0)
    {
        errorEncountered("bind()", "Failed", true);
    }
    if (listen(proxy.socketVal, 20) < 0)
    {
        errorEncountered("listen()", "Failed", true);
    }
    cout << "Server listening for client connections..." << endl;
    while (true)
    {
        struct sockaddr_in clientAddress;
        int client = sizeof(struct sockaddr);
        cout << "\n########################################################################\n"
             << endl;
        dataSocket = accept(proxy.socketVal, (struct sockaddr *)&clientAddress, (socklen_t *)&client);
        if (dataSocket < 0)
        {
            errorEncountered("accept()", "Failed", true);
        }
        cout << "Client connected: " << inet_ntoa(clientAddress.sin_addr) << endl;
        cout << "Processing client..." << endl;
        processClient(dataSocket);
        // cout << "Forwarded client request successfully." << endl;
        close(dataSocket);
    }
}

int main(int argc, char *argv[])
{
    switch (argc)
    {
    case 2:
        // If only the port is provided, the target proxy server defaults to localhost
        startDataTransformationServer("127.0.0.1", atoi(argv[1]));
        break;
    case 3:
        startDataTransformationServer(argv[1], atoi(argv[2]));
        break;
    default:
        cout << "Usage: " << argv[0] << " <Target IP> <Target Port> | "
             << "<Target Port>" << endl;
        exit(1);
    }
    return 0;
}
