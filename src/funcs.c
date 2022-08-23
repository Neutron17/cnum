#include "funcs.h"
#include "stdext.h"
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define CONF_SZ 2
bool configs[CONF_SZ] = {
		false, // grid print
		false
};

const CmdFn cmdFns[CMD_SZ] = {
		inc, dcr,
		shl, shr,
		new, new,
		add, rem,
		print, print, print, print,
		conf,
		dec, hex, bin, oct,
		rnd, rnd, rnd, rnd
};
const char *commands[CMD_SZ] = {
		"inc", "dcr",	// increment, decrement
		"shl", "shr",	// shift left/right
		"set", "new",	// sets current number
		"add", "rem",	// add rem %n%
		"prt", "p", "prnt", "print", // print
		"conf",
		"dec", "hex", "bin", "oct",
		"rand", "r", "rnd", "random"
};
const bool takesArg[CMD_SZ] = {
		false, false,	// inc dec
		true,  true,	// shl shr
		true,  true,	// set new
		true,  true,	// add rem
		false, false, false, false, // print
		false,
		false, false, false, false
};
const unsigned char CountingSys[4] = {
		10, 16, 2, 8
};

extern bool isDebug;
enum PrintEnum lastmode = P_DEC;

void inc(unsigned *n, int arg) { *n = *n + 1; }
void dcr(unsigned *n, int arg) { *n = *n - 1; }
void shl(unsigned *n, int arg) { *n = *n << arg; }
void shr(unsigned *n, int arg) { *n = *n >> arg; }
void new(unsigned *n, int arg) { *n = arg; }
void add(unsigned *n, int arg) { *n += arg; }
void rem(unsigned *n, int arg) { *n -= arg; }
#include <stdlib.h>
void print(unsigned *n, int arg) {
	if(configs[0]) { // Grid
		char buff[9] = "00000000\0";
		char  str[9] = "00000000\0";
		unsigned char *ptr = (unsigned char *) n;

		for (int i = 0; i < sizeof(*n); i++) {
			switch (arg) {
				case P_DEC:
					strcpy(str, "000");
					strcpy(buff, "000");
					//size = 3; // 255
					DEC(*ptr, buff);
					break;
				case P_HEX:
					//strcpy(foo, "  ");
					strcpy(str, "00");
					strcpy(buff, "00");
					//size = 2; // ff
					HEX(*ptr, buff);
					break;
				case P_BIN: // default
					//size = 8; // 11111111
					BIN(*ptr, buff);
					break;
				case P_OCT:
					strcpy(str, "0000");
					strcpy(buff, "0000");
					//size = 4; // 1103
					OCT(*ptr, buff);
					break;
				default:;
			}
			strcpy(str + strlen(str) - strlen(buff), buff);
			if (isDebug) {
				printf(
						"i:%d str:%s buff:%s num:%u\n" /*"ptr:%p\n"*/
						, i, str, buff, *n/*,(void *)ptr-(void *)n*/);
			}
			printf(/*"\e[41m"*/"%s"/*"\e[0m*/"\n", str);
			ptr++;
		}
	} else { // one line
		char buff[36] = "00000000 00000000 00000000 00000000\0";
		char  str[36] = "00000000 00000000 00000000 00000000\0";
		switch (arg) {
			case P_DEC:
dec:
				strcpy(str, "000000000000");
				strcpy(buff, "000000000000");
				//size = 3; // 255
				DEC(*n, buff);
				break;
			case P_HEX:
				//strcpy(foo, "  ");
				strcpy(str, "00000000");
				strcpy(buff, "00000000");
				//size = 2; // ff

				HEX(*n, buff);
				break;
			case P_BIN: // default
				//size = 8; // 11111111
				BIN(*n, buff);
				break;
			case P_OCT:
				strcpy(str, "0000000000000000");
				strcpy(buff, "0000000000000000");
				//size = 4; // 1103
				OCT(*n, buff);
				break;
			default:
				goto dec;
				break;
		}
		//printf("str %s buff %s n %d\n", str, buff, *n);
		strcpy(str + strlen(str) - strlen(buff), buff);
		printf("%s\n", str);
	}
}
void conf(unsigned *n, int arg) {
	printf("Print: \n"
		   "\t1 grid print: %c\n"
		   "\t2 is debug: %c\n"
		   , configs[0] ? 'X' : 'O', configs[1] ? 'X' : 'O'
	);
	printf("Flip: ");
	int opt = 0;
	scanf("%d", &opt);
	if(opt < 1 || opt > CONF_SZ)
		return;
	configs[opt-1] = !configs[opt-1];
}

void dec(unsigned *n, int arg) { print(n, P_DEC); }
void hex(unsigned *n, int arg) { print(n, P_HEX); }
void bin(unsigned *n, int arg) { print(n, P_BIN); }
void oct(unsigned *n, int arg) { print(n, P_OCT); }

void rnd(unsigned int *n, int arg) { *n = rand() % UINT_MAX; }

