
#ifndef __GPIO_INIT_H
#define __GPIO_INIT_H
#include "stm8s_gpio.h"


#define IN1_PIN   GPIO_PIN_3
#define IN2_PIN   GPIO_PIN_2
#define IN3_PIN   GPIO_PIN_1
#define IN4_PIN   GPIO_PIN_2
#define ADDR0_PIN   GPIO_PIN_7
#define ADDR1_PIN   GPIO_PIN_6
#define ADDR2_PIN   GPIO_PIN_5
#define ADDR3_PIN   GPIO_PIN_4
#define ADDR4_PIN   GPIO_PIN_3
#define ADDR5_PIN   GPIO_PIN_4
#define ADDR6_PIN   GPIO_PIN_5
#define ADDR7_PIN   GPIO_PIN_3

#define RS485_EN_PIN GPIO_PIN_4
#define RS485_EN_PORT GPIOD



void gpio_init(void);
void RS485_high(void);
void RS485_low(void);



#endif

