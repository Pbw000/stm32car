#ifndef ENCODER_H_
#define ENCODER_H_
#include "stm32f10x.h"                  // Device header
#ifdef __cplusplus
extern "C" {
#endif
void EncoderInit(void);
int16_t get_encoder(void);
#ifdef __cplusplus
}
#endif

#endif
