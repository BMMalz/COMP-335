#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int intCompare(const void* intOne, const void* intTwo){ /* Compares two values, returns a positive if the first value is larger, a zero if the values are equal, and a negative if the second value is larger. For use with qsort, as a void pointer it takes any types of data, although in this program it will only ever use floats, and ensures that the given data is cast to a float. */
	if (*(float*)intOne > *(float*)intTwo ) {
		return 1;
	}
  	else if (*(float*)intOne == *(float*)intTwo) {
  		return 0;
  	}
 	else if (*(float*)intOne < *(float*) intTwo ){
 		return -1;
 	}
}

int stringCompare(const void* stringOne, const void* stringTwo){ /* Compares two strings, although it takes any type of data, it will only work with strings since it uses strcmp. For use with qsort. */
	return strcmp(*(char**)stringOne, *(char**)stringTwo);
}

void intSort(char* infile, int option){ /* Sorts a file of numbers. Its parameters are the filename and an integer corresponding to a command line option. */
	FILE* reader;
	float entry; 
	int entries = 0;
	int i = 0;
	reader = fopen(infile, "r");
	if (reader){
		while (fscanf(reader, "%f", &entry) != EOF){
			entries++;
		}
		rewind(reader);
		float* numbers = malloc(entries * sizeof(float));
		i = 0;
		while (fscanf(reader, "%f", &numbers[i]) != EOF){
			i++;
		}
		qsort(numbers, entries, sizeof(float), intCompare);
		if (option == 0){
			i = 0;
			for (i; i < entries; i++){
				printf("%g\n", numbers[i]);
			}
		}
		else if (option == 1){
			i--;
			for (i; i >= 0; i--){
				printf("%g\n", numbers[i]);
			}
		}
		free(numbers);
	}
	else{
		printf("Csort: File %s does not exist\n", infile);
	}
}

void sort(char* infile, int option){ /* Sorts files of all types alphabetically. Its parameters are the filename and an integer corresponding to a filename. */
	FILE* reader;
	char line[100000]; /*don't have longer lines than this please*/
	int entries = 0;
	int i = 0;
	reader = fopen(infile, "r");
	if (reader){
		while (fgets(line, 100000, reader)){
			entries++;
		}
		rewind(reader);
		char** lines = malloc(entries * sizeof(char*));
		for (i; i < entries; i++){
			lines[i] = malloc(100000 * sizeof(char));
		}
		i = 0;
		while (fgets(lines[i], 100000, reader)){
			i++;
		}
		qsort(lines, entries, sizeof(char*), stringCompare);
		if (option == 0){
			i = 0;
			for (i; i < entries; i++){
				printf("%s", lines[i]);
			}
		}
		else if (option == 1){
			i--;
			for (i; i >= 0; i--){
				printf("%s", lines[i]);
			}
		}
		else if (option == 2){
			i = 0;
			for (i; i < entries; i++){
				if (i > 0){
					if (strcmp(lines[i], lines[i-1]) != 0){
						printf("%s", lines[i]);
					}
				}
				else{
					printf("%s", lines[i]);
				}
			}
		}
	}
	else{
		printf("Csort: File %s does not exist\n", infile);
	}
}

int main(int argc, char** argv){ /* Checks that command line arguments are correct */
	if (argc > 3){
		printf("Csort: Too many arguments\n");
		return 0;
	}
	else if(argc < 2){
		printf("Csort: Too few arguments\n");
		return 0;
	}
	else if(argc == 2 && (strcmp(argv[1], "-n") == 0 || strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "-u") == 0 || strcmp(argv[1], "-nr") == 0)){
		printf("Csort: No filename specified\n");
	}
	else{
		if (argc == 2){
			sort(argv[1], 0);
		}
		else if (strcmp(argv[1], "-n") == 0){
			intSort(argv[2], 0);
		}
		else if (strcmp(argv[1], "-r") == 0){
			sort(argv[2], 1);
		}
		else if (strcmp(argv[1], "-u") == 0){
			sort(argv[2], 2);
		}
		else if (strcmp(argv[1], "-nr") == 0){
			intSort(argv[2], 1);
		}
		else{
			printf("Csort: %s is not a valid option\n", argv[1]);
		}
	}
	return 0;
}