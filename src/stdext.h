#ifndef _NTR_STDEXT_H_
#define _NTR_STDEXT_H_ 1

#define BIN(NUM, DEST) itoa(NUM, DEST, 2)
#define OCT(NUM, DEST) itoa(NUM, DEST, 6)
#define DEC(NUM, DEST) itoa(NUM, DEST, 10)
#define HEX(NUM, DEST) itoa(NUM, DEST, 16)

void strreverse(char* begin, char* end);
void itoa(int value, char* str, int base);

#endif
