#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <ctype.h>
#include <iostream>
#include "RemoteSwitch.cpp"

using namespace std;

int main(int argc, char **argv) 
{
	int pin_out = 15; // Pin out using wiringPi pin numbering scheme (15 = TxD / BCM GPIO 14, see https://projects.drogon.net/raspberry-pi/wiringpi/pins/)
    int device = 0;
    bool state = false;
    
    
    if( argc != 4 ) { // not enough arguments
    	std::cout << "usage: " << argv[0] << " device state" << std::endl;
    	std::cout << "example: " << argv[0] << " 7 on" << std::endl;
	    return 0;
    } else {
	    device = atol(argv[1]);
	    string statestr = argv[2];
	    
	    if( statestr.compare("on") == 0 ) {
		    state = true;
	    } else {
		    state = false;
	    }
    }
    
    // load wiringPi
	if(wiringPiSetup() == -1)
	{
		printf("WiringPi setup failed. Maybe you haven't installed it yet?");
		exit(1);
	}

    // setup pin and make it low
	pinMode(pin_out, OUTPUT);
	digitalWrite(pin_out, LOW);
	BlokkerSwitch blokkerSwitch(pin_out);
	
	blokkerSwitch.sendSignal(device, state);
}


