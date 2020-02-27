# DataTransformationServices

Consists of six micro services that can alter user data sent from a client to the server.
The server and client communicates to each other via TCP connection for realiability while the server to the micro services connection communicates through UDP for fast response.
This was primarily tested on MACOS with zsh terminal and MX Linux with x-terminal.

# Running on Linux terminal

Navigate to startMicroServices.sh and comment out the osascript -e command and uncomment the  x-terminal-emulator -e (if you need to, otherwise don't change anything)
NOTE: You need to have x-terminal-emulator installed prior to running anything

# Running on MacOS terminal

Navigate to startMicroServices.sh and comment out the x-terminal-emulator -e and uncomment the osascript -e command (if you need to, otherwise don't change anything)

# Running the program

Open two terminals, one for server and one for client (The micro services will be automatically launched by the mainserver program)
./main <Target Port>
./client <Target Port>
If you don't provide a target port for both server and client, the default port will be set to 8080.
The port of the client and server must match.

# Manual Launch of Microservices

If you don't have x-terminal-emulator or on a macos, you can manually deploy the micro services by launching them one by one. To launch them one by one, first comment out the startMicroservices(port) line in the mainserver file on line 261. Once commented out, you can manually compile and launch the micro services into separate terminals.
NOTE: Ensure that the port assigned to each micro service is in ascending order.
i.e. if the main server and client are launched on port 4000, the identity micro service MUST be launched on port 4001, the reverse micro service MUST be launched on port 4002, the upper micro service MUST be launched on port 4003, the lower micro service MUST be launched on port 4004, the caesar micro service MUST be launched on port 4005, and the custom micro service MUST be launched on port 4006.
The order of the ports matter as they are assigned that way in the main server to prevent using the same ports as the main server.

# Microservices

There are six microservices available: 
    1. Identity 
        - Returns the client request as is 
    2. Reverse 
        - Reverses the client request 
    3. Upper 
        - Converts client request to all upper cases 
    4. Lower 
        - Converts client request to all lower cases 
    5. Caesar 
        - Encrypts user request using the Caesar cypher with an offset of 13 
    6. Custom 
        - Converts client request to l33t

You can chain the microservices when being prompt for which microservice to run
ex. 235
2 - will reverse the request first
3 - once reversed the request will be converted to all upper cases
5 - once reversed and converted to upper cases, it will be encrypted using the caesar cypher

# Script files
clearMicroServices.sh - deletes all the auto generated make files of the micro services
hostTerminal.sh - keeps the terminal from closing when auto launched from script
startMicroServices - compiles and starts all of the micro services in a new terminal