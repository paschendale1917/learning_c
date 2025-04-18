#ifndef RTC_H
#define RTC_H

#include "stm32f4xx.h"


#define START_RTC 			SET_BIT(RCC->BDCR,RCC_BDCR_RTCEN)
#define STOP_RTC  			CLEAR_BIT(RCC->BDCR,RCC_BDCR_RTCEN)

typedef struct
	{
	uint8_t year;
	uint8_t month;
	uint8_t mday;
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
	uint8_t wday;
	} unix_cal;

extern unix_cal unix_time;
extern unix_cal set_rtc;

void init_RTC(void);
void set_time(uint8_t hour, uint8_t min, uint8_t sec);
void set_date(uint8_t date, uint8_t month,uint8_t year);
void set_time_and_date(uint8_t date, uint8_t month,uint8_t year,uint8_t hour, uint8_t min, uint8_t sec);
void set_week_day(uint8_t week_day);//нереализовано
void timer_to_calendar  (unix_cal * unix_time);
uint32_t cal_to_timer (unix_cal * unix_time);

void reset_time(uint16_t xpos,  uint16_t ypos, unix_cal * set_rtc, uint8_t space, uint16_t bcolor,  uint16_t fcolor, uint8_t *font);
void reset_date(uint16_t xpos,  uint16_t ypos, unix_cal * unix_time, uint8_t space, uint16_t bcolor,  uint16_t fcolor, uint8_t *font);

#endif