#ifndef M_DMA_H_
#define M_DMA_H_
#include "stm32f10x.h"                  // Device header
class DMA{
	public:DMA(uint32_t*,uint32_t*,const uint16_t&);
	void start_transfer();
	private: uint16_t arr_size;
};

#endif