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

#define CMD_SZ 7

void inc(unsigned *n, int arg);
void dec(unsigned *n, int arg);
void shl(unsigned *n, int arg);
void shr(unsigned *n, int arg);
void new(unsigned *n, int arg);
void add(unsigned *n, int arg);
void rem(unsigned *n, int arg);

typedef void (*CmdFn)(unsigned*, int);

const CmdFn cmdFns[CMD_SZ] = {
	inc,
	dec,
	shl,
	shr,
	new,
	add,
	rem
};
const char *commands[CMD_SZ] = {
	"inc",	// increment
	"dcr",	// decrement
	"shl",	// shift left
	"shr",	// shift right
	"new",	// new number
	"add",	// add %n%
	"rem"	// min %n%
};
enum CmdEnum {
	INC,
	DEC,
	SHL,
	SHR,
	NEW,
	ADD,
	REM
};

#define VERSION 1.1

bool isDebug = false;
bool useLast = true;
char numStr[7];
unsigned num;

void parseArgs(int argc, char *argv[]);
bool isInLUT(const char *command);

int main(int argc, char *argv[]) {
	srand(time(NULL));	// seed
	parseArgs(argc, argv);	// dps: isDebug, useLast, numStr 
        char buffer[9];
	if(useLast)
		strcpy(numStr, argv[argc-1]);
	num = atoi(numStr);
	if(num == 0) { // atoi failed
		num = rand() % UINT_MAX;
		printf("No number set, using random: %u\n", num);
	}
        unsigned char *ptr = (unsigned char *)&num;
        char *str = (char *)malloc(9);
        strcpy(str, "00000000");
	char *cmd = (char *) malloc(64 * sizeof(char));
	int arg = -0;
 	while(true) {
		ptr = (unsigned char *)&num;
inchk:
		scanf("%64s %d", cmd, &arg);
		if(strcmp(cmd, "q") == 0) {
			printf("Exiting\n");
			goto exit;
		}
		for(int i = 0; i < CMD_SZ; i++) {
			if(strcmp(commands[i], cmd) == 0) {
				printf("%s\n", commands[i]);
				cmdFns[i](&num, arg);
			}
		}
		if(!isInLUT(cmd)) {
			if(isDebug)
				printf("Command: %s\n", cmd);
			printf("Not a command\n");
			goto inchk;
		}
		
		for(int i = 0; i<sizeof(num); i++) {
                	BIN(*ptr, buffer);
        	        strcpy(str+8-strlen(buffer), buffer);
			if(isDebug) {
                		printf(
                		"i:%d str:%s buffer:%s num:%u ptr:%p\n"
                		,i,str,buffer,num,(void *)ptr-(void *)&num);
			}
                	printf("\e[41m%s\e[0m\n", str);
        	        strcpy(str, "00000000");
        	        strcpy(buffer, "00000000");
        	        ptr++;
	        }
	}
exit:
        free(str);
	free(cmd);
	return EXIT_SUCCESS;
}

void inc(unsigned *n, int arg) {
	*n = *n + 1;
}
void dec(unsigned *n, int arg) {
	*n = *n - 1;
}
void shl(unsigned *n, int arg) {
	*n = *n << 1;
}
void shr(unsigned *n, int arg) {
	*n = *n >> 1;
}
void new(unsigned *n, int arg) {
	num = arg;
}
void add(unsigned *n, int arg) {
	*n += arg;
}
void rem(unsigned *n, int arg) {
	*n -= arg;
}

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



