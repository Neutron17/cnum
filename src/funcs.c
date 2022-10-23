#include "funcs.h"
#include "stdext.h"
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#define CONF_SZ 2
bool configs[CONF_SZ] = {
		true, // grid print
		false
};
// 0-8: arg
const CmdFn cmdFns[CMD_SZ] = {
		shl, shr,
		divid, mod,
		new, new,
		add, rem, rem,
		inc, dcr,
		print, print, print, print,
		conf,
		dec, hex, bin, oct,
		rnd, rnd, rnd, rnd,
		half,
};
const char *commands[CMD_SZ] = {
		"shl", "shr", 			// shift left/right
		"div", "mod", 			// divide, modulo
		"set", "new", 			// sets current number
		"add", "rem", "sub",		// add rem %n%
		"inc", "dcr",			// increment, decrement
		"prt", "p", "prnt", "print", 	// print
		"conf",
		"dec", "hex", "bin", "oct",
		"rand", "r", "rnd", "random",
		"half"

};
const unsigned char CountingSys[4] = {
		10, 16, 2, 8
};
const char *restrict const zeros_ml[] = {
	"000", "00",
	"00000000",
	"0000"
};
const char *restrict const zeros_ol[] = {
	"000000000000",
	"00000000",
	"00000000 00000000 00000000 00000000",
	"0000000000000000"
};

extern bool isDebug;
enum PrintEnum lastmode = P_DEC;
// simple relative command
#define DEFINE_SRCMD(NAME, OP) 			\
	void NAME(unsigned *n, int arg) { 	\
		*n = *n OP; 			\
	}
// simple command
#define DEFINE_SCMD(NAME, OP) 			\
	void NAME(unsigned *n, int arg) { 	\
		*n = OP; 			\
	}

DEFINE_SRCMD(inc, +1);
DEFINE_SRCMD(dcr, -1);
DEFINE_SRCMD(shl, << arg);
DEFINE_SRCMD(shr, >> arg);
DEFINE_SRCMD(divid, / arg);
DEFINE_SRCMD(mod, % arg);

DEFINE_SCMD(new, (unsigned)arg);

DEFINE_SRCMD(add, +arg);
DEFINE_SRCMD(rem, -arg);
DEFINE_SRCMD(half, / 2);

#include <stdlib.h>
DEFINE_SCMD(rnd, rand() % UINT_MAX);

void print(unsigned *n, int arg) {
	if(configs[0]) { // Grid
		char buff[9];
		char  str[9];
		unsigned char *ptr = (unsigned char *) n;
		strcpy(str, zeros_ml[arg]);
		strcpy(buff, zeros_ml[arg]);

		for (int i = 0; i < sizeof(*n); i++) {
			switch (arg) {
				case P_DEC:
					DEC(*ptr, buff);
					break;
				case P_HEX:
					HEX(*ptr, buff);
					break;
				default:
				case P_BIN: // default
					BIN(*ptr, buff);
					break;
				case P_OCT:
					OCT(*ptr, buff);
					break;
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
		char buff[36];
		char  str[36];
		strcpy(str, zeros_ol[arg]);
		strcpy(buff, zeros_ol[arg]);
		switch (arg) {
			case P_DEC:
dec:
				DEC(*n, buff);
				break;
			case P_HEX:
				HEX(*n, buff);
				break;
			case P_BIN: // default
				BIN(*n, buff);
				break;
			case P_OCT:
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

