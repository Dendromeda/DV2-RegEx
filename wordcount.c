/*
DV2: Algoritmer och problemlösning.
File: wordcount.c
Name: Adam Lindgren & Jakob Lundin.
CS-user: dv17aln & c14jln
Date: 23 Februari 2018
Description: Goes through a given textfile and prints the words that matches
			 the given regular expression or the default one. Also fulfills the
			 given word length or the default one.
Required input: A filepath.
Optional input: A regular expression and an integer for the word length.
Output: Words and their frequency printed to the terminal.
Limitations: If used with languages that have words longer than 32 characters.
*/

#include "wordcount.h"

int main(int argc, char **argv){
	regex_t regex;
	bool lastWord;
	size_t length = validateParams(argc, argv, &regex);
	FILE *fp = openFile(argv[1]);
	char *str = calloc(sizeof(char), STRING_LENGTH);

	table *t = table_empty(5, *stringcmp);

	do {
		//If readWord returns true, it's the end of the file.
		lastWord = readWord(fp, str);
		if(matchWord(&regex, str, length)) {
			storageFunc(t, str);
		}
	} while(!lastWord);
	printWords(t);

	fclose(fp);
	regfree(&regex);
	table_kill(t);
	free(str);

	return 0;
}

int validateParams(int argc, char **argv, regex_t *regex){
	if(argc < 2 || argc > 4) {
		usageText();
	}

	if(argc >= 3) {
		regexCompile(regex, argv[2]);
	} else {
		//This is the default regular expression.
		regexCompile(regex, "([a-z]*)([aeiouy]{2,})([a-z]*)(ly|ing)$");
	}

	if(argc == 4) {
		return atoi(argv[3]);
	} else {
		return WORD_LENGTH;
	}
}


void storageFunc(table *t, char *str){
	int *val = table_lookup(t, str);
	//If word is present, increment frequency.
	if (val != NULL) {
		(*val)++;
		return;
	}

	//Otherwise, add it to table.
	val = malloc(sizeof(int));
	*val = 1;
	char *key = malloc(sizeof(char)*STRING_LENGTH);

	strcpy(key, str);
	table_insert(t,key,val);
}


void printWords(table *t){
	char str[STRING_LENGTH];
	int frequency;

	table_sort(t);
	for (int i = 0; i < table_getSize(t); i++) {
		frequency = table_getEntry(t, str, i);
		printf("%s %d\n", str, frequency);
	}
}


bool readWord(FILE *fp, char *str){
	int i = 0;
	char *temp = calloc(sizeof(char), STRING_LENGTH);

	char c = fgetc(fp);
	c = tolower(c);

	//Reads a character until it encounters a non-letter character.
	while(c >= 'a' && c <= 'z') {
		temp[i++] = c;
		c = fgetc(fp);
		c = tolower(c);
	}

	temp[i] = '\0';
	strcpy(str, temp);
	free(temp);

	if (c != EOF) {
		return false;
	} else {
		return true;
	}
}


bool stringcmp(void *p1, void *p2){
	int i = 0;
	char *str1 = p1;
	char *str2 = p2;

	while(str1[i] != 0) {
		if (str1[i] != str2[i]) {
			return false;
		}
		i++;
	}

	if (str2[i] != 0) {
		return false;
	} else {
		return true;
	}
}


FILE *openFile(char *file){
	FILE *fp = fopen(file, "r");

	if(fp == NULL) {
		fprintf(stderr, "Couldn't open input file %s\n", file);
		exit(2);
	}

	return fp;
}


bool matchWord(regex_t *regex, char *str, size_t length){
	if (regexExecute(regex, str)) {
		if (strlen(str) == length) {
			return true;
		}
	}

	return false;
}


void regexCompile(regex_t *regex, char *strRegex){
	int result = 0;

	//regcomp returns anything except 0 when it fails to compile.
	result = regcomp(regex, strRegex,  REG_ICASE|REG_EXTENDED);
	if(result) {
		fprintf(stderr, "Couldn't compile regex \n");
		exit(3);
	}
}


bool regexExecute(regex_t *regex, char *string){
	int result = 0;

	//regexec returns 0 when it's a match, otherwise something else.
	result = regexec(regex, string, 0, NULL, 0);

	if(!result) {
		return true;
	} else {
		return false;
	}
}


void usageText(void){
    printf("\nUSAGE:\n");
    printf("wordcount [FILE] [REGEX] [WORDLENGTH]\n\n");
	printf("Options:\n");
	printf("Regex input is optional. If no regex is given ");
	printf("the default regex will be used.\n");
	printf("Wordlength input is optional. If no length is given ");
	printf("the default length will be used.\n\n");
	exit(1);
}
