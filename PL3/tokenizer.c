

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int charCounter(FILE *fp){
	int count = 0;
	char ch = fgetc(fp);
	while (ch != EOF){
		count++;
		ch = fgetc(fp);
	}
	return count;
}

int delimCheck (char ch) {		/* check for deliminators */
	if (ch == ',' || ch == ';' || ch == '('
		|| ch == ')'|| ch == '{'|| ch == '}'){
		return 1;
	}
	else if(ch == '\t'|| ch == '\n' || ch == ' '){

		return 2;
	}
	else{
		return 0;
	}
}

int opCheck (char ch) {		/* check for operators */
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/'||ch == '%' ){
		return 1;
	}
	if (ch == '=' || ch == '!'|| ch == '|' || ch == '<' || ch == '>' || ch == '&'){
		return 2;
	}

	else{
		return 0;
	}
}
int checkTwo (char* temp){
	if (strcmp(temp, "==") == 0 || strcmp(temp, "!=") == 0 || strcmp(temp, "<=") == 0 || strcmp(temp, ">=") == 0 || strcmp(temp, "||") == 0 || strcmp(temp, "&&") == 0 ){
		return 1;
	}
	else{
		return 0;
	}
}

int main(int argc, char** argv){
	FILE *fp;
	char ch;
	char fch;
	int count = 0;
	char** tokenArray = malloc(1000000 * sizeof(char*));
	int i = 0;
	for (i; i < 1000000; i++){
		tokenArray[i] = malloc(64 * sizeof(char));
	}
	fp = fopen(argv[1], "r");
	if (fp == NULL){
		printf("Invalid file\n");
		return 0;
	}
	int var = 0;
	char string[64];
	char temp[3];
	ch = fgetc(fp);
	i = 0;
	while (ch != EOF){
		count++;
		if (delimCheck(ch) == 1){
			if (var == 1){
				strcpy(tokenArray[i], string);
				i++;
				memset(string, 0, 64);
				string[0] = ch;
				strcpy(tokenArray[i], string);
				i++;
				memset(string, 0, 64);
			}else{
				memset(string, 0, 64);
				string[0] = ch;
				strcpy(tokenArray[i], string);
				i++;
				memset(string, 0, 64);
			}
			var = 0;
		}
		else if(delimCheck(ch) == 2){
			if (var == 1){
				strcpy(tokenArray[i], string);
				i++;
				memset(string, 0, 64);
				var = 0;
			}

		}
		else if (opCheck(ch) == 1){
			if (var == 1){
				strcpy(tokenArray[i], string);
				i++;
				memset(string, 0, 64);
				string[0] = ch;
				strcpy(tokenArray[i], string);
				i++;
				memset(string, 0, 64);
			}else{
				memset(string, 0, 64);
				string[0] = ch;
				strcpy(tokenArray[i], string);
				i++;
				memset(string, 0, 64);
			}
			var = 0;
		}
		else if (opCheck(ch) == 2){
			
			fch = fgetc(fp);
			temp[0] = ch;
			temp[1] = fch;
			if (checkTwo(temp) == 1){
				if (var == 1){
					strcpy(tokenArray[i], string);
					i++;
					memset(string, 0, 64);
					strcpy(string,temp);
					strcpy(tokenArray[i], string);
					i++;
					memset(string, 0, 64);
				}
				else{
					memset(string, 0, 64);
					strcpy(string,temp);
					strcpy(tokenArray[i], string);
					i++;
					memset(string, 0, 64);
				}
			}
			else{
				if (var == 1){
					strcpy(tokenArray[i], string);
					i++;
					memset(string, 0, 64);
					string[0] = ch;
					strcpy(tokenArray[i], string);
					i++;
					if (delimCheck(fch) != 2){
					memset(string, 0, 64);
					string[0] = fch;
					strcpy(tokenArray[i], string);
					i++;
					memset(string, 0, 64);
					}
				}else{
					memset(string, 0, 64);
					string[0] = ch;
					strcpy(tokenArray[i], string);
					i++;
					if (delimCheck(fch) != 2){
					memset(string, 0, 64);
					string[0] = fch;
					strcpy(tokenArray[i], string);
					i++;
					memset(string, 0, 64);
				}
				}
			}
			var = 0;
		}
		else{
			if(var == 0){
				memset(string, 0, 64);
				string[strlen(string)] = ch;
				var = 1;
			}else{
				string[strlen(string)] = ch;
			}
		}
		ch = fgetc(fp);
	}
	int counter, indent;
	for(counter = 0; counter < i; counter++){
		if(indent == 5){
		printf("\n%s ", tokenArray[counter]);
		indent = 0;
		}else{
		printf("%s ", tokenArray[counter]);
		}
		indent++;
	}
	printf("\n");
	return 0;
}
