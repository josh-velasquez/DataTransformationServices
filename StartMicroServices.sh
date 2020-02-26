#!/bin/sh

echo "Compiling micro services..."
echo "Compiling Identity micro service..."
g++ ./Identity.cpp -o identity
# echo "Compiling Reverse micro service..."
# g++ ./Reverse.cpp -o reverse
# echo "Compiling Upper micro service..."
# g++ ./Upper.cpp -o upper
# echo "Compiling Lower micro service..."
# g++ ./Lower.cpp -o lower
# echo "Compiling Caesar micro service..."
# g++ ./Caesar.cpp -o caesar
# echo "Compiling Custom micro service..."
# g++ ./Custom.cpp -o custom
# echo "Finished compiling micro services.\n"

# zsh -c is for running on zsh terminal
# gnome-terminal -x sh -c is for linux
# $1 will have the server ip address
# $2 will have the port number

portNum=$2
echo "Starting microservices..."
echo "Starting Identity microservice..."
portNum=$((portNum+1))
gnome-terminal -x sh -c './identity '"$1 $portNum"
# zsh -c './identity '"$1 $portNum"
# open -a Terminal -n './identity '"$1 $portNum"

# echo "Starting Reverse microservice..."
# portNum=$((portNum+1))
# gnome-terminal -x sh -c './reverse '"$1 $portNum"
# zsh -c './reverse '"$1 $portNum"

# echo "Starting Upper microservice..."
# portNum=$((portNum+1))
# gnome-terminal -x sh -c './upper '"$1 $portNum"
# zsh -c './upper '"$1 $portNum"

# echo "Starting Lower microservice..."
# portNum=$((portNum+1))
# gnome-terminal -x sh -c'./lower '"$1 $portNum"
# zsh -c './lower '"$1 $portNum"

# echo "Starting Caesar microservice..."
# portNum=$((portNum+1))
# gnome-terminal -x sh -c './caesar '"$1 $portNum"
# zsh -c './caesar '"$1 $portNum"

# echo "Starting Custom microservice..."
# portNum=$((portNum+1))
# gnome-terminal -x sh -c './custom '"$1 $portNum"
# zsh -c './custom '"$1 $portNum"

# echo "Successfully started microservices."
