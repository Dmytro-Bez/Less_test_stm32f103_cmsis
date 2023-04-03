#include "main.h"

int main(void)
{
	cmsis_swd_afio_setting();

	cmsis_rcc_system_clock_72MHz();			//Запускаємо контролер на чистоті 72МГц
	cmsis_sys_tick_timer_init();			//Налаштовуємо системний таймер
	cmsis_PC13_output_push_pull_init();		//PC13 на вихід

	void cmsis_setting_swd();
	while (1){
		set_pinc13_led();

		GPIOA->BSRR=GPIO_BSRR_BS15;
		GPIOA->BSRR=GPIO_BSRR_BS3;
		GPIOA->BSRR=GPIO_BSRR_BS4;
		delay_ms(300);
		GPIOA->BSRR=GPIO_BSRR_BR15;
		GPIOA->BSRR=GPIO_BSRR_BR3;
		GPIOA->BSRR=GPIO_BSRR_BR4;
		delay_ms(300);
	}
}

