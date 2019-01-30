#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//#define LINAPP				//При компиляции для AST2400 эту строку закоментировать
#define DEFLENGTH	70

char str[DEFLENGTH];

unsigned int pwmc[8] = {30, 30, 30, 30, 30, 30, 40 ,40};
unsigned int curtemp[5];
char pattern[48] = "/usr/local/fbpackages/fan_ctrl/set_fan_speed.sh ";
char buffer[52];
//char patnum = " ";
char pwmval[2];
char arg[4];

/********************************************************************************************/
//Примитивы
int get_num(char *data, int num);			//Преобразование char -массива в int
											//data - указатель на входную строку
											//num - номер строки в исходном файле
void set_coef(int *tempr);					//Расчет
											//tempr - указатель на входной массив
									
/********************************************************************************************/

int main()
{
	int ctemp = 0;			//текущее значение температуры
	int str_cnt = 1;
	FILE *mf;				//буффер для потока		
	char *estr;
	int cnt = 0;

	memset(curtemp, 0, 4*sizeof(curtemp));

	#ifdef LINAPP
	mf = fopen("sensors.txt", "r");
	#else		//LINAPP
	//TODO: файл должен быть /www/pages/sensors.log (ну или путь надо будет уточнить)
	mf = fopen("/www/pages/sensors.log", "r");
	#endif		//LINAPP

	#ifdef LINAPP
	if (mf == NULL)
	{
		printf("File read error\n");
		return -1;
	}
	else
	{
		printf ("File read success\n");
	}
	#endif		//LINAPP

	while (feof(mf) == 0)
	{
		//Пока не достигнут конец файла читаем строка за строкой
		fgets(str, sizeof(str), mf);

		if (str_cnt == 27 || str_cnt == 31 || str_cnt == 35 || str_cnt == 39 || str_cnt == 43)
		{
			#ifdef LINAPP
			//Просто тестовая печать интересующих строк
			printf("%s\n", str);
			#endif

			ctemp = get_num(str, str_cnt);

			#ifdef LINAPP
			//Просто тестовая печать интересующих строк
			printf("%d\n", (short)ctemp);
			#endif

			curtemp[cnt] = ctemp;
			cnt++;

		}

		str_cnt++;
	}

	//Пересчет ШИМ
	set_coef(&curtemp);

	//Установка значений
	for (int i=0; i<8; i++)
	{
		memset(buffer, 0, sizeof(buffer));
		memset(arg, 0, sizeof(buffer));
		strcpy(buffer, pattern);
		char dt[3];
		char dn[2];
		char blank[2] = {" "};
		unsigned int pwmb1 = pwmc[i];
		unsigned int pwmb2 = pwmc[i]/10;
		dt[0] = (pwmb2 % 10) + '0';
		dt[1] = (pwmb1 % 10) + '0';
		dt[2] = '\0';
		dn[0] = (i % 10) + '0';
		dn[1] = '\0';
		strcat(arg, dt);
		strcat(blank, dn);
		strcat(arg, blank);
		strcpy(buffer, pattern);
		strcat(buffer, arg);
		#ifdef LINAPP
		printf("%s\n", buffer);
		#endif
		system(buffer);
	}

	#ifdef LINAPP
	printf("File read complete\n");
	#endif		//LINAPP
	fclose(mf);
	return 0;
}

/********************************************************************************************/
int get_num(char *data, int num)
{
    int res = 0;
	char buf[2];		//буфер для хранения текущей температуры в массиве char
	if (num != 43)
	{
		buf[0] = data[16];
		buf[1] = data[17];
	}
	else
	{
		buf[0] = data[19];
		buf[1] = data[20];
	}
	res = atoi(&buf);
	return res;
}

/********************************************************************************************/
void set_coef(int *tempr)
{
	unsigned int dbuf = (tempr[3]+tempr[4])/2;
	unsigned int pwmbuf = dbuf*40/20;
	if (pwmbuf > 99) pwmbuf = 99;
	pwmc[6] = pwmbuf;
	pwmc[7] = pwmbuf;

	#ifdef LINAPP
	printf ("DEBUG1: %d\n", (unsigned int)pwmbuf);
	#endif		//LINAPP

	dbuf = (tempr[0]+tempr[1]+tempr[2])/3;
	pwmbuf = dbuf*30/20;
	if (pwmbuf > 99) pwmbuf = 99;

	pwmc[0] = pwmbuf;
	pwmc[1] = pwmbuf;
	pwmc[2] = pwmbuf;
	pwmc[3] = pwmbuf;
	pwmc[4] = pwmbuf;
	pwmc[5] = pwmbuf;

	#ifdef LINAPP
	printf ("DEBUG2: %d\n", (unsigned int)pwmbuf);
	#endif		//LINAPP
}

