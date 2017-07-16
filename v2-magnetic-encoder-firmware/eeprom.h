#ifndef EEPROM_H
#define EEPROM_H

#include "Arduino.h"

// EEPROM
void eeprom_init();
void eeprom_write_byte(unsigned char *pos, unsigned char value);
unsigned char eeprom_read_byte(unsigned char *pos);
void eeprom_read_block (void *__dst, const void *__src, size_t __n);
void eeprom_update_block (const void *__src, void *__dst, size_t __n);

#endif
