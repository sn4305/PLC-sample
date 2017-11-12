#include "uart_init.h"
#include <stdarg.h>
#include <stdio.h>
#include "eep_init.h"
#include "gpio_init.h"

#define LEN1 5

u32 baudrate_value=9600;
u8 reply_data[5]={0};
const u16 wCRCTalbeAbs[]={0x0000, 0xCC01, 0xD801, 0x1400, 0xF001, 0x3C00, 0x2800, 0xE401, 0xA001, 0x6C00, 0x7800, 0xB401, 0x5000, 0x9C01, 0x8801, 0x4400,};
u8 crc_low;
u8 crc_high;
u16 crc_value;
extern unsigned int IN_value;
extern unsigned int my_addr;
extern void delay_ms(uint16_t nCount);

void UART1_Configuration(void)  
{
    UART1_DeInit();   
    UART1_Init((u32)baudrate_value, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
    UART1_ITConfig(UART1_IT_IDLE, ENABLE);
    UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);
    UART1_Cmd(ENABLE);		
}

void UART1_Send_byte(u8 byte)  
{
    UART1_SendData8((unsigned char)byte);
    while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
}	

void UART1_Send_str(u8 *string, u16 len)
{
    u16 i;
    for(i=0;i<len;i++)
    {
        UART1_Send_byte(string[i]);
    }
}


u16 CRC16(u8 *pchMsg,u16 wDataLen)
{
    u16 wCRC=0xFFFF;
    u16 i;
    u8 chChar;
    for(i=0;i<wDataLen;i++)
    {
        chChar=*pchMsg++;
        wCRC=wCRCTalbeAbs[(chChar^wCRC)&15]^(wCRC>>4);
        wCRC=wCRCTalbeAbs[((chChar>>4)^wCRC)&15]^(wCRC>>4);
    }
    return wCRC;
}

uint16_t find_laststr(uint8_t *s1,uint16_t s1_len, uint8_t *s2,uint8_t *s3) //--ok
{
    uint16_t n,tt;
	uint16_t s3_len=0;
    uint8_t *ptr_s1,*ptr_s3;
    if(*s2)
    {
        ptr_s1=s1;
        for(tt=0;tt<s1_len;tt++)
        {
            for(n=0;*(ptr_s1+n)==*(s2+n);n++)
            {
                if(!(*(s2+n+1)))
                {
                    ptr_s3=ptr_s1;
                    s3_len=s1_len-tt;
                    break;
                }
            }
            ptr_s1++;
        }
        for(tt=0;tt<s3_len;tt++)
        {
            s3[tt]=ptr_s3[tt];
        }
        if(s3_len==0)
        {
            s3=NULL;
        }
        return s3_len;
    }
    else
    {
        for(tt=0;tt<s1_len;tt++)
        {
            s3[tt]=s1[tt];
        }
        return s1_len;
    }
}


void reply_to_server(void)
{                            
    reply_data[0]=0x04;
    reply_data[1]=my_addr;
    reply_data[2]=IN_value;            
    crc_value=CRC16(reply_data,3);
    crc_low=(u8)(crc_value&0xff);
    crc_high=(u8)((crc_value>>8)&0xff);
    reply_data[3]=crc_low;
    reply_data[4]=crc_high;
    
    
    UART1_Send_str(reply_data,5);

}

void UART1_rx_handler(uint8_t *pdata, uint8_t len)
{

//    uint8_t pdata1[5];
//    uint8_t s2[3];
//    s2[0] = 0x04;
//    s2[1] = my_addr;
//    s2[2] = 0xFF;
//    find_laststr(pdata,len,s2,pdata1);
//    
//    UART1_Send_str(pdata1,len1);
  
    uint8_t i;
    for(i=0;i < len;i++)  //added in 11.10  13:38
    {
      if(pdata[i]==0x04 && pdata[i+1]==my_addr && pdata[i+2]==0xff)
      {
        crc_value=CRC16(pdata+i,LEN1-2);
        crc_low=(u8)(crc_value&0xff);
        crc_high=(u8)((crc_value>>8)&0xff);
        if(pdata[i+LEN1-2]==crc_low && pdata[i+LEN1-1]==crc_high)
        {
          reply_to_server();
        }  
      }
      else
      {
        //        reply_to_server();
        //GPIO_WriteReverse(GPIOD, IN1_PIN);
      }
    }
}

	
