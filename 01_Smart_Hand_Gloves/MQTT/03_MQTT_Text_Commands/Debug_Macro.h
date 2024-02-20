#define DEBUG
#ifdef DEBUG
#define DEBUG_LN(x) Serial.println(x)
#else
#define DEBUG_LN(x) while(0){}
#endif