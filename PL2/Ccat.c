/*
Ccat.c - Benjamin Malz
Description: This program displays the contents of a file with optional numbered lines.
Input: The input file is any valid text file.
Output: The output will be the contents of the file, optionally with numbers on every line or only non-empty lines.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printer(char* infile, int option){ /* This function prints the lines of the given input file. The parameters are the filename and an integer representing which option was chosen in the command line, if any. The option determines the numbering of the lines. */
	FILE* reader;
	char line[100000]; /*don't have longer lines than this please*/
	int counter = 1;
	reader = fopen(infile, "r");
	if (reader){
		if (option == 0){
			while (fgets(line, 100000, reader)){
				printf("%s", line);
			}
		}
		else if (option == 1){
			while (fgets(line, 100000, reader)){
				printf("% 6d  %s",counter, line);
				counter++;
			}
		}
		else if (option == 2){
			while (fgets(line, 100000, reader)){
				if (strcmp(line, "\n") == 0){
					printf("%s", line);
				}
				else{
					printf("% 6d  %s",counter, line);
					counter++;
				}
			}
		}
		fclose(reader);
	}
	else{
		printf("Ccat: File %s does not exist\n", infile);
	}
}

int main(int argc, char** argv){ /* Checks the command line arguments, sends the corresponding integer to the function based on command line option */
	if (argc > 3){
		printf("Ccat: Too many arguments\n");
		return 0;
	}
	else if(argc < 2){
		printf("Ccat: Too few arguments\n");
		return 0;
	}
	else if(argc == 2 && (strcmp(argv[1], "-n") == 0 || strcmp(argv[1], "-b") == 0)){
		printf("Ccat: No filename specified\n");
	}
	else{
		if (argc == 2){
			printer(argv[1], 0);
		}
		else{
			if (strcmp(argv[1], "-n") == 0){
				printer(argv[2], 1);
			}
			else if (strcmp(argv[1], "-b") == 0){
				printer(argv[2], 2);
			}
			else{
				printf("Ccat: %s is not a valid option\n", argv[1]);
			}
		}
	}
	return 0;
}