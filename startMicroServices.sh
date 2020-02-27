#!/bin/sh

echo "Compiling micro services..."
echo "Compiling Identity micro service..."
g++ ./identity.c++ -o identity
echo "Compiling Reverse micro service..."
g++ ./reverse.c++ -o reverse
echo "Compiling Upper micro service..."
g++ ./upper.c++ -o upper
echo "Compiling Lower micro service..."
g++ ./lower.c++ -o lower
echo "Compiling Caesar micro service..."
g++ ./caesar.c++ -o caesar
echo "Compiling Custom micro service..."
g++ ./custom.c++ -o custom
echo "Finished compiling micro services.\n"

# zsh -c is for running on zsh terminal
# gnome-terminal -x sh -c is for linux
# $1 will have the server ip address
# $2 will have the port number

portNum=$1
echo "Starting Identity microservice..."
portNum=$((portNum+1))
x-terminal-emulator -e ./holdTerminal.sh ./identity $portNum
# zsh -c './identity '"$1 $portNum"

echo "Starting Reverse microservice..."
portNum=$((portNum+1))
x-terminal-emulator -e ./holdTerminal.sh ./reverse $portNum
# zsh -c './reverse '"$1 $portNum"

echo "Starting Upper microservice..."
portNum=$((portNum+1))
x-terminal-emulator -e ./holdTerminal.sh ./upper $portNum
# zsh -c './upper '"$1 $portNum"

echo "Starting Lower microservice..."
portNum=$((portNum+1))
x-terminal-emulator -e ./holdTerminal.sh ./lower $portNum
# zsh -c './lower '"$1 $portNum"

echo "Starting Caesar microservice..."
portNum=$((portNum+1))
x-terminal-emulator -e ./holdTerminal.sh ./caesar $portNum
# zsh -c './caesar '"$1 $portNum"

echo "Starting Custom microservice..."
portNum=$((portNum+1))
x-terminal-emulator -e ./holdTerminal.sh ./custom $portNum
# zsh -c './custom '"$1 $portNum"

echo "Successfully started microservices."
