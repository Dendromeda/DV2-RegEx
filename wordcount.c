#include "wordcount.h"

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
FILE *openFile(char *file){
	FILE *fp = fopen(file, "r");
	if(fp == NULL) {
		fprintf(stderr, "Couldn't open input file %s\n", file);
		return NULL;
	}
	return fp;
}

void regexCompile(regex_t *regex){
	int result = 0;
	result = regcomp(regex, "([a-z]*)([aeiouy]{2,})([a-z]*)(ly|ing)$",  REG_ICASE|REG_EXTENDED);
	if(result) {
		fprintf(stderr, "Couldn't compile regex \n");
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
	/*bool result;
		result = regexec(regex, string, 0, NULL, 0);
		return result;
	*/
}
