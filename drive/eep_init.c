#include "eep_init.h"
#include "stm8s_flash.h"


#define FLASH_FIRST_CHAR ('z')
extern u32 baudrate_value;
u8 baudrate_type=3;
u32 eeprom_addr=0x4000;

u8 rd_flash[6]={0};
u8 wr_flash[6]={0};

u8 In1_type=1;    // 0 for NC and 1 for NO
u8 In2_type=1;  
u8 Out1_type=4;   // 0: None  1:In1   2:In2  3:In1&In2  4: In1|In2
u8 Out2_type=4;

extern void delay_ms(uint16_t nCount);

void eeprom_read(u32 addr, u8 *read_data, u8 read_len)
{
    u8 rd_temp;
    for(rd_temp=0;rd_temp<read_len;rd_temp++)
    {
        read_data[rd_temp]=FLASH_ReadByte(addr+rd_temp);
    }
}

void eeprom_write(u32 addr, u8 *write_data, u8 write_len)
{
    u8 wr_temp;
    FLASH_Unlock(FLASH_MEMTYPE_DATA);
    for(wr_temp=0;wr_temp<write_len;wr_temp++)
    {
        FLASH_EraseByte(eeprom_addr+wr_temp);
        delay_ms(1);
    }
    for(wr_temp=0;wr_temp<write_len;wr_temp++)
    {
        FLASH_ProgramByte(eeprom_addr+wr_temp,write_data[wr_temp]);
        delay_ms(1);
    }
    FLASH_Lock(FLASH_MEMTYPE_DATA);
}


void eeprom_data_update(void)
{
    wr_flash[0]=FLASH_FIRST_CHAR;
    wr_flash[1]=baudrate_type;
    wr_flash[2]=In1_type;
    wr_flash[3]=In2_type;
    wr_flash[4]=Out1_type;
    wr_flash[5]=Out2_type;
    eeprom_write(eeprom_addr,wr_flash,6);
}
                     

void read_config_from_eeprom(void)
{
    FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
    eeprom_read(eeprom_addr,rd_flash,6);
    if(rd_flash[0]!=FLASH_FIRST_CHAR)
    {
        eeprom_data_update();
    }
    else
    {
        baudrate_type=rd_flash[1];
        In1_type=rd_flash[2];
        In2_type=rd_flash[3];
        Out1_type=rd_flash[4];
        Out2_type=rd_flash[5];
    }
    switch(baudrate_type)
    {
        case 0x01:
            baudrate_value=2400;
            break;
        case 0x02:
            baudrate_value=4800;
            break;
        case 0x03:
            baudrate_value=9600;
            break;
        case 0x04:
            baudrate_value=19200;
            break;
        default:
            baudrate_value=9600;
            break;   
    }
}
	
