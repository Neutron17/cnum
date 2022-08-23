#ifndef _NTR_FUNCS_H_
#define _NTR_FUNCS_H_ 1

#include <stdbool.h>

#define CMD_SZ 21

void inc(unsigned *n, int arg);
void dcr(unsigned *n, int arg);
void shl(unsigned *n, int arg);
void shr(unsigned *n, int arg);
void new(unsigned *n, int arg);
void add(unsigned *n, int arg);
void rem(unsigned *n, int arg);
void print(unsigned *n, int arg);
void conf(unsigned *n, int arg);

void dec(unsigned *n, int arg);
void hex(unsigned *n, int arg);
void bin(unsigned *n, int arg);
void oct(unsigned *n, int arg);

void rnd(unsigned *n, int arg);

typedef void (*CmdFn)(unsigned*, int);
const extern CmdFn cmdFns[CMD_SZ];

const extern char *commands[CMD_SZ];
const extern bool takesArg[CMD_SZ];

enum CmdEnum {
	E_INC, E_DCR,
	E_SHL, E_SHR,
	E_SET, E_NEW,
	E_ADD, E_REM,
	E_PRT, E_P, E_PRNT, E_PRINT,
	E_DEC, E_HEX, E_BIN, E_OCT,
	E_RAND, E_R, E_RND, E_RANDOM
};

enum PrintEnum { P_DEC = 0, P_HEX, P_BIN, P_OCT };
const extern unsigned char CountingSys[4];

#endif //_NTR_FUNCS_H_
