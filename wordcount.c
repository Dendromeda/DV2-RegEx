#include "wordcount.h"

#define WORD_LENGTH 6

int main(int argc, char **argv){
	regex_t regex;
	bool wordRead;
	size_t length = validateParams(argc, argv, &regex);
	FILE *fp = openFile(argv[1]);
	char *str = calloc(sizeof(char), 64);

	table *t = table_empty(5, *stringcmp);

	do {
		wordRead = readWord(fp, str);
		if(matchWord(&regex, str, length)) {
			storageFunc(t, str);
		}
	} while(wordRead);
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
		regexCompile(regex, "([a-z]*)([aeiouy]{2,})([a-z]*)(ly|ing)$");
	}

	if(argc == 4) {
		return atoi(argv[3]);
	} else {
		return WORD_LENGTH;
	}
}

/*Function storageFunc
Searches table for string, if present, increments the value stored.
If not, creates new string and value, and inserts into tabLength
Made for storing values matching requirements
*/
void storageFunc(table *t, char *str){
	int *val = table_lookup(t, str);
	if (val != NULL) {
		(*val)++;
		return;
	}

	val = malloc(sizeof(int));
	*val = 1;
	char *key = malloc(sizeof(char)*32);

	strcpy(key, str);
	table_insert(t,key,val);
}
/* Function printWords
Sorts table containing words and frequency.
Prints out now sorted words and frequency
*/
void printWords(table *t){
	char str[32];
	int count;

	table_sort(t);
	for (int i = 0; i < table_getSize(t); i++) {
		count = table_getEntry(t, str, i);
		printf("%s %d\n", str, count);
	}
}

/* Function readWord
Reads characters from file until it encounters a non-letter character, adding
them to string temp. When encountering non-letter character, copies string
to given string pointer
*/
bool readWord(FILE *fp, char *str){
	int i = 0;
	char *temp = calloc(sizeof(char), 64);

	char c = fgetc(fp);
	c = tolower(c);

	while((c >= 'a' && c <= 'z')){
		temp[i++] = c;
		c = fgetc(fp);
		c = tolower(c);
	}

	temp[i] = '\0';
	strcpy(str, temp);
	free(temp);

	if (c == EOF){
		return false;
	}
	return true;
}

/* Function stringcmp
Compares two string to eachother. Returns bool if identical
*/
bool stringcmp(void *p1, void *p2){
	int i = 0;
	char *str1 = p1;
	char *str2 = p2;

	while(str1[i] != 0) {
		if (str1[i] != str2[i]) {
			return 0;
		}
		i++;
	}
	if (str2[i] != 0) {
		return 0;
	}
	return 1;
}

/* Function openFile
Tries to open file, exits program if not possibilities
*/
FILE *openFile(char *file){
	FILE *fp = fopen(file, "r");
	if(fp == NULL) {
		fprintf(stderr, "Couldn't open input file %s\n", file);
		exit(2);
	}
	return fp;
}

/* Function matchWord
Tries to match given string to a regular expression, returns true if match
*/
bool matchWord(regex_t *regex, char *str, size_t length){
	if (regexExecute(regex, str)) {
		if (strlen(str) == length) {
			return true;
		}
	}
	return false;
}

/* Function regexCompile
Tries to compile given regular expression, exits program if not able
*/
void regexCompile(regex_t *regex, char *strRegex){
	int result = 0;

	result = regcomp(regex, strRegex,  REG_ICASE|REG_EXTENDED);
	if(result) {
		fprintf(stderr, "Couldn't compile regex \n");
		exit(3);
	}
}
/* Function regexExecute
Checks string against given regular exression, returns true if match
*/
bool regexExecute(regex_t *regex, char *string){
	int result;

	result = regexec(regex, string, 0, NULL, 0);
	if(!result) {
		return true;
	} else {
		return false;
	}
}

/* Function usageText
Prints program argument syntax
*/
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
