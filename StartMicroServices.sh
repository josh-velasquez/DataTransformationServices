#!/bin/sh
echo "Compiling micro services..."
echo "Compiling Identity micro service..."
g++ ./Indentity.cpp -o identity
echo "Compiling Reverse micro service..."
g++ ./Reverse.cpp -o reverse
echo "Compiling Upper micro service..."
g++ ./Upper.cpp -o upper
echo "Compiling Lower micro service..."
g++ ./Lower.cpp -o lower
echo "Compiling Caesar micro service..."
g++ ./Caesar.cpp -o caesar
echo "Compiling Custom micro service..."
g++ ./Custom.cpp -o custom
echo "Finished compiling micro services.\n"

# zsh -c is for running on zsh terminal
# gnome-terminal -e is for linux
# $1 will have the server ip address
# $2 will have the port number

# let portNumber = $2

echo "Starting microservices..."
echo "Starting Identity microservice..."
# gnome-terminal -e ./identity $1 ($2 + 1)
# portNumber = $portNumber + 1
# zsh -c './indentity' $1 portNumber
# zsh -c './indentity' "10.13.118.4" 7001

# echo "Starting Reverse microservice..."
# gnome-terminal -e ./reverse $1 ($2 + 2)
# portNumber = $portNumber + 1
# zsh -c './reverse' $1 $portNumber
# zsh -c './reverse' "10.13.118.4" 8002

# echo "Starting Upper microservice..."
# gnome-terminal -e ./upper $1 ($2 + 3)
# portNumber = $portNumber + 1
# zsh -c './upper' $1 portNumber
# zsh -c './upper' "10.13.118.4" 8003

# echo "Starting Lower microservice..."
# gnome-terminal -e ./lower $1 ($2 + 4)
# portNumber = $portNumber + 1
# zsh -c './lower' $1 portNumber
# zsh -c './lower' "10.13.118.4" 8004

# echo "Starting Caesar microservice..."
# gnome-terminal -e ./caesar $1 ($2 + 5)
# portNumber = $portNumber + 1
# zsh -c './caesar' $1 portNumber
# zsh -c './caesar' "10.13.118.4" 8005

# echo "Starting Custom microservice..."
# gnome-terminal -e ./custom $1 ($2 + 6)
# portNumber = $portNumber + 1
# zsh -c './custom' $1 portNumber
# zsh -c './custom' "10.13.118.4" 8006

# echo "Successfully started microservices."
