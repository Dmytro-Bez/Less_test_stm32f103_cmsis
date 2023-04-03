#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx.h"

void cmsis_rcc_system_clock_72MHz(void);		//Налаштування роботи тактування мікроконтролера
void set_pinc13_led(void);						//Налаштування порту для роботи з індикацією
void cmsis_PC13_output_push_pull_init(void);	//Налаштування PC13 порту для роботи на вихід
void cmsis_sys_tick_timer_init(void);			//Налаштування затримки системи
void SysTick_Handler(void);						//Звороній зв'язок для таймера з векторм переривань
void delay_ms(uint32_t milliseconds);			//Функція затримки(Delay_ms)
void cmsis_setting_swd(void);
void cmsis_swd_afio_setting(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
