#include "eeprom.h"
#include "eeprom_emul.h"
#include "Arduino.h"



// --------------------------------------------------------------------------
// Private Variables
// --------------------------------------------------------------------------
static bool eeprom_initialised = false;


void eeprom_init() {
  if(!eeprom_initialised) {
    HAL_FLASH_Unlock();

    //__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

    /* EEPROM Init */
    if(EE_Init() != EE_OK)
    {
      while(1) {
        HAL_Delay(1);
      }
    }

    HAL_FLASH_Lock();
    eeprom_initialised = true;
  }

}

void eeprom_write_byte(unsigned char *pos, unsigned char value) {
  uint16_t eeprom_address = (unsigned) pos;

  eeprom_init();

  HAL_FLASH_Unlock();
  //__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
  if(EE_WriteVariable(eeprom_address, (uint16_t) value) != EE_OK) {
    while(1) {
      HAL_Delay(1);
    }
  }
  HAL_FLASH_Lock();
}

unsigned char eeprom_read_byte(unsigned char *pos) {
  uint16_t data = 0xFF;
  uint16_t eeprom_address = (unsigned) pos;

  eeprom_init();

  if(EE_ReadVariable(eeprom_address, &data) != EE_OK) {
    return (char) data;
  }
  return (char)data;
}

void eeprom_read_block (void *__dst, const void *__src, size_t __n) {
  uint16_t data = 0xFF;
  uint16_t eeprom_address = (unsigned) __src;

  eeprom_init();

  for(uint8_t c = 0; c < __n; c++) {
    EE_ReadVariable(eeprom_address+c, &data);
    *((uint8_t*)__dst + c) = data;
  }
}

void eeprom_update_block (const void *__src, void *__dst, size_t __n) {

}



