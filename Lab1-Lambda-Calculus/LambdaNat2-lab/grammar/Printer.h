#ifndef PRINTER_HEADER
#define PRINTER_HEADER

#include "Absyn.h"

/* Certain applications may improve performance by changing the buffer size */
#define BUFFER_INITIAL 2048
/* You may wish to change _L_PAREN or _R_PAREN */
#define _L_PAREN '('
#define _R_PAREN ')'

/* The following are simple heuristics for rendering terminals */
/* You may wish to change them */
void renderCC(Char c);
void renderCS(String s);
void indent(void);
void backup(void);


char *printProgram(Program p);
char *printListExp(ListExp p);
char *printExp(Exp p);

void ppProgram(Program p, int i);
void ppListExp(ListExp p, int i);
void ppExp(Exp p, int i);

char *showProgram(Program p);
char *showListExp(ListExp p);
char *showExp(Exp p);

void shProgram(Program p);
void shListExp(ListExp p);
void shExp(Exp p);

void ppId(String s, int i);
void shId(String s);
void ppInteger(Integer n, int i);
void ppDouble(Double d, int i);
void ppChar(Char c, int i);
void ppString(String s, int i);
void ppIdent(String s, int i);
void shInteger(Integer n);
void shDouble(Double d);
void shChar(Char c);
void shString(String s);
void shIdent(String s);
void bufAppendS(const char *s);
void bufAppendC(const char c);
void bufReset(void);
void resizeBuffer(void);

#endif

