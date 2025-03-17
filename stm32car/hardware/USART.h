 #ifndef _USART_H
#define _USART_H
#ifdef __cplusplus
extern "C" {
#endif
#include "stm32f10x.h"
void start_transfer();
void Bluetooth_Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
uint8_t Serial_GetRxData(void);
#ifdef __cplusplus
}
#endif
#endif
