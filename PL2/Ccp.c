/*
Ccp.c - Benjamin Malz
Description: This program copies the contents of one file into another file.
Input: The input file is any input file, although only text will correctly copy.
Output: There is no output text displayed in the terminal, however the specified filename will contain the copied text from the input file.
*/
#include <stdio.h>
#include <stdlib.h>

void xerox(char* infile, char* outfile){ /* This function reads each line of the input file and copies its contents to the output file. Its first parameter is the input file, and its second is the desired output file. */
	FILE* reader;
	FILE* writer;
	char line[100000]; /*don't have longer lines than this please*/
	reader = fopen(infile, "r");
	if (reader){
		writer = fopen(outfile, "w");
		while (fgets(line, 100000, reader)){
			fprintf(writer, "%s", line);
		}
		fclose(reader);
	}
	else{
		printf("Ccp: File %s does not exist\n", infile);
	}
}

int main(int argc, char** argv){ /* Check if arguments are valid*/
	if (argc > 3){
		printf("Ccp: Too many arguments\n");
	}
	else if(argc < 3){
		printf("Ccp: Too few arguments\n");
	}
	else{
		xerox(argv[1], argv[2]);
	}
	return 0;
}