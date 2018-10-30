#ifndef DAEMON_H
#define DAEMON_H


#include <stdio.h>


typedef struct 
{
	char debug_mode;
	char *datafilepath;
	char *basepath;	
}daemon_cfg_t;

extern FILE *log_stream;

extern daemon_cfg_t daemon_cfg;

#endif // DAEMON_H