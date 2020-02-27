/**
 * Joshua Velasquez
 * February 28, 2020
 * Main server that processes the clients requests and forwards them to micro services.
 * Once the micro services replies back with a response, the response is sent back to 
 * the server which is then forwarded to the client
*/
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
static void createSocket(string targetIpAddress, int port, Socket &targetSocket, int sock, int socketType)
{
    int socketVal;
    struct sockaddr_in address;

    // Set addresses to target ip and port
    address.sin_family = AF_INET;
    // address.sin_addr.s_addr = inet_addr(targetIpAddress.c_str());
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);

    // Create socket for server
    if ((socketVal = socket(AF_INET, sock, socketType)) < 0)
    {
        errorEncountered("socket()", "Failed", true);
    }
    targetSocket.socketVal = socketVal;
    targetSocket.address = address;
}

/**
 * Starts the microservices servers by invoking a shell script
*/
static void startMicroServices(string targetIp, int port)
{
    string command = "./StartMicroServices.sh " + targetIp + " " + to_string(port);
    system(command.c_str());
}

/**
 * Establishes a connection with the micro services
*/
string connectToMicroService(string microservice, string targetIp, int port, string message)
{
    int bytesSent, bytesRecv;
    char inBuffer[BUFFERSIZE], outBuffer[BUFFERSIZE];
    Socket microserviceSocket = Socket();
    createSocket(targetIp, port, microserviceSocket, SOCK_DGRAM, IPPROTO_UDP);
    cout << "Sending request to " << microservice << " microservice..." << endl;
    strcpy(outBuffer, message.c_str());
    bytesSent = sendto(microserviceSocket.socketVal, outBuffer, BUFFERSIZE, 0, (struct sockaddr *)&microserviceSocket.address, sizeof(microserviceSocket.address));
    if (bytesSent < 0)
    {
        errorEncountered("sendto()", "Failed", true);
    }
    cout << "Request sent to " << microservice << " microservice." << endl;
    cout << "Waiting for " << microservice << " microservice response..." << endl;
    bytesRecv = recvfrom(microserviceSocket.socketVal, inBuffer, BUFFERSIZE, 0, (struct sockaddr *)&microserviceSocket.address, (socklen_t *)&microserviceSocket.address);
    if (bytesRecv < 0)
    {
        errorEncountered("recvfrom()", "Failed", true);
    }
    cout << "Response from " << microservice << " microservice received." << endl;
    return inBuffer;
}

/**
 * Runs the identity micro service
*/
string runIdentityMicroService(string targetIp, int port, string message)
{
    return connectToMicroService("identity", targetIp, port, message);
}

/**
 * Runs the reverse micro service
*/
string runReverseMicroService(string targetIp, int port, string message)
{
    return connectToMicroService("reverse", targetIp, port, message);
}

/**
 * Runs the upper micro service
*/
string runUpperMicroService(string targetIp, int port, string message)
{
    return connectToMicroService("upper", targetIp, port, message);
}

/**
 * Runs the lower micro service
*/
string runLowerMicroService(string targetIp, int port, string message)
{
    return connectToMicroService("lower", targetIp, port, message);
}

/**
 * Runs the caesar micro service
*/
string runCaesarMicroService(string targetIp, int port, string message)
{
    return connectToMicroService("caesar", targetIp, port, message);
}

/**
 * Runs the custom micro service
*/
string runCustomMicroService(string targetIp, int port, string message)
{
    return connectToMicroService("custom", targetIp, port, message);
}

/**
 * Forwards the micro service response from the server to the client
*/
void sendMicroServiceResponseToClient(int clientSocket, string message)
{
    int bytesSent;
    char outBuffer[BUFFERSIZE];
    strcpy(outBuffer, message.c_str());
    cout << "Forwarding microservice response to client..." << endl;
    bytesSent = send(clientSocket, outBuffer, BUFFERSIZE, 0);
    if (bytesSent < 0)
    {
        errorEncountered("send()", "Failed", true);
    }
    cout << "Forwarded microservice response to client..." << endl;
}

/**
 * Invokes the micro services script and parses our the user input
 * 
 * NOTE: The ports are incremented respestively so they can run on their own ports 
 * (this value should correspond to the port values assigned in the bash script that 
 * auto launches the microservices)
 * Ex. if the server is running on port 3000, the identity microservice would run at
 * port at port 30001
*/
void processClientRequest(string targetIp, int port, int clientSocket, string userInput)
{
    // The user input will consist of "message\nmicroservices" so we need to split by \n
    int pos = userInput.find("\n");
    string newUserMessage = userInput.substr(0, pos);
    string microservices = userInput.substr(pos + 1, userInput.length());
    char microservice;
    cout << "Starting microservices..." << endl;
    // startMicroServices(targetIp, port);
    cout << "Microservices on standby." << endl;
    for (int i = 0; i < microservices.length(); i++)
    {
        microservice = microservices[i];
        if (microservice == '1')
        {
            newUserMessage = runIdentityMicroService(targetIp, port + 1, newUserMessage);
        }
        else if (microservice == '2')
        {
            newUserMessage = runReverseMicroService(targetIp, port + 2, newUserMessage);
        }
        else if (microservice == '3')
        {
            newUserMessage = runUpperMicroService(targetIp, port + 3, newUserMessage);
        }
        else if (microservice == '4')
        {
            newUserMessage = runLowerMicroService(targetIp, port + 4, newUserMessage);
        }
        else if (microservice == '5')
        {
            newUserMessage = runCaesarMicroService(targetIp, port + 5, newUserMessage);
        }
        else if (microservice == '6')
        {
            newUserMessage = runCustomMicroService(targetIp, port + 6, newUserMessage);
        }
    }
    sendMicroServiceResponseToClient(clientSocket, newUserMessage);
}

/**
 * Waits for connected client's request
*/
void processClient(string targetIp, int port, int clientSocket)
{
    char inBuffer[BUFFERSIZE], outBuffer[BUFFERSIZE], savedMessage[BUFFERSIZE];
    int bytesRecv, bytesSent;
    cout << "Waiting for client request..." << endl;
    bytesRecv = recv(clientSocket, (char *)&inBuffer, BUFFERSIZE, 0);
    if (bytesRecv < 0)
    {
        errorEncountered("recv()", "Failed", true);
    }
    cout << "Client request received." << endl;
    processClientRequest(targetIp, port, clientSocket, inBuffer);
}

/**
 * Creates the socket for the server and prepares it for listening
*/
void startDataTransformationServer(string targetIpAddress, int port)
{
    int dataSocket;
    cout << "\n########################################################################\n"
         << endl;
    cout << "Creating server socket..." << endl;
    Socket proxy = Socket();
    // Create a TCP connection with client
    createSocket(targetIpAddress, port, proxy, SOCK_STREAM, IPPROTO_TCP);
    cout << "Binding sockets.." << endl;
    if (bind(proxy.socketVal, (struct sockaddr *)&proxy.address, sizeof(struct sockaddr_in)) < 0)
    {
        errorEncountered("bind()", "Failed", true);
    }
    if (listen(proxy.socketVal, 20) < 0)
    {
        errorEncountered("listen()", "Failed", true);
    }
    while (true)
    {
        struct sockaddr_in clientAddress;
        int client = sizeof(struct sockaddr);
        cout << "\n########################################################################\n"
             << endl;
        cout << "Server listening for client connections..." << endl;
        dataSocket = accept(proxy.socketVal, (struct sockaddr *)&clientAddress, (socklen_t *)&client);
        if (dataSocket < 0)
        {
            errorEncountered("accept()", "Failed", true);
        }
        cout << "Client connected: " << inet_ntoa(clientAddress.sin_addr) << endl;
        cout << "Processing client..." << endl;
        processClient(targetIpAddress, port, dataSocket);
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