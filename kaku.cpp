#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <ctype.h>
#include <iostream>
#include "RemoteSwitch.cpp"
#include "NewRemoteTransmitter.cpp"

using namespace std;

int main(int argc, char **argv) 
{
    int pin_out = 15; // Pin out using wiringPi pin numbering scheme (15 = TxD / BCM GPIO 14, see https://projects.drogon.net/raspberry-pi/wiringpi/pins/)
    int device = 0;
    char *address;
    bool state = false;
    int dim = -1;
    
    
    if( argc < 4 ) { // not enough arguments
    	std::cout << "usage: " << argv[0] << " address device state level" << std::endl;
    	std::cout << "example: " << argv[0] << " for oldkaku : A 2 on" << std::endl;
    	std::cout << "example: " << argv[0] << " for newkaku : 123 10 dim 5" << std::endl;
        exit(1);
    } else {
	    address = argv[1];
	    device = atol(argv[2]);
	    string statestr = argv[3];
	    
	    if( statestr.compare("on") == 0 ) 
	    {
		state = true;
	    } 
	    else if( statestr.compare("off") == 0 ) 
	    {
		state = false;
	    }
	    else if( statestr.compare("dim") == 0 ) 
	    {
		dim = atol(argv[4]);
	    }
	    else 
	    {
	        printf ("Only on, off, or dim state are valid");
	        exit(1);
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
	
	if (atol(address) > 0)
	{
            NewRemoteTransmitter transmitter(atol(address), pin_out, 260, 4);
	    if (device == 0)
	    {
                transmitter.sendGroup(state);
            }
            else
            {
                if (dim < 0)
                {
                    transmitter.sendUnit(device, state);
                }
                else
                {
                    transmitter.sendDim(device, dim);
                }
            }
        }
        else
        {	    
	    KaKuSwitch kaKuSwitch(pin_out);
	    kaKuSwitch.sendSignal(address[0], device, state);
        }
    exit(0);
}
