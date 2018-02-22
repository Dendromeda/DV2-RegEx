#include "wordcount.h"

/*
int main(int argc, char **argv){
	table *t = table_empty(10, *stringcmp, NULL);
	char *str = "heeeeej";
	storageFunc(t, str);
	str = "fairly";
	storageFunc(t, str);
	storageFunc(t, str);
	printWords(t);

	regex_t regex;
	regexCompile(&regex);
	if(regexExecute(&regex, str)) {
		printf("its ok\n");
	}
	//system("pause");
	return 0;
} */

void main(int argc, char **argv){
	FILE *fp = openFile(argv[1]);
	char *str[32];
	regex_t regex;
	regexCompile(&regex, "([a-z])([aeiouy]{2,})([a-z]*)(ly|ing)$");
	table *t = table_empty(5, *stringcmp, NULL);

	while(readWord(fp, str)){
		formatWord(str);
		if(matchWord(&regex, str)){
			storageFunc(t, str);
		}
	}
	printWords(t);
	table_kill(t);
}

void storageFunc(table *t, char *str){
	int *val = table_lookup(t, str);
	if (val != NULL){
		(*val)++;
		return;
	}
	val = malloc(sizeof(int));
	*val = 1;
	char *key = malloc(sizeof(char)*32);

	strcpy(key, str);
	table_insert(t,key,val);
}

void printWords(table *t){
	char str[32];
	int count;
	table_sort(t);
	for (int i = 0; i < table_getSize(t); i++){
		count = table_getEntry(t, str, i);
		printf("%s %d\n", str, count);

	}
}

bool readWord(FILE *fp, char *str){
	if(fscanf(fp, "%s", str) != EOF)
		return true;
	else
		return false;
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



FILE *openFile(char *file){
	FILE *fp = fopen(file, "r");
	if(fp == NULL) {
		fprintf(stderr, "Couldn't open input file %s\n", file);
		exit(0);
	}
	return fp;
}


bool matchWord(regex_t *regex, char *str){
	if (regexExecute(regex, str)){
		/*if (strlen(str) == 6){
			return true;
		}*/
		return true;
	}
	return false;
}
/* Teckenkoll funkar ej. Klarar ej av "'Really"
 *
 */
void formatWord(char *str){
	regex_t regex;
	regexCompile(&regex, "[a-z]");
	/*for (int i = 0; str[i]; i++){

		//if (str[i] < 97 && str[i] > 122){
		if(!regexExecute(&regex, &str[i])) {
			//for (int j = i; str[j]; j++){
			//printf("hej hopp\n");
			int j = i;
			while(str[j]) {
				//printf("%c", str[j]);
				str[j] = str[j+1];
				//printf(" %c\n", str[j]);
				j++;
			}
		}
		str[i] = tolower(str[i]);
	}*/
	int i = 0;
	int j = 0;

	char *temp[32];
	while(str[i]) {
		str[i] = tolower(str[i]);
		if(str[i] < 97 || str[i] > 122) {
		//if(!regexExecute(&regex, &str[i])) {
			i++;
		} else {
			temp [j] = str[i];
			i++;
			j++;
		}
	}
	printf("%s", temp);
	strcpy(str, temp);
}


void regexCompile(regex_t *regex, char *strRegex){
	int result = 0;
	result = regcomp(regex, strRegex,  REG_ICASE|REG_EXTENDED);
	if(result) {
		fprintf(stderr, "Couldn't compile regex \n");
		exit(0);
	}
}

bool regexExecute(regex_t *regex, char *string){
	int result;
	result = regexec(regex, string, 0, NULL, 0);
	if(!result) {
		return true;
	}
	else {
		return false;
	}
}
