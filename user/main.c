
#include "stm8s.h"
#include "stm8s_clk.h"
#include "stm8s_flash.h"
#include "stm8s_gpio.h"
#include "gpio_init.h"
#include "uart_init.h"
#include "string.h"
#include "stm8s_itc.h"
#include "tim1.h"

uint8_t uart1_handle_enable=0;
uint8_t uart_rx_data[50]={0};
uint8_t uart_rx_num=0;
extern uint8_t LED1_execute;
extern uint8_t bd_arm1_execute;

//extern u8 my_addr;

unsigned int IN_value=0;

void delay_us(uint16_t nCount)
{
    nCount *=3.2; 
    while(--nCount);
}


void delay_ms(uint16_t nCount)
{
    while(nCount--)
    {
        delay_us(1000);
    }
}


int main(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
    ITC_SetSoftwarePriority(ITC_IRQ_UART1_RX, ITC_PRIORITYLEVEL_0);
    gpio_init();
    UART1_Configuration();
    ITC_SetSoftwarePriority(ITC_IRQ_UART1_RX, ITC_PRIORITYLEVEL_0);
    Tim1_Init();
    __enable_interrupt();
    
    while(1)
    { 
        if(bd_arm1_execute==1)
        {
            bd_arm1_execute=0;
            if(GPIO_ReadInputPin(GPIOD, IN1_PIN)==SET)
            {
                IN_value|=0x01;   //0000 0001
            }
            else
            {
                IN_value&=0xfe;   //1111 1110
            }
            if(GPIO_ReadInputPin(GPIOD, IN2_PIN)==SET)
            {
                IN_value|=0x02;   //0000 0010
            }
            else
            {
                IN_value&=0xfd;   //1111 1101
            }
//            if(GPIO_ReadInputPin(GPIOA, IN3_PIN)==SET)
//            {
//                IN_value|=0x04;   //0000 0100
//            }
//            else
//            {
//                IN_value&=0xfb;   //1111 1011
//            }
//            if(GPIO_ReadInputPin(GPIOA, IN4_PIN)==SET)
//            {
//                IN_value|=0x08;   //0000 1000
//            }
//            else
//            {
//                IN_value&=0xf7;   //1111 0111 
//            }
            IN_value&=0xfb;   //1111 1011
            IN_value&=0xf7;   //1111 0111
        }
        if(uart1_handle_enable==1)
        {
            uart1_handle_enable=0;
            UART1_rx_handler(uart_rx_data,uart_rx_num);
            uart_rx_num=0;
        }   
        
    }
}



