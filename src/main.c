#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>	// true, false
#include <string.h>	// strcpy
#include <limits.h>	// UINT_MAX	(main) {rand}
#include <time.h>	// rand		(main)
#include <getopt.h>	// getopt	(parseArgs)
#include "funcs.h"

#define VERSION 1.22

bool isDebug = false;
bool useLast = true;
bool useArg  = false;
u_int8_t countingsys = 10;
char numStr[7];

void parseArgs(int argc, char *argv[]);
bool isInLUT(const char *command);

int main(int argc, char *argv[]) {
	srand(time(NULL));	// seed
	parseArgs(argc, argv);	// depend: isDebug, useLast, numStr
	if(useLast)
		strcpy(numStr, argv[argc-1]);
	unsigned num = strtol(numStr, NULL, 10);
	if(num == 0 || errno == EINVAL || errno == ERANGE) { // conv fail
		num = rand() % UINT_MAX;
		printf("No number set, using random: %u\n", num);
	}
	char *cmd = (char *) malloc(6 * sizeof(char));
	int arg = -0;
 	while(true) {
inchk:
		useArg = false;
		printf("> ");
		// TODO: handle error
		scanf("%6s", cmd);
		if(*cmd == 'q' || *cmd == 'Q') {
			printf("Exiting\n");
			goto exit;
		}
		bool found = false;
		for(int i = 0; i < CMD_SZ; i++) {
			if(isDebug)
				printf("Checking: %s\n", commands[i]);
			if(strncasecmp(commands[i], cmd, 7) == 0) {
				found = true;
				if (takesArg[i]) {
arg:
					printf("Arg: ");
					char strarg[16];
					//fgets(strarg, 16, stdout);
					scanf("%15s", strarg);
					arg = strtol(strarg, NULL, countingsys);
					if(errno == EINVAL || errno == ERANGE) {
						fprintf(stderr, "Couldn't convert to number\n");
						goto arg;
					}
					useArg = true;
				}
				if (isDebug)
					printf("%s\n", commands[i]);
				cmdFns[i](&num, arg);
				break;
			}
		}
		if(!found) {
			if(isDebug)
				printf("Command: %s\n", cmd);
			printf("Not a command\n");
			goto inchk;
		}
	}
exit:
	free(cmd);
	return EXIT_SUCCESS;
}

// TODO faster search algorithm
bool isInLUT(const char *command) {
	for(int i = 0; i < CMD_SZ; i++) {
		if(strncasecmp(commands[i], command, 6) == 0)
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
