/*
Caverage.c - Benjamin Malz
Description: This program calculates the floating point average from a list of integers given in an input file, and displays the floating point average in the terminal.
Input: The input file must be a file that contains only numbers, separated by newlines. The input file can be empty, which prompts an error message.
Output: The output will be displayed in the terminal. The output will either be the floating point average, rounded to two decimal places, or an error message.
*/

#include <stdio.h>
#include <stdlib.h>

void calculator(char* filename){ /* This function checks if the given file is valid. If it is, the function reads each number and adds it to a total, then divides by the amount of numbers given. Its sole parameter is the filename.*/
	FILE* reader;
	float total = 0;
	float counter = 0;
	int holder;
	reader = fopen(filename, "r");
	if (reader){
		while (fscanf(reader, "%d", &holder) != EOF){
			total += holder;
			counter++;
		}
	if(counter == 0){
		printf("Caverage: Empty file\n");
	}
	else{
		float average = total/counter;
		printf("%.2f\n", average);
	}
	fclose(reader);
	}
	else{
		printf("Caverage: File %s does not exist\n", filename);
	}

}

int main(int argc, char** argv){ /* Checks if the arguments from the command line are valid. If they are, calls the calculator function. */
	if (argc > 2){
		printf("Caverage: Too many arguments\n");
	}
	else if(argc < 2){
		printf("Caverage: Too few arguments\n");
	}
	else{
		calculator(argv[1]);
	}
	return 0;
}