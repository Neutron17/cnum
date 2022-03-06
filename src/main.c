/*
 * Neutron17
 * 	cnum
 * 	GPL v3
 * github.com/Neutron17
 * gitlab.com/Neutron17
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>	// true, false
#include <string.h>	// strcpy
#include <limits.h>	// UINT_MAX	(main) {rand}
#include <time.h>	// rand		(main)
#include <getopt.h>	// getopt	(parseArgs)
#include "stdext.h"	// itoa		(main)

#define CMD_SZ 16

void inc(unsigned *n, int arg);
void dcr(unsigned *n, int arg);
void shl(unsigned *n, int arg);
void shr(unsigned *n, int arg);
void new(unsigned *n, int arg);
void add(unsigned *n, int arg);
void rem(unsigned *n, int arg);
void print(unsigned *n, int arg);
void dec(unsigned *n, int arg);
void hex(unsigned *n, int arg);
void bin(unsigned *n, int arg);
void oct(unsigned *n, int arg);

typedef void (*CmdFn)(unsigned*, int);
const CmdFn cmdFns[CMD_SZ] = {
	inc, dcr,
	shl, shr,
	new, new,
	add, rem,
	print, print, print, print,
	dec, hex, bin, oct
};
const char *commands[CMD_SZ] = {
	"inc", "dcr",	// increment, decrement
	"shl", "shr",	// shift left/right
	"set", "new",	// sets current number
	"add", "rem",	// add rem %n%
	"prt", "p", "prnt", "print", // print
	"dec", "hex", "bin", "oct"
};
const bool takesArg[CMD_SZ] = {
	false, false,	// inc dec
	true,  true,	// shl shr
	true,  true,	// set new
	true,  true,	// add rem
	false, false, false, false, // print
	false, false, false, false
};
enum CmdEnum {
	E_INC, E_DCR,
	E_SHL, E_SHR,
	E_SET, E_NEW,
	E_ADD, E_REM,
	E_PRT, E_P, E_PRNT, E_PRINT,
	E_DEC, E_HEX, E_BIN, E_OCT
};
enum PrintEnum { P_DEC, P_HEX, P_BIN, P_OCT };

#define VERSION 1.2

bool isDebug = false;
bool useLast = true;
bool useArg  = false;
char numStr[7];
unsigned num;


void parseArgs(int argc, char *argv[]);
bool isInLUT(const char *command);

int main(int argc, char *argv[]) {
	srand(time(NULL));	// seed
	parseArgs(argc, argv);	// dps: isDebug, useLast, numStr 
	if(useLast)
		strcpy(numStr, argv[argc-1]);
	num = atoi(numStr);
	if(num == 0) { // atoi failed
		num = rand() % UINT_MAX;
		printf("No number set, using random: %u\n", num);
	}
        //strcpy(str, "00000000");
	char *cmd = (char *) malloc(64 * sizeof(char));
	int arg = -0;
 	while(true) {
	//	ptr = (unsigned char *)&num;
inchk:
		useArg = false;
		printf("> ");
		scanf("%64s", cmd);
		if(strcmp(cmd, "q") == 0) {
			printf("Exiting\n");
			goto exit;
		}
		for(int i = 0; i < CMD_SZ; i++) {
			if(isDebug)
				printf("Checking: %s\n", commands[i]);
			if(strcmp(commands[i], cmd) == 0) {
				if(takesArg[i]) {
					if(isDebug) {
						printf("Commands %s takes argument\n",
								commands[i]); 
					}
					scanf("%d", &arg);
					useArg = true;
				}
				if(isDebug)
					printf("%s\n", commands[i]);
				cmdFns[i](&num, arg);
				break;
			}
		}
		if(!isInLUT(cmd)) {
			if(isDebug)
				printf("Command: %s\n", cmd);
			printf("Not a command\n");
			goto inchk;
		}	
	}
exit:
        //free(str);
	free(cmd);
	return EXIT_SUCCESS;
}

void inc(unsigned *n, int arg) { *n = *n + 1; }
void dcr(unsigned *n, int arg) { *n = *n - 1; }
void shl(unsigned *n, int arg) { *n = *n << arg; }
void shr(unsigned *n, int arg) { *n = *n >> arg; }
void new(unsigned *n, int arg) { *n = arg; }
void add(unsigned *n, int arg) { *n += arg; }
void rem(unsigned *n, int arg) { *n -= arg; }
void print(unsigned *n, int arg) {
        char buff[9] = "00000000\0";
	char  str[9] = "00000000\0";
	char foo [9] = "00000000\0";
        unsigned char *ptr = (unsigned char *) n;
	unsigned char size = 8;
	for(int i = 0; i<sizeof(*n); i++) {
		switch(arg) {
			case P_DEC:
				strcpy(str, "000");
				strcpy(buff,"000");
				//size = 3; // 255
				DEC(*ptr, buff);
				break;
			case P_HEX:
				//strcpy(foo, "  ");
				strcpy(str, "00");
				strcpy(buff,"00");
				//size = 2; // ff
				HEX(*ptr, buff);
				break;
			case P_BIN: // default
				//size = 8; // 11111111
				BIN(*ptr, buff);
				break;
			case P_OCT:
				strcpy(str,  "0000");
				strcpy(buff, "0000");
				//size = 4; // 1103
				OCT(*ptr, buff);
				break;
		}
               	//BIN(*ptr, buff);
		//printf("str %s buff %s %d ");
                strcpy(str+strlen(str)-strlen(buff), buff);
		if(isDebug) {
               		printf(
               		"i:%d str:%s buff:%s num:%u\n" /*"ptr:%p\n"*/
               		,i,str,buff,*n/*,(void *)ptr-(void *)n*/);
		}
               	printf(/*"\e[41m"*/"%s"/*"\e[0m*/"\n", str);
                //strcpy(str, "00000000");
                //strcpy(buff, "00000000");
                ptr++;
	}
}
void dec(unsigned *n, int arg) { print(n, P_DEC); }
void hex(unsigned *n, int arg) { print(n, P_HEX); }
void bin(unsigned *n, int arg) { print(n, P_BIN); }
void oct(unsigned *n, int arg) { print(n, P_OCT); }

// TODO faster search algorithm
bool isInLUT(const char *command) {
	for(int i = 0; i < CMD_SZ; i++) {
		if(strcmp(commands[i], command) == 0) 
			return true;
	}
	return false;
}

void parseArgs(int argc, char *argv[]) {
	int c;
	while((c = getopt(argc, argv, "Vdvn:")) != -1) {
		switch(c) {
			case 'v':
			case 'd':
				isDebug = true;
				break;
			case 'V':
				printf("Version: %f\n", VERSION);
				exit(0);
				break;
			case 'n':
				if(isDebug)
					printf("Parsed argument 'n'\n");
				useLast = false;
				strcpy(numStr, optarg);
				break;
		}
	}
}



