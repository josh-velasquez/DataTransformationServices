#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

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
static void createSocket(string targetIpAddress, int port, Socket &targetSocket)
{
    int socketVal;
    struct sockaddr_in address;

    // Set addresses to target ip and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(targetIpAddress.c_str());
    address.sin_port = htons(port);

    // Create socket for server
    if ((socketVal = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        errorEncountered("socket()", "Failed", true);
    }
    targetSocket.socketVal = socketVal;
    targetSocket.address = address;
}

/**
 * Starts the microservices servers
*/
static void startMicroServices()
{
}

static void runMicroService()
{
}

static void modifyMessage()
{
}

static void printUserOptions()
{
    printf("\n####################################");
    printf("Data Transformation Services");
    printf("What would you like to do?");
    printf("\t1. Enter a message");
    printf("\t2. Run microservice(s)");
    printf("\t3. Exit program");
    int userChoice;
    printf(">> ");
    cin >> userChoice;
    switch (userChoice)
    {
    case 1:
        modifyMessage();
        break;
    case 2:
        runMicroService();
        break;
    default:
        exit(1);
    }
}

void startDataTransformationServer(string targetIpAddress, int port)
{
    int dataSocket;
    printf("\n########################################################################\n");
    printf("Creating proxy socket...");
    Socket proxy = Socket();
    createSocket(targetIpAddress, port, proxy);
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
        // processClientRequest(dataSocket);
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
        cout << "Usage: " << argv[0] << " <Proxy IP> <Target Port> | "
             << "<Target Port>" << endl;
        exit(1);
    }
    return 0;
}
