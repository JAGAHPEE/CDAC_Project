#include <sys/types.h>
#define test_count 5
#define Sense_MAX 3500
#define MAX_MAPPED 100
#define THRESHOLD 40 

// Pin 33 for Wake-Up
#define BUTTON_PIN_BITMASK 0x200000000 // 2^33 in hex

int MIN_1 = 0;
int MIN_2 = 0;
int MIN_3 = 0;

uint8_t flag_for_min_max = 0;

int value_1,value_2,value_3;
