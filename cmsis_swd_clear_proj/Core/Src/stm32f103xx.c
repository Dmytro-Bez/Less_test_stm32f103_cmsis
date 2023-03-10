#include "main.h"
/*-----Змінні використання-----*/
volatile uint8_t counter=0;
volatile uint32_t sysTick_ms=0;															//Tick for the HAL_GetTick()
volatile uint32_t Delay_counter_ms=0;													//Tick for the HAL_Delay()

/*-----Налаштування роботи тактування мікроконтролера-----*/
void cmsis_rcc_system_clock_72MHz(void){
	//Налаштування роботи мікроконтролера на 72MHz
	SET_BIT(RCC->CR,RCC_CR_HSEON);														//Запуск внутрішнього RC генератора
	while(READ_BIT(RCC->CR,RCC_CR_HSIRDY) == 0);										//Чекаємо підняття прапора готовності
	SET_BIT(RCC->CR,RCC_CR_HSEON);														//Підключення зовнішнього резонатора
	while(READ_BIT(RCC->CR,RCC_CR_HSERDY) == 0);										//Чекаємо підняття прапора готовності
	CLEAR_BIT(RCC->CR,RCC_CR_HSEBYP);													//Скидання біта байпаса
	SET_BIT(RCC->CR,RCC_CR_CSSON);														//Запуск clock detect
//	  SET_BIT(RCC->CR,RCC_CR_PLLON);											//Запуск PLL
//	  while(READ_BIT(RCC->CR,RCC_CR_PLLRDY) == 0);								//Чекаємо готовність вмикання PLL
	//Налаштування дільників для роботи таймера
	MODIFY_REG(RCC->CFGR,RCC_CFGR_SW,RCC_CFGR_SW_PLL);									//Вибір PLL як sys. clock
	MODIFY_REG(RCC->CFGR,RCC_CFGR_SWS,RCC_CFGR_SWS_PLL);								//Використання PLL як sys. clock
	MODIFY_REG(RCC->CFGR,RCC_CFGR_HPRE,RCC_CFGR_HPRE_DIV1);								//APB prescaler 1
	//Налаштування флеш пам'яті для роботи тактової частоти на 72MHz
	MODIFY_REG(FLASH->ACR,FLASH_ACR_LATENCY,FLASH_ACR_LATENCY_2);						//010 two wait state,if 48MHz
	SET_BIT(FLASH->ACR,FLASH_ACR_PRFTBE);												//Prefetch is enable :1
	SET_BIT(FLASH->ACR,FLASH_ACR_PRFTBS);												//Prefetch buffer is enable :1
	MODIFY_REG(RCC->CFGR,RCC_CFGR_PPRE1,RCC_CFGR_PPRE1_DIV2);							//APB1 prescaler /2
	MODIFY_REG(RCC->CFGR,RCC_CFGR_PPRE2,RCC_CFGR_PPRE2_DIV1);							//APB2 prescaler /1
	//Налаштуємо АЦП
	MODIFY_REG(RCC->CFGR,RCC_CFGR_ADCPRE,RCC_CFGR_ADCPRE_DIV6);							// 72/6=12MHz
	SET_BIT(RCC->CFGR,RCC_CFGR_PLLSRC);													//HSE for the PLL
	CLEAR_BIT(RCC->CFGR,RCC_CFGR_PLLXTPRE);												//Не потребуємо преддільника
	MODIFY_REG(RCC->CFGR,RCC_CFGR_PLLMULL,RCC_CFGR_PLLMULL9);							//Домножування для значення 72
	//Налаштування шину USB
	CLEAR_BIT(RCC->CFGR,RCC_CFGR_USBPRE);												//Налаштуваннч роботи usb на 48MHz
	MODIFY_REG(RCC->CFGR,RCC_CFGR_MCO,RCC_CFGR_MCO_PLLCLK_DIV2);						//
	SET_BIT(RCC->CR,RCC_CR_PLLON);														//Запуск PLL
	while(READ_BIT(RCC->CR,RCC_CR_PLLRDY) == 0);										//Чекаємо готовність вмикання PLL
}

/*-----Налаштування порту для роботи з індикацією-----*/
void set_pinc13_led(void){
//	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);		//HAL - setting pinc13_led
//	  HAL_Delay(1500);
//	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, SET);
//	  HAL_Delay(1000);
	GPIOC->BSRR=GPIO_BSRR_BS13;															//CMSIS - setting pinc13_led
//	  HAL_Delay(1500);
	delay_ms(500);
	GPIOC->BSRR=GPIO_BSRR_BR13;
//	  HAL_Delay(300);
	delay_ms(500);
}

/*-----Налаштування PC13 порту для роботи на вихід-----*/
void cmsis_PC13_output_push_pull_init(void){
	//Включення тактування порту С
	SET_BIT(RCC->APB2ENR,RCC_APB2ENR_IOPCEN);											//Запуск тактування потру С
	MODIFY_REG(GPIOC->CRH,GPIO_CRH_CNF13_Msk,0b00<<GPIO_CRH_CNF13_Pos);					//PC13 output push-pull
	MODIFY_REG(GPIOC->CRH,GPIO_CRH_MODE13_Msk,0b11<<GPIO_CRH_MODE13_Pos);				//Встановлення швидкості PC13 на 50MHz
}

/*-----Налаштування затримки системи-----*/
void cmsis_sys_tick_timer_init(void){
	//Налаштування ситемного таймера
	CLEAR_BIT(SysTick->CTRL,SysTick_CTRL_ENABLE_Msk);									//Вимикаємо 0 bit
	SET_BIT(SysTick->CTRL,SysTick_CTRL_TICKINT_Msk);									//Дозвіл на переривання
	SET_BIT(SysTick->CTRL,SysTick_CTRL_CLKSOURCE_Msk);									//Вибираємо без дільника,буде 72MHz
	MODIFY_REG(SysTick->LOAD,SysTick_LOAD_RELOAD_Msk,71999<<SysTick_LOAD_RELOAD_Pos);	//Налаштування на 1KHz
	MODIFY_REG(SysTick->LOAD,SysTick_VAL_CURRENT_Msk,71999<<SysTick_VAL_CURRENT_Pos);	//Початок читання
	SET_BIT(SysTick->CTRL,SysTick_CTRL_ENABLE_Msk);										//Запуск таймер
}

/*-----Звороній зв'язок для таймера з векторм переривань-----*/
void SysTick_Handler(void){
	sysTick_ms++;
	if(Delay_counter_ms){
		Delay_counter_ms--;
	}
}

/*-----Функція затримки(Delay_ms)-----*/
void delay_ms(uint32_t milliseconds){
	Delay_counter_ms=milliseconds;
	while(Delay_counter_ms != 0);
}
