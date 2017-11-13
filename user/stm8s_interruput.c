
#include "stm8s.h"
#include "stm8s_uart1.h"
#include "gpio_init.h"
#include "uart_init.h"
#include "tim1.h"
#include "stm8s_tim1.h"

extern uint8_t uart1_handle_enable;
extern uint8_t uart_rx_data[50];
extern uint8_t uart_rx_num;
u8 read_srdr;
extern uint8_t uart_rx_timeout_enable;
extern uint16_t uart_rx_timeout_cnt;

#pragma vector=1
__interrupt void TRAP_IRQHandler(void)
{
  
}
#pragma vector=2
__interrupt void TLI_IRQHandler(void)
{
  
}
#pragma vector=3
__interrupt void AWU_IRQHandler(void)
{
  
}
#pragma vector=4
__interrupt void CLK_IRQHandler(void)
{
  
  
}
#pragma vector=5
__interrupt void EXTI_PORTA_IRQHandler(void)
{
  
}
#pragma vector=6
__interrupt void EXTI_PORTB_IRQHandler(void)
{
  
}
#pragma vector=7
__interrupt void EXTI_PORTC_IRQHandler(void)
{
    
}
#pragma vector=8
__interrupt void EXTI_PORTD_IRQHandler(void)
{

  
  
}
#pragma vector=9
__interrupt void EXTI_PORTE_IRQHandler(void)
{

}

#ifdef STM8S903
#pragma vector=0xA
__interrupt void EXTI_PORTF_IRQHandler(void)
{
  
}
#endif
#ifdef STM8S208
#pragma vector=0xA
__interrupt void CAN_RX_IRQHandler(void)
{
  
}
#pragma vector=0xB
__interrupt void CAN_TX_IRQHandler(void)
{
  
}
#endif
#pragma vector=0xC
__interrupt void SPI_IRQHandler(void)
{
  
}
#pragma vector=0xD
__interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void)
{
    TIM1_ClearITPendingBit(TIM1_IT_UPDATE);
    TIM1_ISR_handler();
}
#pragma vector=0xE
__interrupt void TIM1_CAP_COM_IRQHandler(void)
{
  
}
#ifdef STM8S903
#pragma vector=0xF
__interrupt void TIM5_UPD_OVF_BRK_TRG_IRQHandler(void)
{
  
}
#pragma vector=0x10
__interrupt void TIM5_CAP_COM_IRQHandler(void)
{
  
}
#else
#pragma vector=0xF
__interrupt void TIM2_UPD_OVF_BRK_IRQHandler(void)
{
     
}
#pragma vector=0x10
__interrupt void TIM2_CAP_COM_IRQHandler(void)
{
  
}
#endif
#if defined (STM8S208) || defined(STM8S207) || defined(STM8S105)
#pragma vector=0x11
__interrupt void TIM3_UPD_OVF_BRK_IRQHandler(void)
{
  
}
#pragma vector=0x12
__interrupt void TIM3_CAP_COM_IRQHandler(void)
{
  
}
#endif
//#ifndef STM8S105
#if defined (STM8S208) || defined(STM8S207) || defined(STM8S105)
#pragma vector=0x13
__interrupt void UART1_TX_IRQHandler(void)
{
  
}
#pragma vector=0x14
__interrupt void UART1_RX_IRQHandler(void)
{ 
    if(UART1_GetITStatus(UART1_IT_IDLE)!=RESET)
    {
        read_srdr=UART1->SR;
        read_srdr=UART1->DR;
        
        uart_rx_timeout_enable=0;
        uart_rx_timeout_cnt=0;
        uart_rx_timeout_enable=1;
        
        
    }
    if(UART1_GetITStatus(UART1_IT_RXNE)!=RESET)
    {             
        read_srdr=UART1->SR;
        read_srdr=UART1->DR;
        //added in 11.11 12:00
        if(uart_rx_num < 255)
        {
          uart_rx_data[uart_rx_num++]=UART1_ReceiveData8();
        }
    }
}
#endif
#pragma vector=0x15
__interrupt void I2C_IRQHandler(void)
{
  
}
#ifdef STM8S105
#pragma vector=0x16
__interrupt void UART2_TX_IRQHandler(void)
{
   
}
#pragma vector=0x17
__interrupt void UART2_RX_IRQHandler(void)
{
   
}
#endif
#if defined(STM8S207) || defined(STM8S208)
#pragma vector=0x16
__interrupt void UART3_TX_IRQHandler(void)
{
  
}
#pragma vector=0x17
__interrupt void UART3_RX_IRQHandler(void)
{
  
}
#endif
#if defined(STM8S207) || defined(STM8S208)
#pragma vector=0x18
__interrupt void ADC2_IRQHandler(void)
{
   
}
#else
#pragma vector=0x18
__interrupt void ADC1_IRQHandler(void)
{
   
}
#endif
#ifdef STM8S903
#pragma vector=0x19
__interrupt void TIM6_UPD_OVF_TRG_IRQHandler(void)
{
  
}
#else
#pragma vector=0x19
__interrupt void TIM4_UPD_OVF_IRQHandler(void)
{
  
}
#endif
#pragma vector=0x1A
__interrupt void EEPROM_EEC_IRQHandler(void)
{
  
}


