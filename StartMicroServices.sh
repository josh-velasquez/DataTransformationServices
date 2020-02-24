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

echo "Starting microservices..."
echo "Starting Identity microservice..."
# gnome-terminal -e ./identity
zsh -c './indentity'

echo "Starting Reverse microservice..."
# gnome-terminal -e ./reverse
zsh -c './reverse'

echo "Starting Upper microservice..."
# gnome-terminal -e ./upper
zsh -c './upper'

echo "Starting Lower microservice..."
# gnome-terminal -e ./lower
zsh -c './lower'

echo "Starting Caesar microservice..."
# gnome-terminal -e ./caesar
zsh -c './caesar'

echo "Starting Custom microservice..."
# gnome-terminal -e ./custom
zsh -c './custom'

echo "Successfully started microservices."
