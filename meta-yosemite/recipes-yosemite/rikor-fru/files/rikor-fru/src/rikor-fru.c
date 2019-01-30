

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "crc16.h"
#include "rikor-fru.h"


#ifndef DEBUG
#define DEBUG
#endif

int fru_buf_init(rikor_fru_t *const data)
{
	data->id = 0xaa5555aa;
	data->board_id = 0x1234567890abcdefL;
	data->ip1 = (192<<24) | (168<<16) | (0<<8) | (220);
	return EXIT_SUCCESS;
}



int read_fru(const char *device, rikor_fru_t *const data)
{
	// unsigned char buf[256];
	FILE *fp;
	unsigned short crc;
	unsigned short fcrc;
	int rc;

	fp = fopen(device, "rb");
	if (!fp)
	{
		int err = errno;

#ifdef DEBUG
		// syslog(LOG_INFO, "failed to open device %s", device);
		fprintf(stderr, "failed to open device %s\n", device);
#endif
		return err;
	}

	rc = fread(data, sizeof(rikor_fru_t), 1, fp);
	rc += fread(&fcrc, 2, 1, fp);
	fclose(fp);

	if (rc != 2)
	{
#ifdef DEBUG
		// syslog(LOG_INFO, "failed to read device %s", device);
		fprintf(stderr, "failed to read device %s\n", device);
#endif
		return ENOENT;
	} 
	else
	{
		crc = crc16(0, (const u8 *)data, sizeof(rikor_fru_t));
		if(fcrc != crc)
		{ // Ошибка CRC
#ifdef DEBUG
			// syslog(LOG_INFO, "failed to read device %s", device);
			fprintf(stderr, "CRC error in device %s\n", device);
#endif
			return ERRCRC;
		}
		return 0;
	}

	// crc = crc16(0, (const u8 *)data, sizeof(rikor_fru_t));
	// fprintf(stderr, "crc16(0) %d\n", crc);
	// fprintf(stderr, "%d\n%d\n%d\n", (crc + (~crc) + 1), crc * (~crc), crc - ~crc);
	// return -1;
}



int write_fru(const char *device, const rikor_fru_t *const data)
{
	FILE *fp;
	unsigned short crc;
	int rc;

	fp = fopen(device, "wb");
	if (!fp)
	{
		int err = errno;

#ifdef DEBUG
		// syslog(LOG_INFO, "failed to open device %s", EEPROM_PATH);
		fprintf(stderr, "failed to open device %s\n", EEPROM_PATH);
#endif
		return err;
	}

	rc = fwrite(data, sizeof(rikor_fru_t), 1, fp);
	crc = crc16(0, (const u8 *)data, sizeof(rikor_fru_t));
	rc += fwrite(&crc, 2, 1, fp);
	fclose(fp);

	return 0;
}

