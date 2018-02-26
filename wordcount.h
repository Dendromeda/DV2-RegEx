#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include "table.h"

int validateParams(int argc, char **argv, regex_t *regex);

void storageFunc(table *t, char *str);

void printWords(table *t);

bool readWord(FILE *fp, char *str);

bool stringcmp(void *str1, void *str2);

FILE *openFile(char *file);

bool matchWord(regex_t *regex, char *str, size_t length);

void regexCompile(regex_t *regex, char *strRegex);

bool regexExecute(regex_t *regex, char *string);

void usageText(void);
