#ifndef AD_H_
#define AD_H_
#include "stm32f10x.h"                  // Device header
class AD{public:
AD(const uint8_t&);
uint16_t GetADValue();
};
#endif