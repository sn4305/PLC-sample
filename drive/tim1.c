#include "tim1.h"
#include "stm8s_tim1.h"


uint8_t bd_arm1_enable=1;
uint16_t bd_arm1_cnt=0;
uint8_t bd_arm1_execute=0;
uint32_t uart_rx_timeout_settime=800;  //updated from 100 to 500ms,to 800ms
uint8_t uart_rx_timeout_enable=0;  
uint16_t uart_rx_timeout_cnt=0;
extern uint8_t uart1_handle_enable;


void Tim1_Init(void)
{
    TIM1_TimeBaseInit(16,TIM1_COUNTERMODE_UP,1000,0);
    TIM1_ARRPreloadConfig(ENABLE);//ʹ���Զ���װ
    TIM1_ITConfig(TIM1_IT_UPDATE,ENABLE);//���ݸ����ж�
    TIM1_Cmd(ENABLE);//����ʱ��
}

void TIM1_ISR_handler(void)
{
    if(bd_arm1_enable==1)
    {
        bd_arm1_cnt++;
        if(bd_arm1_cnt>=500)
        {
            bd_arm1_cnt=0;
            bd_arm1_execute=1;
        }
    }
    if(uart_rx_timeout_enable==1)
    {
        uart_rx_timeout_cnt++;
        if(uart_rx_timeout_cnt>=uart_rx_timeout_settime)
        {
            uart_rx_timeout_enable=0;
            uart_rx_timeout_cnt=0;
            uart1_handle_enable=1;           
        }
    } 
}


