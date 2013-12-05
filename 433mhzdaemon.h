#define MQ_NAME "/433mhzdaemon"
#define MQ_MESSAGE_MAX_LENGTH 10
#define MQ_MAX_NUM_OF_MESSAGES 10
#define MQ_MODE (S_IRUSR | S_IWUSR | S_IWGRP | S_IWOTH)
#define MQ_MESSAGE_PRIORITY 0

enum deviceType{ action, oldkaku, newkaku };

enum deviceCommand { off, on, dim };

