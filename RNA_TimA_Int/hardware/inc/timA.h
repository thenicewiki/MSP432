/****************************************************/
// MSP432P401R
// 定时器A
// Bilibili：m-RNA
// E-mail:m-RNA@qq.com
// 创建日期:2021/8/26
/****************************************************/

#ifndef __RNA_TIMA_H
#define __RNA_TIMA_H
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

extern uint8_t TIMA2_CAP_STA;
extern uint16_t TIMA2_CAP_VAL;

void TimA0_Int_Init(uint16_t ccr0, uint16_t psc);
void TimA1_Int_Init(uint16_t ccr0, uint16_t psc);


void TimA2_Int_Init(void);


void Tim32_0_Int_Init(uint32_t aar, uint8_t psc);
void Tim32_1_Int_Init(uint32_t aar, uint8_t psc);


void NVIC_Configuration(void);

void Task_1s_Thread(void);
void Task_2s_Thread(void);


#endif
