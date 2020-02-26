# DataTransformationServices
Consists of microservices that can alter user data sent from a client to the server

# Running the program
Open two terminals, one for server and one for client
./makefile <Target Ip> <Target Port>
The port of the client and server must match

# Running on Linux terminal
Navigate to StartMicroServices.sh and replace the zsh -c commands with gnome-terminal -e (if you need to, otherwise don't change anything)

# Running on MacOS terminal
Depending on your default mac terminal, if your terminal is running the zsh shell, replace the gnome-terminal -e with zsh -c instead (if you need to, otherwise don't change anything)


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
        - Converts client request to pig latin

You can chain the microservices when being prompt for which microservice to run
ex. 235
2 - will reverse the request first
3 - once reversed the request will be converted to all upper cases
5 - once reversed and converted to upper cases, it will be encrypted using the caesar cypher