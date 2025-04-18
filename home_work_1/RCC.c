#include "RCC.h"


void set_sysclk168(void){
	//�������� ������������ �� HSE
	SET_BIT(RCC->CR,RCC_CR_HSEON);
	while(READ_BIT(RCC->CR,RCC_CR_HSERDY));
	
	//��������� ����
	SET_BIT(FLASH->ACR,FLASH_ACR_PRFTEN);
	SET_BIT(FLASH->ACR,FLASH_ACR_LATENCY_6WS); //��� ������� 168 ���(max freq) ��� ���������� ������� >2.7v
	
	MODIFY_REG(RCC->PLLCFGR,RCC_PLLCFGR_PLLM,0x04<<RCC_PLLCFGR_PLLM_Pos); //� ��������� �������, ��� ������� ����� M ������ ���� � ������ 1-2���, ����� ��������� �� 8 ���, �������������, �������� M=4
	MODIFY_REG(RCC->PLLCFGR,RCC_PLLCFGR_PLLN,0xA8<<RCC_PLLCFGR_PLLN_Pos); //��������� N=168
	MODIFY_REG(RCC->PLLCFGR,RCC_PLLCFGR_PLLP,0x00<<RCC_PLLCFGR_PLLP_Pos); //�������� P=2
	MODIFY_REG(RCC->PLLCFGR,RCC_PLLCFGR_PLLQ,0x04<<RCC_PLLCFGR_PLLQ_Pos); //�������� Q=4 ������� ������ SDIO � ��� ��������� ���������(��.��������) �� ������ ��������� 48 ���, ��� ����� ��� ��������(168/4=42 ���)
	SET_BIT(RCC->PLLCFGR,RCC_PLLCFGR_PLLSRC_HSE); 												//������������ MAIN PLL �� HSE
	
	MODIFY_REG(RCC->CFGR,RCC_CFGR_HPRE, RCC_CFGR_HPRE_DIV1);							//AHBprescaler =1(������� ���� AHB ����� PLLCLK
	MODIFY_REG(RCC->CFGR,RCC_CFGR_PPRE1, RCC_CFGR_PPRE1_DIV4); 						//�������� APB1 =4 168/4=42 ���
	MODIFY_REG(RCC->CFGR,RCC_CFGR_PPRE2, RCC_CFGR_PPRE2_DIV2); 						//�������� APB2 =2 168/2=84 ���
	
	SET_BIT(RCC->CR,RCC_CR_PLLON); 																				//��������� pll
	while(READ_BIT(RCC->CR,RCC_CR_PLLRDY));
	MODIFY_REG(RCC->CFGR,RCC_CFGR_SW,0x02<<RCC_CFGR_SW_Pos);							//������������ �� PLLRCLK 168 MHz

}