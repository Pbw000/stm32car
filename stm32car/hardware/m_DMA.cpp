#include "stm32f10x.h"                  // Device header
#include "m_DMA.h"

DMA::DMA(uint32_t* src,uint32_t* dist, const uint16_t& size) : arr_size(size) {
  		
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr =  (uint32_t)src;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)dist;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = arr_size;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel1, DISABLE);
}

void DMA::start_transfer() {
    DMA_Cmd(DMA1_Channel1, DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel1, arr_size);
    DMA_Cmd(DMA1_Channel1, ENABLE);
    while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
    
        DMA_ClearFlag(DMA1_FLAG_TC1);
    
}