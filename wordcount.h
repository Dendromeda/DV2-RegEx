/*
DV2: Algoritmer och problemlösning.
File: wordcount.h
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include "table.h"

//Change this defined constant if expecting words longer than 32 characters.
#define STRING_LENGTH 32
#define WORD_LENGTH 6


/* Function:	validateParams
 * Description: Validates the inparameters for the program. If no filepaths
 				are given, the program prints the usage text and exits the
				program. If none of the optional parameters are present,
				it uses the default values.
 * Input:		An integer with the amount of parameters, a string array with
 				the parameters given and a regex pointer.
 * Output:		An integer.
 */
int validateParams(int argc, char **argv, regex_t *regex);


/* Function:    storageFunc
 * Description:	Searces table for string, if present increments the value
 				stored. If not, creates a new string and value, and inserts
				into table.
 * Input:		A table and a string.
 * Output:		None.
 */
void storageFunc(table *t, char *str);


/* Function:    printWords
 * Description:	Sorts table containing word-pairs according to frequency,
 				then prints the sorted words and their frequency
 * Input:		A table.
 * Output:		None.
 */
void printWords(table *t);


/* Function:	readWord
 * Description:	Reads characters from file until it encounters a
 				non-letter character, adding them to a temporary string.
				When encountering a non-letter character, it copies the
				temporary string to the given string. Returns true when it
				encounters end of file (EOF).
 * Input:		A file pointer and a string.
 * Output:		Boolean.
 */
bool readWord(FILE *fp, char *str);


/* Function:	stringcmp
 * Description:	Compares to strings, returns true if identical.
 * Input:		Two strings.
 * Output:		Boolean.
 */
bool stringcmp(void *str1, void *str2);


/* Function:	openFile
 * Description:	Opens a file, if not possible it exits the program and gives
 				an error message.
 * Input:		A string with the filepath.
 * Output:		File pointer.
 */
FILE *openFile(char *file);


/* Function:	matchWord
 * Description:	Tries to match given string to a regular expression, returns
 				true if it matches.
 * Input:		A regex pointer, string and an integer with the desired length.
 * Output:		Boolean.
 */
bool matchWord(regex_t *regex, char *str, size_t length);


/* Function:	regexCompile
 * Description:	Compiles the given regular expression, if not possible it
 				exits the program and gives an error message.
 * Input:		A regex pointer and string with the desired regular expression.
 * Output:		None.
 */
void regexCompile(regex_t *regex, char *strRegex);


/* Function:	regexExecute
 * Description:	Matches the string against the given regular expression,
  				returns true if it matches.
 * Input:		A regex pointer and a string.
 * Output:		Boolean.
 */
bool regexExecute(regex_t *regex, char *string);


/* Function:	usageText
 * Description:	Prints the program argument syntax and exits the program.
 * Input:		None.
 * Output:		None.
 */
void usageText(void);
