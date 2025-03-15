#include "stm32f10x.h"                  // Device header
extern int8_t Serial_RxFlag;
uint8_t Serial_RxData;
extern uint8_t recvData[20];



uint8_t Compute_CRC8(uint8_t data1, uint8_t data2) {
    CRC_ResetDR();
    uint32_t input = ((uint32_t)data1 << 24) | ((uint32_t)data2 << 16);
    CRC_CalcCRC(input);
    return (uint8_t)(CRC_GetCRC() & 0xFF);
}


void Bluetooth_Serial_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART3, ENABLE);
}
void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART3, Byte);
	while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
	for (uint16_t i = 0; i < Length; i ++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y --)
	{
		Result *= X;
	}
	return Result;
}

void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}



uint8_t Serial_GetRxData(void)
{Serial_RxFlag=0;
	return Serial_RxData;
}

void USART3_IRQHandler(void)
{
    if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
    {
        Serial_RxData = USART_ReceiveData(USART3);
        switch (Serial_RxFlag)
        {
        case -1:
            // Waiting for the start byte (0xFF)
            if (Serial_RxData == 0xFF)
                Serial_RxFlag = 1;
            break;
        case 3:
            // Check the CRC of the received data
            if (Serial_RxData == Compute_CRC8(recvData[0], recvData[1]))
                Serial_RxFlag = 0; // CRC is correct, reset flag
            else
                Serial_RxFlag = -1; // CRC is incorrect, reset to waiting for start byte
            break;
        default:
            if (Serial_RxFlag > 0)
            {
                // Store received data in recvData array
                recvData[Serial_RxFlag - 1] = Serial_RxData;
                Serial_RxFlag++;
                
                // If Serial_RxFlag reaches 3, it means we have received two data bytes
                if (Serial_RxFlag > 3)
                {
                    Serial_RxFlag = -1; // Reset to waiting for start byte
                }
            }
            else
            {
                Serial_RxFlag = -1; // Invalid state, reset to waiting for start byte
            }
            break;
        }
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    }
}
