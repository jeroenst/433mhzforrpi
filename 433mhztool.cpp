#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <ctype.h>
#include <iostream>
#include <string.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>

#include "433mhzdaemon.h"

using namespace std;

int main(int argc, char **argv) 
{
	mqd_t mqd;
	int ret;
    
    char msg[MQ_MESSAGE_MAX_LENGTH];
    ssize_t msg_len;

    string programname = argv[0];

    if( argc < 4 ) 
    { // not enough arguments
        if (programname.find("kaku") != std::string::npos)
        {
        	std::cout << "usage: " << argv[0] << " address device state level" << std::endl;
        	std::cout << "example: " << argv[0] << " for oldkaku : A 2 on" << std::endl;
        	std::cout << "example: " << argv[0] << " for newkaku : 123 10 dim 5" << std::endl;
        }
        else if (programname.find("action") != std::string::npos)
        {
	        std::cout << "usage: " << argv[0] << " dipchannel socket state" << std::endl;
        	std::cout << "example: " << argv[0] << " 18 B on" << std::endl;
        }    
        else
        {
                printf ("Unknown programname '%s', use kaku or action\n",argv[0]);
                exit(2);
        }
                    
        exit(1);
    }
    else
    {
        if (programname.find("kaku") != std::string::npos)
        {
            if (atol(argv[1]))
            {
                // msg[0] = devicetype
                msg[0] = (char) newkaku;
                // msg[1] = address part 1
                msg[1] = (char) atol(argv[1]);
            }
            else
            {
                msg[0] = (char) oldkaku;
                msg[1] = (char) (argv[1])[0];
            }
	    // msg[2] = address part 2
       	    msg[2] = (char) atol(argv[2]);
        }
        else if (programname.find("action") != std::string::npos)
        {
            // msg[0] = devicetype
            msg[0] = (char) action;
            msg[1] = atol(argv[1]);
            msg[2] = *argv[2];
        }    
	else
	{
		printf ("Unknown programname '%s', use kaku or action\n",argv[0]);
		exit(2);
	}
        
        string statestr = argv[3];
        msg[4] = 0;

        if( statestr.compare("on") == 0 ) 
        {
            // msg[3] = state
            msg[3]  = (char) on;
        } 
        else if( statestr.compare("off") == 0 ) 
        {
            msg[3] = (char) off;
        }
        else if( statestr.compare("dim") == 0 ) 
        {
	    msg[3] = (char) dim;
	   // msg[4] = value	
	    msg[4] = (char) atol(argv[4]);
        }
        else 
        {
            printf ("Only on, off, or dim state are valid");
            exit(3);
        }

        	/* Open the message queue. Message queue is already created from a different process */
        	mqd = mq_open(MQ_NAME, O_WRONLY);
	        if( mqd != (mqd_t)-1 )
        	{
//                printf(" Message Queue Opened\n");

                	printf(" Sending message to 433mhzdaemon.... ");
	                ret = mq_send(mqd, msg, MQ_MESSAGE_MAX_LENGTH, MQ_MESSAGE_PRIORITY);
        	        if(ret)
                	        perror("Failed");
	                else
        	                printf("Done\n");
                
                	/* Close the message queue */
	                ret = mq_close(mqd);
        	        if(ret)
				perror(" Message queue close failed");
                	else
				printf(" Message Queue Closed\n");
        
        	}
	        else
        	{
	                perror(" Message queue open failed, is 433mhzdaemon running?");
			exit(4);
        	}
	}
	
	return 0;
}
