
#include "RTC.h"

unix_cal unix_time;
unix_cal set_rtc;

void init_RTC(void){
	
	SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);                               					 //Power interface clock enable	
	SET_BIT(RCC->BDCR,RCC_BDCR_BDRST);                                               	 //сброс Backup области
	CLEAR_BIT(RCC->BDCR,RCC_BDCR_BDRST);
	SET_BIT(RCC->BDCR,RCC_BDCR_RTCEN); 																								 //врубаем тактирование часов
	SET_BIT(PWR->CR,PWR_CR_DBP);                                                       //Disable backup domain write protection
	MODIFY_REG(RTC->WPR,RTC_WPR_KEY,0xCA<<RTC_WPR_KEY_Pos);
	MODIFY_REG(RTC->WPR,RTC_WPR_KEY,0x53<<RTC_WPR_KEY_Pos);
	
	//SET_BIT(RCC->BDCR,RCC_BDCR_LSCOSEL);//lse
	MODIFY_REG(RCC->BDCR,RCC_BDCR_RTCSEL,0x01<<RCC_BDCR_RTCSEL_Pos);
	SET_BIT(RCC->BDCR,RCC_BDCR_RTCEN);
	SET_BIT(RCC->BDCR,RCC_BDCR_LSEON);  
	while (!(RCC->BDCR & RCC_BDCR_LSERDY)){};
   	
	MODIFY_REG(RTC->WPR,RTC_WPR_KEY,0xCA<<RTC_WPR_KEY_Pos);
	MODIFY_REG(RTC->WPR,RTC_WPR_KEY,0x53<<RTC_WPR_KEY_Pos);
	CLEAR_BIT(PWR->CR,PWR_CR_DBP);																											//Enable backup domain write protection
}


uint8_t bcdToDec(uint8_t val){
  return( (val/16*10) + (val%16) );
}


uint8_t decToBcd(uint8_t val){
  uint8_t 	h_tetr=0, 
					  l_tetr=0, 
				  	value=0;
	h_tetr=val/10<<4;
	l_tetr=val%10;
	return value=h_tetr|l_tetr;
}

void timer_to_calendar ( unix_cal * unix_time){
	uint8_t sec,min,hour,date,month,year;
	uint32_t timer_time,timer_date;
	timer_time=RTC->TR;
	unix_time->sec=bcdToDec((uint8_t)timer_time);
	unix_time->min= bcdToDec((uint8_t)(timer_time>>8));
	unix_time->hour=bcdToDec((uint8_t)(timer_time>>16));
	timer_date=RTC->DR;
	unix_time->mday=bcdToDec((uint8_t)timer_date);
	month=(uint8_t)(timer_date>>8);
	month&=~0xE0;
	unix_time->month=bcdToDec(month);
	unix_time->year=bcdToDec((uint8_t)(timer_date>>16));
	
}

void set_time_and_date(uint8_t date, uint8_t month,uint8_t year,uint8_t hour, uint8_t min, uint8_t sec){
	SET_BIT(PWR->CR,PWR_CR_DBP);                                        //вырубаем защиту от записи backup области
	CLEAR_BIT(RCC->BDCR,RCC_BDCR_BDRST);
	if (!READ_BIT(RTC->ISR, RTC_ISR_INITF)){ 		
		SET_BIT(RTC->ISR,RTC_ISR_INIT);
		while(!(READ_BIT(RTC->ISR,RTC_ISR_INITF)));
		MODIFY_REG(RTC->PRER,RTC_PRER_PREDIV_A,127<<RTC_PRER_PREDIV_A_Pos);
		MODIFY_REG(RTC->PRER,RTC_PRER_PREDIV_S,255<<RTC_PRER_PREDIV_S_Pos);
		RTC->TR=decToBcd(sec)|(decToBcd(min)<<8)|(decToBcd(hour)<<16);
		month&=~0xE0;
		RTC->DR=decToBcd(date)|(decToBcd(month)<<8)|(decToBcd(year)<<16);
	}	
	CLEAR_BIT(RTC->ISR,RTC_ISR_INIT);
	CLEAR_BIT(PWR->CR,PWR_CR_DBP);
	SET_BIT(RCC->BDCR,RCC_BDCR_BDRST);	
}

void set_time(uint8_t hour, uint8_t min, uint8_t sec){
	SET_BIT(PWR->CR,PWR_CR_DBP);
	CLEAR_BIT(RCC->BDCR,RCC_BDCR_BDRST);
	if (!READ_BIT(RTC->ISR, RTC_ISR_INITF)){ 		
		SET_BIT(RTC->ISR,RTC_ISR_INIT);
		while(!(READ_BIT(RTC->ISR,RTC_ISR_INITF)));
		MODIFY_REG(RTC->PRER,RTC_PRER_PREDIV_A,127<<RTC_PRER_PREDIV_A_Pos);
		MODIFY_REG(RTC->PRER,RTC_PRER_PREDIV_S,255<<RTC_PRER_PREDIV_S_Pos);
		RTC->TR=decToBcd(sec)|(decToBcd(min)<<8)|(decToBcd(hour)<<16);
		
	}	
	CLEAR_BIT(RTC->ISR,RTC_ISR_INIT);
	CLEAR_BIT(PWR->CR,PWR_CR_DBP);
	SET_BIT(RCC->BDCR,RCC_BDCR_BDRST);	
}

void set_date(uint8_t date, uint8_t month,uint8_t year){
	SET_BIT(PWR->CR,PWR_CR_DBP);
	CLEAR_BIT(RCC->BDCR,RCC_BDCR_BDRST);
	if (!READ_BIT(RTC->ISR, RTC_ISR_INITF)){ 		
		SET_BIT(RTC->ISR,RTC_ISR_INIT);
		while(!(READ_BIT(RTC->ISR,RTC_ISR_INITF)));
		MODIFY_REG(RTC->PRER,RTC_PRER_PREDIV_A,127<<RTC_PRER_PREDIV_A_Pos);
		MODIFY_REG(RTC->PRER,RTC_PRER_PREDIV_S,255<<RTC_PRER_PREDIV_S_Pos);
		month&=~0xE0;
		RTC->DR=decToBcd(date)|(decToBcd(month)<<8)|(decToBcd(year)<<16);
	}	
	//CLEAR_BIT(RTC->ICSR,RTC_ICSR_INIT);
	CLEAR_BIT(PWR->CR,PWR_CR_DBP);
	SET_BIT(RCC->BDCR,RCC_BDCR_BDRST);	
}

