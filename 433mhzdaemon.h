#define MQ_NAME "/433mhzdaemon"
#define MQ_MESSAGE_MAX_LENGTH 10
#define MQ_MAX_NUM_OF_MESSAGES 10
#define MQ_MODE (S_IRUSR | S_IWUSR | S_IWGRP | S_IWOTH)
#define MQ_MESSAGE_PRIORITY 0

// Pin out using wiringPi pin numbering scheme (15 = TxD / BCM GPIO 14, see https://projects.drogon.net/raspberry-pi/wiringpi/pins/)
#define PIN_OUT 15

enum deviceType{ action, oldkaku, newkaku };

enum deviceCommand { off, on, dim };

