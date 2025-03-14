 #ifndef _PWM_H
#define _PWM_H
#ifdef __cplusplus
extern "C" {
#endif
#include "stm32f10x.h"
void PWM_Init(void);
void Set_CCR(uint16_t);
#ifdef __cplusplus
}
#endif
#endif
