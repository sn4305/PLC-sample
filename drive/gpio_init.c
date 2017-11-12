

#include "gpio_init.h"

unsigned int my_addr;


void gpio_init(void)
{
    GPIO_Init(GPIOD, IN1_PIN, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(GPIOD, IN2_PIN, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(GPIOA, IN3_PIN, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(GPIOA, IN4_PIN, GPIO_MODE_IN_PU_NO_IT);
    
    GPIO_Init(GPIOC, ADDR0_PIN, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(GPIOC, ADDR1_PIN, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(GPIOC, ADDR2_PIN, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(GPIOC, ADDR3_PIN, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(GPIOC, ADDR4_PIN, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(GPIOB, ADDR5_PIN, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(GPIOB, ADDR6_PIN, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(GPIOA, ADDR7_PIN, GPIO_MODE_IN_PU_NO_IT);
    
    GPIO_Init(RS485_EN_PORT, RS485_EN_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
    
    my_addr=0;     
    if(GPIO_ReadInputPin(GPIOC, ADDR0_PIN)==SET)
    {
        my_addr|=0x01;    //0000 0001
    }
    if(GPIO_ReadInputPin(GPIOC, ADDR1_PIN)==SET)
    {
        my_addr|=0x02;   //0000 0010
    }
    if(GPIO_ReadInputPin(GPIOC, ADDR2_PIN)==SET)
    {
        my_addr|=0x04;   //0000 0100
    }
    if(GPIO_ReadInputPin(GPIOC, ADDR3_PIN)==SET)
    {
        my_addr|=0x08;   //0000 1000
    }
    if(GPIO_ReadInputPin(GPIOC, ADDR4_PIN)==SET)
    {
        my_addr|=0x10;   //0001 0000
    }
    if(GPIO_ReadInputPin(GPIOB, ADDR5_PIN)==SET)
    {
        my_addr|=0x20;   //0010 0000
    }
    if(GPIO_ReadInputPin(GPIOB, ADDR6_PIN)==SET)
    {
        my_addr|=0x40;   //0100 0000
    }
    if(GPIO_ReadInputPin(GPIOA, ADDR7_PIN)==SET)
    {
        my_addr|=0x80;   //1000 0000
    }

}

void RS485_high(void)
{
    GPIO_WriteHigh(RS485_EN_PORT, RS485_EN_PIN);
}

void RS485_low(void)
{
    GPIO_WriteLow(RS485_EN_PORT, RS485_EN_PIN);
}



