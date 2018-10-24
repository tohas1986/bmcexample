







// Получение списка директорий (файлов) на С
// How to recursively list directories in C on Linux?
// https://stackoverflow.com/a/8438663

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>

#include "daemon.h"
#include "adc.h"



/// !!! Generic C Containers
// https://github.com/pmj/genccont


// Состояния каналов
// 0xff - не инициализирован
// 0x30 ('0') - был отключен
// 0x31 ('1') - был включен
ADCChnData_t adcchndata[16];

static int do_adc_cnt;



int adc_reg_read(const char * cmd, char *val, int val_size)
{
	FILE *pfh;

	if((pfh = fopen(cmd, "r")) != NULL)
	{
		fgets(val, val_size, pfh);
		fclose(pfh);
		for(int i=strlen(val); (val[i] <= ' ') && (i>0); i--) val[i] = 0;
	}
	else
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int adc_reg_write(const char * cmd, char *val)
{
	FILE *pfh;

	if((pfh = fopen(cmd, "w+")) != NULL)
	{
		fputs(val, pfh);
		fclose(pfh);
	}
	else
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


int init_ADC()
{
	char cwd[PATH_MAX];
	char cmd[PATH_MAX];
	char ret_string[16];
	int ret;
	int cnt;

	syslog(LOG_DEBUG, "int init_ADC()");
	fprintf(log_stream, "Debug: int init_ADC()\n");

	fprintf(log_stream, "basepath: %s\n", daemon_cfg.basepath);

	cnt = 0;
	for(int i=0; i<16; i++)
	{
		// Включение канала
		sprintf(cwd, "%s/adc%d", daemon_cfg.basepath, i);
		fprintf(log_stream, "%s\n", cwd);

		strcpy(cmd, cwd);
		strcat(cmd, "_en");
		ret = adc_reg_read(cmd, ret_string, sizeof(ret_string));
		if(ret == EXIT_SUCCESS)
		{ // Есть канал с таким номером
			adcchndata[i].en = ret_string[0];
			ret_string[0] = '1';
			ret_string[1] = 0;
			ret = adc_reg_write(cmd, ret_string);

			strcpy(cmd, cwd);
			strcat(cmd, "_r1");
			sprintf(ret_string, "%d", adcchndata[i].r1);
			ret = adc_reg_write(cmd, ret_string);

			strcpy(cmd, cwd);
			strcat(cmd, "_r2");
			sprintf(ret_string, "%d", adcchndata[i].r2);
			ret = adc_reg_write(cmd, ret_string);

			strcpy(cmd, cwd);
			strcat(cmd, "_v2");
			sprintf(ret_string, "%d", adcchndata[i].v2);
			ret = adc_reg_write(cmd, ret_string);

			if(adcchndata[i].value_cmd != NULL) free(adcchndata[i].value_cmd);
			adcchndata[i].value_cmd = malloc(strlen(daemon_cfg.basepath) + 20);
			if(adcchndata[i].value_cmd != NULL)
				sprintf(adcchndata[i].value_cmd, "%s_value", cwd);

			cnt++;
		}
		else
		{
			fprintf(log_stream, "Can't access channel %d\n", i);
			adcchndata[i].en = 0xff;
		}

	}

	if(cnt == 0)
	{ // Не смогли сконфигурировать ни одного канала
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}




void do_ADC()
{
	char outbuf[2048];   // 16 строк по 128 байт на строку
	char outstr[132];
	char buf[30];
	FILE *pfh;

	sprintf(outbuf, "%d\n", do_adc_cnt++);
	for(int i=0; i<16; i++)
	{
		if(adcchndata[i].en != 0xff)
		{
			if(adc_reg_read(adcchndata[i].value_cmd, buf, sizeof(buf)) == EXIT_SUCCESS)
			{
				sprintf(outstr, "adc%2d  %s  \"%s\"\n", i, buf, adcchndata[i].name);
			}
			else
			{
				sprintf(outstr, "chn %d no value\n", i);
			}
			strcat(outbuf, outstr);
		}
		else
		{
			sprintf(buf, "chn %d no value\n", i);
			strcat(outbuf, buf);
		}
	}

	if((pfh = fopen(daemon_cfg.datafilepath, "w")) != NULL)
	{
		fputs(outbuf, pfh);
		fclose(pfh);
	}
	else
	{
		// syslog(LOG_ERR, "Can not create out data file");
		fprintf(log_stream, "Can not create out data file\n");
	}
}



void deinit_ADC()
{
	// syslog(LOG_DEBUG, "void deinit_ADC()");
	fprintf(log_stream, "void deinit_ADC(): DEINIT\n");
	for(int i=0; i<16; i++)
	{
		if(adcchndata[i].value_cmd != NULL)
		{
			free(adcchndata[i].value_cmd);
			adcchndata[i].value_cmd = NULL;
		}
	}
}





