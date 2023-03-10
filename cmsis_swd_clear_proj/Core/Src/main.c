#include "main.h"

void cmsis_setting_swd(void);
void cmsis_swd_afio_setting(void);

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

/*----Для використання не jtag(5 pin),а swd(2 pin),ми маємо переналаштувати порт-----*/
void cmsis_setting_swd(void){
	//PA15 на вихід
	SET_BIT(RCC->APB2ENR,RCC_APB2ENR_IOPAEN);
	MODIFY_REG(GPIOA->CRH,GPIO_CRH_CNF15,0b00<<GPIO_CRH_CNF15_Pos);
	MODIFY_REG(GPIOA->CRH,GPIO_CRH_MODE15,0b11<<GPIO_CRH_MODE15_Pos);
	GPIOA->BSRR=GPIO_BSRR_BR15;

	//PB3 на вихід
	SET_BIT(RCC->APB2ENR,RCC_APB2ENR_IOPBEN);
	MODIFY_REG(GPIOB->CRL,GPIO_CRL_CNF3,0b00<<GPIO_CRL_CNF3_Pos);
	MODIFY_REG(GPIOB->CRL,GPIO_CRL_MODE3,0b11<<GPIO_CRL_MODE3_Pos);
	GPIOA->BSRR=GPIO_BSRR_BR3;

	//PA4 на вихід
	SET_BIT(RCC->APB2ENR,RCC_APB2ENR_IOPBEN);
	MODIFY_REG(GPIOA->CRH,GPIO_CRL_CNF4,0b00<<GPIO_CRL_CNF4_Pos);
	MODIFY_REG(GPIOA->CRH,GPIO_CRL_MODE4,0b11<<GPIO_CRL_MODE4_Pos);
	GPIOA->BSRR=GPIO_BSRR_BR4;
}

/*----Примінення альтернативної функції для роботи swd-----*/
void cmsis_swd_afio_setting(void){
	SET_BIT(RCC->APB2ENR,RCC_APB2ENR_IOPAEN);
	SET_BIT(RCC->APB2ENR,RCC_APB2ENR_AFIOEN);				//Включення тактування
	AFIO->MAPR=0b010<<AFIO_MAPR_SWJ_CFG_Pos;				//SERIAL WIRE
	//Створюємо блокування ніжок РА13 РА14
	GPIOA->LCKR=GPIO_LCKR_LCKK | GPIO_LCKR_LCK13 | GPIO_LCKR_LCK14;
	GPIOA->LCKR=GPIO_LCKR_LCK13 | GPIO_LCKR_LCK14;
	GPIOA->LCKR;
}
