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

/* dps: depends */

typedef void (*CmdFn)(unsigned*);

#define BIN(NUM, DEST) itoa(NUM, DEST, 2)
#define OCT(NUM, DEST) itoa(NUM, DEST, 6)
#define DEC(NUM, DEST) itoa(NUM, DEST, 10)
#define HEX(NUM, DEST) itoa(NUM, DEST, 16)

#define VERSION 1.0
#define CMD_SZ  4

bool isDebug = false;
bool useLast = true;
//bool running = true;
char numStr[7];
const char *commands[CMD_SZ] = {
	"inc",
	"dec",
	"shl",
	"shr"
};
void parseArgs(int argc, char *argv[]);
bool isInLUT(const char *command);

void inc(unsigned *n);
void dec(unsigned *n);
void shl(unsigned *n);
void shr(unsigned *n);

CmdFn cmdFns[CMD_SZ] = {
	inc,
	dec,
	shl,
	shr
};

int main(int argc, char *argv[]) {
	srand(time(NULL));	// seed
	parseArgs(argc, argv);	// dps: isDebug, useLast, numStr 
        char buffer[9];
        unsigned x;
	if(useLast)
		strcpy(numStr, argv[argc-1]);
	x = atoi(numStr);
	if(x == 0) { // atoi failed
		x = rand() % UINT_MAX;
		printf("No number set, using random: %u\n", x);
	}
        unsigned char *ptr = (unsigned char *)&x;
        char *str = (char *)malloc(9);
        strcpy(str, "00000000");
	char *cmd = (char *) malloc(64 * sizeof(char));
 	while(true) {
		ptr = (unsigned char *)&x;
inchk:
		scanf("%64s", cmd);
		if(strcmp(cmd, "q") == 0) {
			printf("Exiting\n");
			goto exit;
		}
		if(!isInLUT(cmd)) {
			printf("Not a command\n");
			goto inchk;
		}
		
		for(int i = 0; i<sizeof(x); i++) {
                	BIN(*ptr, buffer);
        	        strcpy(str+8-strlen(buffer), buffer);
			if(isDebug) {
                		printf(
                		"i:%d str:%s buffer:%s x:%u ptr:%p\n"
                		,i,str,buffer,x,(void *)ptr-(void *)&x);
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

void inc(unsigned *n) {
	*n = *n + 1;
}
void dec(unsigned *n) {
	*n = *n - 1;
}
void shl(unsigned *n) {
	*n = *n << 1;
}
void shr(unsigned *n) {
	*n = *n >> 1;
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



