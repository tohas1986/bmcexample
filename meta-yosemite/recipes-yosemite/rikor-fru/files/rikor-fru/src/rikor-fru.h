

#ifndef RIKOR_FRU_H
#define RIKOR_FRU_H

#include <linux/types.h>

#define EEPROM_PATH "/sys/devices/platform/ast-i2c.3/i2c-3/3-0052/eeprom"

#define ERRCRC      -2


#pragma pack(push, 1)
typedef struct 
{
	unsigned int id;
	unsigned long long board_id;
	unsigned int ip1;
} rikor_fru_t;
#pragma pack(pop)

int fru_buf_init(rikor_fru_t *const data);
int read_fru(const char *device, rikor_fru_t *const data);
int write_fru(const char *device, const rikor_fru_t *const data);

#endif // RIKOR_FRU_H
