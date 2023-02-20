/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */


/*
 * Seven segment Pin A:PC7
 * Seven segment Pin B:PC6
 * Seven segment Pin C:PA9
 * Seven segment Pin D:PA10
 * Seven segment Pin E:PA8
 * Seven segment Pin F:PC9
 * Seven segment Pin G:PC8
 *
 * Vibration Motor Module PWM Pin: PA5
 *
 * Button Level UP	:PB0
 * Button Level DOWn:PB1
 *
 */

#include <stdint.h>
#include "stm32f407xx.h"
#include "gpio.h"
#include "timer.h"
#include "coreM4.h"
#include "sevenSegment.h"

int tmTickCount=0;
int8_t nmbr=0;

void SysTick_Handler(){
	++tmTickCount;
}

void EXTI0_IRQHandler(void){
	static int inTimeOld;
	clear_pending_reg(GPIO_PIN_NO_0);
	if(tmTickCount-inTimeOld>=3){
		gpio_toggleto_output_pin(GPIOD, GPIO_PIN_NO_15);////////////Button Press indicator
		inTimeOld=tmTickCount;
		if(nmbr<9){
			nmbr++;
			update_of_7segment(nmbr);
			TIMER2->CCR1 = nmbr*2222*3;
		}
	}
}

void EXTI1_IRQHandler(void){
	static int inTimeOld;
	clear_pending_reg(GPIO_PIN_NO_1);
	if(tmTickCount-inTimeOld>=3){
		gpio_toggleto_output_pin(GPIOD, GPIO_PIN_NO_15);////////////Button Press indicator
		inTimeOld=tmTickCount;
		if(nmbr>0){
			nmbr--;
			update_of_7segment(nmbr);
			TIMER2->CCR1 = nmbr*2222*3;
		}
	}
}


int main(){
	GPIO_Handle_t button_press_indicator ={GPIOD,{GPIO_PIN_NO_15,GPIO_MODE_OUT,GPIO_SPEED_MEDIUM,GPIO_OTYPE_PP,GPIO_NO_PUPD}};
	gpio_init(&button_press_indicator);

	GPIO_Handle_t gpioA_7segmentA ={GPIOC,{GPIO_PIN_NO_7,GPIO_MODE_OUT,GPIO_SPEED_MEDIUM,GPIO_OTYPE_PP,GPIO_NO_PUPD}};
	GPIO_Handle_t gpioA_7segmentB ={GPIOC,{GPIO_PIN_NO_6,GPIO_MODE_OUT,GPIO_SPEED_MEDIUM,GPIO_OTYPE_PP,GPIO_NO_PUPD}};
	GPIO_Handle_t gpioA_7segmentC ={GPIOA,{GPIO_PIN_NO_9,GPIO_MODE_OUT,GPIO_SPEED_MEDIUM,GPIO_OTYPE_PP,GPIO_NO_PUPD}};
	GPIO_Handle_t gpioA_7segmentD ={GPIOA,{GPIO_PIN_NO_10,GPIO_MODE_OUT,GPIO_SPEED_MEDIUM,GPIO_OTYPE_PP,GPIO_NO_PUPD}};
	GPIO_Handle_t gpioA_7segmentE ={GPIOA,{GPIO_PIN_NO_8,GPIO_MODE_OUT,GPIO_SPEED_MEDIUM,GPIO_OTYPE_PP,GPIO_NO_PUPD}};
	GPIO_Handle_t gpioA_7segmentF ={GPIOC,{GPIO_PIN_NO_9,GPIO_MODE_OUT,GPIO_SPEED_MEDIUM,GPIO_OTYPE_PP,GPIO_NO_PUPD}};
	GPIO_Handle_t gpioA_7segmentG ={GPIOC,{GPIO_PIN_NO_8,GPIO_MODE_OUT,GPIO_SPEED_MEDIUM,GPIO_OTYPE_PP,GPIO_NO_PUPD}};

	gpio_init(&gpioA_7segmentA);
	gpio_init(&gpioA_7segmentB);
	gpio_init(&gpioA_7segmentC);
	gpio_init(&gpioA_7segmentD);
	gpio_init(&gpioA_7segmentE);
	gpio_init(&gpioA_7segmentF);
	gpio_init(&gpioA_7segmentG);

	GPIO_Handle_t Gpio_pd_btn_up={GPIOB,{GPIO_PIN_NO_0,GPIO_MODE_RE_IT,0,0,GPIO_NO_PUPD}};
	GPIO_Handle_t Gpio_pd_btn_down={GPIOB,{GPIO_PIN_NO_1,GPIO_MODE_RE_IT,0,0,GPIO_NO_PUPD}};

	gpio_init(&Gpio_pd_btn_up);
	gpio_init(&Gpio_pd_btn_down);

	nvic_irqno_enable(IRQ_EXTI0);
	nvic_irqno_enable(IRQ_EXTI1);

	systick_config(SYSTEM_FREQ/10);


	RCC->CFGR |= 0<<10; // set APB1 = 16 MHz
	GPIO_Handle_t PA5 ={GPIOA,{GPIO_PIN_NO_5,GPIO_MODE_ALTERNATE,0,0,0,GPIO_AF1}};
	gpio_init(&PA5);
	pwm_init(TIMER_2, 16, 20000, 500);

	update_of_7segment(nmbr);

	while(1){

	}

}
