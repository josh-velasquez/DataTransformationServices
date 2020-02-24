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
    address.sin_addr.s_addr = inet_addr(targetIpAddress.c_str());
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
}

string runReverseMicroService()
{
}

string runUpperMicroService()
{
}

string runLowerMicroService()
{
}

string runCaesarMicroService()
{
}

string runCustomMicroService()
{
}

char *printUserOptions()
{
    return "\n####################################\nData Transformation Services\nWhat would you like to do?\n\t1. Enter a message\n\t2. Run microservice(s)\n\t3. Exit program";
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

void processClientRequest(int socket)
{
    char inBuffer[BUFFERSIZE], savedMessage[BUFFERSIZE];
    int bytesRecv, bytesSent;
    char *str;

    while (strncmp(inBuffer, "3", 1) != 0)
    {
        memset(&inBuffer, 0, BUFFERSIZE);
        str = printUserOptions();
        bytesSent = send(socket, str, sizeof(str), 0);
        if (bytesSent < 0)
        {
            errorEncountered("send()", "Failed", true);
        }
        bytesRecv = recv(socket, (char *)inBuffer, BUFFERSIZE, 0);
        if (bytesRecv < 0)
        {
            errorEncountered("recv()", "Failed", true);
        }
        if (strncmp(inBuffer, "1", 1) != 0)
        {
            bcopy(inBuffer, savedMessage, bytesRecv);
        }
        else
        {
            str = processMicroServiceRequests(inBuffer, savedMessage);
            bytesSent = send(socket, str, sizeof(str), 0);
            if (bytesSent < 0)
            {
                errorEncountered("send()", "Failed", true);
            }
        }
    }
}

void startDataTransformationServer(string targetIpAddress, int port)
{
    int dataSocket;
    printf("\n########################################################################\n");
    printf("Creating proxy socket...");
    Socket proxy = Socket();
    // Create a TCP connection with client
    createSocket(targetIpAddress, port, proxy, IPPROTO_TCP);
    printf("Binding sockets..");
    if (bind(proxy.socketVal, (struct sockaddr *)&proxy.address, sizeof(struct sockaddr_in)) < 0)
    {
        errorEncountered("bind()", "Failed", true);
    }
    if (listen(proxy.socketVal, 20) < 0)
    {
        errorEncountered("listen()", "Failed", true);
    }
    printf("Proxy server listening for requests...");
    while (true)
    {
        struct sockaddr_in clientAddress;
        int client = sizeof(struct sockaddr);
        printf("\n########################################################################\n");
        printf("Waiting for requests...");
        dataSocket = accept(proxy.socketVal, (struct sockaddr *)&clientAddress, (socklen_t *)&client);
        if (dataSocket < 0)
        {
            errorEncountered("accept()", "Failed", true);
        }
        cout << "Request received: " << inet_ntoa(clientAddress.sin_addr) << endl;
        printf("Processing request...");
        processClientRequest(dataSocket);
        printf("Forwarded client request successfully.");
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
