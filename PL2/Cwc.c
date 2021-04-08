/*
Cwc.c - Benjamin Malz
Description: This program counts the number of lines, words and characters (bytes) in a given text file.
Input: The input file is any valid text file.
Output: The output is the number of lines, the number of words, the number of characters, and the filename.
*/
#include <stdio.h>
#include <stdlib.h>

void counter(char* infile){ /* This function counts how many lines, words and characters are in the given file. Its only parameter is the filename. */
	FILE* reader;
	int linecount = 0;
	int wordcount = 0;
	int bytecount = 0;
	char curChar, prevChar;
	reader = fopen(infile, "r");
	if (reader){
		while (curChar != EOF){
			prevChar = curChar;
			curChar = fgetc(reader);
			if (curChar == ' ' && prevChar != ' ' && prevChar != '\n'){
				wordcount++;
			}
			else if (curChar == '\n'){
				linecount++;
				if (prevChar != '\n' && prevChar != ' '){
					wordcount++;
				}
			}
			if (curChar != EOF){
				bytecount++;
			}
			else{
				wordcount++;
			}
		}
		fclose(reader);
		printf(" %d %d %d %s\n", linecount, wordcount, bytecount, infile);
	}
	else{
		printf("Cwc: File %s does not exist\n", infile);
	}
}

int main(int argc, char** argv){ /* Handles command line arguments */
	if (argc > 2){
		printf("Cwc: Too many arguments\n");
		return 0;
	}
	else if(argc < 2){
		printf("Cwc: Too few arguments\n");
		return 0;
	}
	else{
		counter(argv[1]);
		return 0;
	}
}