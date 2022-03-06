/****************************************************/
// MSP432P401R
// 8-1 定时器中断
// Bilibili：m-RNA
// E-mail:m-RNA@qq.com
// 创建日期:2021/9/1
/****************************************************/

#include "sysinit.h"
#include "usart.h"
#include "timA.h"
#include "usart.h"
#include "led.h"
#include "delay.h"
#include "adc.h"

#define CLKDIV 64   //时钟源分频
#define CCR0 60000  // 比较值0

/*
 * 定时器中断周期：
 *
 * T_timer_a = CLKDIV * (CCR0 + 1) / f_clk 
 *           = 64 * 37500 / 48000000 
 *           = 0.05s = 20Hz
 */

// Tim32
#define CLKDIV32 TIMER32_PRESCALER_1 // 时钟源分频
#define ARR 0xffffff               // 自动重装载值
// ARR 理论可以到32位 即 0xFFFF FFFF




int main(void)
{
	
		
    SysInit();  			     		// 第3讲 时钟配置
		delay_init();
		LED_Init();					 			// 第2讲 GPIO输出
		uart_init(115200);
		//TimA0_Int_Init(60000,64); // TIMA0中断
		//TimA1_Int_Init(60000,64);   // TIMA1中断
		TimA2_Int_Init();
    //Tim32_0_Int_Init(ARR, CLKDIV32); // TIM32中断
		NVIC_Configuration();				// 中断优先级表
		ADC_Config();
		
    MAP_Interrupt_enableMaster(); // 开启总中断
		

		printf("Hello MSP432!\r\n");

    while (1)
    {		
    }
		
		
		
}


