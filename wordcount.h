#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "table.h"

void storageFunc(table *t, char *str);

void printWords(table *t);

bool readFile(FILE *fp, char *str);

bool stringcmp(void *str1, void *str2);

//Tilagt 19/2 av Adam
//Har inte testat att kompilera dessa funktioner, se det mer som ett utkast.
FILE *openFile(char *file);

bool matchWord(regex_t *regex, char *str);

void regexCompile(regex_t *regex);

bool regexExecute(regex_t *regex, char *string);
