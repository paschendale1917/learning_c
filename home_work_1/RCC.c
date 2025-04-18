#include "RCC.h"
void set_sysclk168(void){
	//включаем тактирование от HSE
	SET_BIT(RCC->CR,RCC_CR_HSEON);
	while(READ_BIT(RCC->CR,RCC_CR_HSERDY));
	
	//настройка флэш
	SET_BIT(FLASH->ACR,FLASH_ACR_PRFTEN);
	SET_BIT(FLASH->ACR,FLASH_ACR_LATENCY_6WS);						 //для частоты 168 МГц(max freq) при напряжении питания >2.7v
	
	MODIFY_REG(RCC->PLLCFGR,RCC_PLLCFGR_PLLM,0x04<<RCC_PLLCFGR_PLLM_Pos); 			//в референсе указано, что частота после M должна быть в районе 1-2МГц, здесь резонатор на 8 МГц, соответсвенно, делитель M=4
	MODIFY_REG(RCC->PLLCFGR,RCC_PLLCFGR_PLLN,0xA8<<RCC_PLLCFGR_PLLN_Pos); 			//множитель N=168
	MODIFY_REG(RCC->PLLCFGR,RCC_PLLCFGR_PLLP,0x00<<RCC_PLLCFGR_PLLP_Pos); 			//делитель P=2
	MODIFY_REG(RCC->PLLCFGR,RCC_PLLCFGR_PLLQ,0x04<<RCC_PLLCFGR_PLLQ_Pos); 			//делитель Q=4 частота работы SDIO и еще некоторой периферии(см.референс) не должна превышать 48 МГц, для этого сей делитель(168/4=42 МГц)
	SET_BIT(RCC->PLLCFGR,RCC_PLLCFGR_PLLSRC_HSE); 						//тактирование MAIN PLL от HSE
	
	MODIFY_REG(RCC->CFGR,RCC_CFGR_HPRE, RCC_CFGR_HPRE_DIV1);				//AHBprescaler =1(частота шины AHB равна PLLCLK
	MODIFY_REG(RCC->CFGR,RCC_CFGR_PPRE1, RCC_CFGR_PPRE1_DIV4); 				//делитель APB1 =4 168/4=42 МГц
	MODIFY_REG(RCC->CFGR,RCC_CFGR_PPRE2, RCC_CFGR_PPRE2_DIV2); 				//делитель APB2 =2 168/2=84 МГц
	
	SET_BIT(RCC->CR,RCC_CR_PLLON); 								//запускаем pll
	while(READ_BIT(RCC->CR,RCC_CR_PLLRDY));
	MODIFY_REG(RCC->CFGR,RCC_CFGR_SW,0x02<<RCC_CFGR_SW_Pos);				//тактирование от PLLRCLK 168 MHz
}
