







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
// 0x00 - был отключен
// 0x01 - был включен
static unsigned char adcstate[16];
static char *value_cmd[16];

char datafilepath[] = "/tmp/out.txt";


int init_ADC()
{
	char basepath[PATH_MAX];
	char cwd[PATH_MAX];
	FILE *pfh;
	int cnt;

	syslog(LOG_DEBUG, "int init_ADC()");
	fprintf(log_stream, "Debug: int init_ADC()\n");

	if(getcwd(cwd, sizeof(cwd)) == NULL)
	{
		syslog(LOG_ERR, "getcwd() error");
		fprintf(log_stream, "getcwd() error\n");
		return EXIT_FAILURE;
	}

	if(strcmp(cwd, "/") == 0)
	{ // Запущен демон
		strcpy(basepath, "/sys/devices/platform/ast_adc.0");
	}
	else
	{
		strcpy(basepath, cwd);
		strcat(basepath, "/test/ast_adc.0");
	}

	fprintf(log_stream, "basepath: %s\n", basepath);

	cnt = 0;
	for(int i=0; i<16; i++)
	{
		// Включение канала
		// strcpy(cwd, basepath);
		// strcat(cwd, "/adc");
		// strcat(cwd, itoa(i));
		// strcat(cwd, "_en");

		sprintf(cwd, "%s/adc%d_en", basepath, i);
		fprintf(log_stream, "%s\n", cwd);

		if(access(cwd, F_OK) != -1)
		{
			fprintf(log_stream, "trace 1\n");
			pfh = fopen(cwd, "rw+");
			if(pfh != NULL)
			{
				fprintf(log_stream, "trace 2\n");
				if(fread(&adcstate[i], sizeof(char), 1, pfh) != 1)
				{ // Не смогли прочитать из файла 1 символ
					adcstate[i] = 0xff;
					fprintf(log_stream, "trace 3\n");
				}
				else
				{
					fputc('1', pfh);
					cnt++;
					fprintf(log_stream, "trace 4\n");
				}
			}
			else
			{
				adcstate[i] = 0xff;
				fprintf(log_stream, "trace 5\n");
			}
			fclose(pfh);
		}
		else
		{
			adcstate[i] = 0xff;
			fprintf(log_stream, "trace 6\n");
		}
	}
	// В этом месте включили каналы, которые смогли

	if(cnt == 0)
	{
		return EXIT_FAILURE;
	}
	else
	{
		for(int i=0; i<16; i++)
		{
			fprintf(log_stream, "adc%d state 0x%02x\n", i, adcstate[i]);
			value_cmd[i] = malloc(strlen(basepath) + 20);
			sprintf(value_cmd[i], "%s/adc%d_value", basepath, i);
		}
		// return EXIT_FAILURE;
		return EXIT_SUCCESS;
	}
}

void do_ADC()
{
	char outbuf[PATH_MAX];
	char buf[30];
	FILE *pfh;
	// syslog(LOG_DEBUG, "void do_ADC()");
	fprintf(log_stream, "void do_ADC()\n");
	outbuf[0] = 0;
	for(int i=0; i<16; i++)
	{
		if(adcstate[i] != 0xff)
		{
			if((pfh = fopen(value_cmd[i], "r")) != NULL)
			{
				fgets(buf, sizeof(buf), pfh);
				fclose(pfh);
			}
			else
			{
				sprintf(buf, "chn %d no value", i);
			}
			strcat(outbuf, buf);
			strcat(outbuf, "\n");
		}
		else
		{
			sprintf(buf, "chn %d no value\n", i);
			strcat(outbuf, buf);
		}
	}
	if((pfh = fopen(datafilepath, "w")) != NULL)
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
		free(value_cmd[i]);
	}
}





