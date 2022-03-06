/****************************************************/
// MSP432P401R
// 定时器A
// Bilibili：m-RNA
// E-mail:m-RNA@qq.com
// 创建日期:2021/8/26
/****************************************************/

#include "timA.h"
#include "usart.h"

extern int switch_data;
extern int16_t data_array1[512];
extern int16_t data_array2[512];


void NVIC_Configuration(void){

	Interrupt_setPriorityGrouping(4);
	
	MAP_Interrupt_setPriority(FAULT_SYSTICK,0x00);
	MAP_Interrupt_setPriority(INT_DMA_INT1 ,0x20);
	MAP_Interrupt_setPriority(INT_T32_INT2,0x40);


	MAP_Interrupt_setPriority(INT_TA1_0 ,0x60);
	MAP_Interrupt_setPriority(INT_TA2_0 ,0x30);
	
}


/***************************************************TIMEA2******************************************************/


void TimA2_Int_Init(void)
{
		Timer_A_UpModeConfig upConfig =
		{
			TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source
			TIMER_A_CLOCKSOURCE_DIVIDER_48,         // SMCLK = 48MHz
			50000,                           				// 2500 tick period
			TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
			TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,    // Enable CCR0 interrupt
			TIMER_A_DO_CLEAR                        // Clear value
		}; // 50ms                  

	    // 2.初始化定时器A
    MAP_Timer_A_configureUpMode(TIMER_A2_BASE, &upConfig);

    // 3.选择模式开始计数
    MAP_Timer_A_startCounter(TIMER_A2_BASE, TIMER_A_UP_MODE);

    // 4.清除比较中断标志位
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);

    // 5.开启串口端口中断
    MAP_Interrupt_enableInterrupt(INT_TA2_0);
}

void TA2_0_IRQHandler(void)
{

	static uint16_t _cnt_1s=0,_cnt_2s=0;
	_cnt_1s++;
	_cnt_2s++;

	if(_cnt_1s>=10)
	{
		_cnt_1s=0;
		Task_1s_Thread();
	}
	
		if(_cnt_2s>=50)
	{
		_cnt_2s=0;
	  Task_2s_Thread();
	}

	MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_0);	

}

void Task_1s_Thread(void){
	int i;
	if(switch_data & 1)
	{
			float t = 0;
			for(i = 0; i < 10; i++)
			{
					t += (float)(data_array1[i]+0x8000)/0x10000;
			}
			printf("pingpong1:  %.3f \n", t * 3.3f/10.0f);
	}
	else
	{
			float t = 0;
			for(i = 0; i < 10; i++)
			{
					t += (float)(data_array2[i]+0x8000)/0x10000;
			}
			printf("pingpong2:  %.3f \n", t * 3.3f/10.0f);
	}

	MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN1);
	
}

void Task_2s_Thread(void){
		MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
}


/*********************************************************************************************************/








/**************************************         TIMA0          *******************************************/

void TimA0_Int_Init(uint16_t ccr0, uint16_t psc)
{
    // 1.增计数模式初始化
    Timer_A_UpModeConfig upConfig;
    upConfig.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;                                      //时钟源
    upConfig.clockSourceDivider = psc;                                                     //时钟分频 范围1-64
    upConfig.timerPeriod = ccr0;                                                           //自动重装载值（ARR）
    upConfig.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;                   //禁用 tim溢出中断
    upConfig.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE; //启用 ccr0更新中断
    upConfig.timerClear = TIMER_A_DO_CLEAR;                                                // Clear value

    // 2.初始化定时器A
    MAP_Timer_A_configureUpMode(TIMER_A0_BASE, &upConfig);

    // 3.选择模式开始计数
    MAP_Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);

    // 4.清除比较中断标志位
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);

    // 5.开启串口端口中断
    MAP_Interrupt_enableInterrupt(INT_TA0_0);
}


void TimA1_Int_Init(uint16_t ccr0, uint16_t psc)
{
    // 1.增计数模式初始化
    Timer_A_UpModeConfig upConfig;
    upConfig.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;                                      //时钟源
    upConfig.clockSourceDivider = psc;                                                     //时钟分频 范围1-64
    upConfig.timerPeriod = ccr0;                                                           //自动重装载值（ARR）
    upConfig.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;                   //禁用 tim溢出中断
    upConfig.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE; //启用 ccr0更新中断
    upConfig.timerClear = TIMER_A_DO_CLEAR;                                                // Clear value

    // 2.初始化定时器A
    MAP_Timer_A_configureUpMode(TIMER_A1_BASE, &upConfig);

    // 3.选择模式开始计数
    MAP_Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE);

    // 4.清除比较中断标志位
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_1);

    // 5.开启串口端口中断
    MAP_Interrupt_enableInterrupt(INT_TA1_0);
}



// 6.编写TIMA ISR
void TA0_0_IRQHandler(void)
{
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);

    /*开始填充用户代码*/

    MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);

    /*结束填充用户代码*/
}


// 6.编写TIMA ISR
void TA1_0_IRQHandler(void)
{
    MAP_Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);

    /*开始填充用户代码*/
		//MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN0);
    //MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN1);
		//MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN2);
		MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN2);
    /*结束填充用户代码*/
}


void Tim32_0_Int_Init(uint32_t aar, uint8_t psc)
{
    MAP_Timer32_initModule(TIMER32_0_BASE, psc, TIMER32_32BIT, TIMER32_PERIODIC_MODE);

    MAP_Timer32_setCount(TIMER32_0_BASE, aar);

    MAP_Timer32_enableInterrupt(TIMER32_0_BASE);

    MAP_Timer32_startTimer(TIMER32_0_BASE, false); //连续计数模式 false

    MAP_Interrupt_enableInterrupt(INT_T32_INT1);
}

/* Timer32 ISR */
void T32_INT1_IRQHandler(void)
{
    MAP_Timer32_clearInterruptFlag(TIMER32_0_BASE);


    /*开始填充用户代码*/
		// 中断回调函数中变量加static 下次调用这个变量就不会被清除了 因为static 的变量保存在全局变量中
    //static uint32_t timer_second = 0;
		MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN1);

    /*结束填充用户代码*/
}

void Tim32_1_Int_Init(uint32_t aar, uint8_t psc)
{
    MAP_Timer32_initModule(TIMER32_1_BASE, psc, TIMER32_32BIT, TIMER32_PERIODIC_MODE);

    MAP_Timer32_setCount(TIMER32_1_BASE, aar);

    MAP_Timer32_enableInterrupt(TIMER32_1_BASE);

    MAP_Timer32_startTimer(TIMER32_1_BASE, false); //连续计数模式 false

    MAP_Interrupt_enableInterrupt(INT_T32_INT2);
}

/* Timer32 ISR */
void T32_INT2_IRQHandler(void)
{
    MAP_Timer32_clearInterruptFlag(TIMER32_1_BASE);

    /*开始填充用户代码*/

    /*结束填充用户代码*/
}



/*********************************************************************************************************/
