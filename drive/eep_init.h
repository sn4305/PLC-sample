#ifndef __EEP_INIT_H
#define	__EEP_INIT_H

#include "stm8s.h"
#include <stdio.h>

void eeprom_read(u32 addr, u8 *read_data, u8 read_len);
void eeprom_write(u32 addr, u8 *write_data, u8 write_len);
void eeprom_data_update(void);
void read_config_from_eeprom(void);


#endif