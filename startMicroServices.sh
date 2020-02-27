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

# osascript -e is for running on zsh terminal (macos) using apple script
# x-terminal-emulator -e is for linux
# $1 will have the working directory
# $2 will have the port number

portNum=$2
echo "Starting Identity microservice..."
portNum=$((portNum+1))
# x-terminal-emulator -e ./holdTerminal.sh ./identity $portNum
osascript -e 'tell app "Terminal" to do script "cd '$1' | '$1'/identity '$portNum'"'


echo "Starting Reverse microservice..."
portNum=$((portNum+1))
# x-terminal-emulator -e ./holdTerminal.sh ./reverse $portNum
osascript -e 'tell app "Terminal" to do script "cd '$1' | '$1'/reverse '$portNum'"'

echo "Starting Upper microservice..."
portNum=$((portNum+1))
# x-terminal-emulator -e ./holdTerminal.sh ./upper $portNum
osascript -e 'tell app "Terminal" to do script "cd '$1' | '$1'/upper '$portNum'"'

echo "Starting Lower microservice..."
portNum=$((portNum+1))
# x-terminal-emulator -e ./holdTerminal.sh ./lower $portNum
osascript -e 'tell app "Terminal" to do script "cd '$1' | '$1'/lower '$portNum'"'

echo "Starting Caesar microservice..."
portNum=$((portNum+1))
# x-terminal-emulator -e ./holdTerminal.sh ./caesar $portNum
osascript -e 'tell app "Terminal" to do script "cd '$1' | '$1'/caesar '$portNum'"'

echo "Starting Custom microservice..."
portNum=$((portNum+1))
# x-terminal-emulator -e ./holdTerminal.sh ./custom $portNum
osascript -e 'tell app "Terminal" to do script "cd '$1' | '$1'/custom '$portNum'"'

echo "Successfully started microservices."
