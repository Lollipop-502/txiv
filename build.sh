gcc txiv.c -o txiv --std=c99 -lX11 -lm
if [ "$1" == "install" ]; then
    echo "Installing txiv to /usr/local/bin with sudo access"
	sudo rm /usr/local/bin/txiv
	sudo cp txiv /usr/local/bin
fi
