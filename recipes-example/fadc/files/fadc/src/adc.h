#ifndef ADC_H
#define ADC_H


typedef struct 
{
	int r1;
	int r2;
	int v2;
	char *name;
	char *value_cmd;
	unsigned char en;
}ADCChnData_t;


extern ADCChnData_t adcchndata[16];


int init_ADC();

void do_ADC();

void deinit_ADC();

#endif // ADC_H
