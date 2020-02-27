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

portNum=$2
echo "Starting microservices..."
echo "Starting Identity microservice..."
portNum=$((portNum+1))
xterm -hold -e './identity '"$1 $portNum"
# gnome-terminal -x sh -c './identity '"$1 $portNum"
# zsh -c './identity '"$1 $portNum"
# open -a Terminal -n './identity '"$1 $portNum"

echo "Starting Reverse microservice..."
portNum=$((portNum+1))
xterm -hold -e './reverse '"$1 $portNum"
# gnome-terminal -x sh -c './reverse '"$1 $portNum"
# zsh -c './reverse '"$1 $portNum"

echo "Starting Upper microservice..."
portNum=$((portNum+1))
xterm -hold -e './upper '"$1 $portNum"
# gnome-terminal -x sh -c './upper '"$1 $portNum"
# zsh -c './upper '"$1 $portNum"

echo "Starting Lower microservice..."
portNum=$((portNum+1))
xterm -hold -e './lower '"$1 $portNum"
# gnome-terminal -x sh -c'./lower '"$1 $portNum"
# zsh -c './lower '"$1 $portNum"

echo "Starting Caesar microservice..."
portNum=$((portNum+1))
xterm -hold -e './caesar '"$1 $portNum"
# gnome-terminal -x sh -c './caesar '"$1 $portNum"
# zsh -c './caesar '"$1 $portNum"

echo "Starting Custom microservice..."
portNum=$((portNum+1))
xterm -hold -e './custom '"$1 $portNum"
# gnome-terminal -x sh -c './custom '"$1 $portNum"
# zsh -c './custom '"$1 $portNum"

echo "Successfully started microservices."
