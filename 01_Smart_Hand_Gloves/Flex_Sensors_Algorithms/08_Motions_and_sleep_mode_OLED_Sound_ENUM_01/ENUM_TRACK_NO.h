#ifdef ENGLISH
      #ifdef FEMALE
              enum Track_Playback {
                DEFAULT_TRACK = 0,
                MEDICINE = 21,
                FOOD_RES = 22,
                WATER_RES = 24,
                FOOD_REQ = 25,
                ENERGY_DRINK = 26,
                WATER_REQ = 27,
                INIT_TRACK = 28,
              };
      #else 
              enum Track_Playback {
                DEFAULT_TRACK = 0,
                MEDICINE = 11,
                FOOD_RES = 12,
                WATER_RES = 14,
                FOOD_REQ = 15,
                ENERGY_DRINK = 16,
                WATER_REQ = 17,
                INIT_TRACK = 18,
              };
      #endif
#else
  #ifdef FEMALE
    enum Track_Playback {
                DEFAULT_TRACK = 0,
                MEDICINE = 41,
                FOOD_RES = 42,
                WATER_RES = 44,
                FOOD_REQ = 45,
                ENERGY_DRINK = 46,
                WATER_REQ = 47,
                INIT_TRACK = 48,
              };
  #else
    enum Track_Playback {
                DEFAULT_TRACK = 0,
                MEDICINE = 31,
                FOOD_RES = 32,
                WATER_RES = 34,
                FOOD_REQ = 35,
                ENERGY_DRINK = 36,
                WATER_REQ = 37,
                INIT_TRACK = 38,
              };
  #endif
#endif