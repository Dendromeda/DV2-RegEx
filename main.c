#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "table.h"




void storageFunc(table *t, char *str);

void printWords(table *t);

bool readFile(FILE *fp, char *str);

bool stringcmp(void *str1, void *str2);


FILE *openFile(char *file)

void regexCompile(regex_t *regex);

bool regexExecute(regex_t *regex, char *string);



int main(int argc, char **argv){
	table *t = table_empty(10, *stringcmp, NULL);
	char *str = "heeeeej";
	storageFunc(t, str);
	storageFunc(t, str);
	str = "tjena";
	storageFunc(t, str);
	printWords(t);
	system("pause");
}

void storageFunc(table *t, char *str){
	int *val = table_lookup(t, str);
	if (val != NULL){
		(*val)++;
		return;
	}
	val = malloc(sizeof(int));
	*val = 1;
	char *key = malloc(sizeof(char)*7);
	strcpy(key, str);
	table_insert(t,key,val);
}

void printWords(table *t){
	cell c;
	int *v;
	char *str;
	table_sort(t);
	for (int i = 0; i < t->size; i++){
		c = t->arr[i];
		v = c.val;
		str = c.key;
		fprintf(stdout, "%s %d\n", str, *v);
	}
}

bool readFile(FILE *fp, char *str){
	if (fscanf(fp, "%s", str))
		return 1;
	else
		return 0;
}

bool stringcmp(void *p1, void *p2){
	int i = 0;
	char *str1 = p1;
	char *str2 = p2;

	while(str1[i] != 0){
		if (str1[i] != str2[i]){
			return 0;
		}
		i++;
	}
	if (str2[i] != 0){
		return 0;
	}
	return 1;
}


//Det är dessa funktioner som är otestade.
FILE *openFile(char *file) {
	FILE *fp = fopen(file, r);
	if(fp == NULL) {
		fprintf(stderr, "Couldn't open input file %s\n", file);
		return NULL;
	}
	return fp;
}

void regexCompile(regex_t *regex) {
	int result = 0;
	result = regcomp(regex, "(?=\\b\\w{6}\\b)(\\w*?)([aeiouy]{2,})(\\w*?)(ly|ing)\\b",  REG_ICASE);
	if(result) {
		//Eftersom ingen kompilering har gjorts ligger denna printsats här utifall att det inte går att kompilera regex-uttrycket.
		fprintf(stderr, "Couldn't compile regex \n");
	}
}

bool regexExecute(regex_t *regex, char *string) {
	int result = 0;
	result = regexec(regex, string, 0, NULL, 0);
	if(!result) {
		return true;
	}
	else {
		return false;
	}
}
