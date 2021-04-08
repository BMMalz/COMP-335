
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
char* token;
char* lookahead;
void nextToken(){
	char c;
	token += 80;
	lookahead += 80;
	scanf("%c", &c);
}

int main(int argc, char** argv){
	FILE *fp;
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
	tokenize(tokenArray,fp);
	program();
	/*
	printf("Token: %s address: %p | Lookahead: %s address: %p \n",token, token,lookahead,lookahead);
	while (strcmp(token,"") != 0){
	nextToken();
	printf("Token: %s address: %p | Lookahead: %s address: %p \n",token, token,lookahead,lookahead);
	}
	*/
}


int tokenize(char** tokenArray,FILE *fp){
	int var = 0;
	int i = 0;
	int count = 0;
	char ch;
	char fch;
	char string[64];
	char temp[3];
	memset(string, 0, 64);
	memset(temp, 0, 3);
	ch = fgetc(fp);
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
	indent = 0;
	for(counter = 0; counter < i; counter++){
		if(indent == 5){
		printf("\n%s ", tokenArray[counter]);
		indent = 0;
		}else{
		printf("%s ", tokenArray[counter]);
		}
		indent++;
	}
	token = tokenArray[0];
	lookahead = tokenArray[1];
	printf("\n");
	return 0;
}
int addop (){
	printf("addop %s\n", token);
	if (token == "+"){
		return 0;
	}else if(token == "-"){
		return 0;
	}else{
		printf("Error: + or - expected\n");
		return 1;
	}
}
int additiveExp(){
	printf("additiveExp %s\n", token);
	if(lookahead = "*"){
		MultipliExp();
		return 0;
	}else if (lookahead = "+"){
		additiveExp();
		nextToken();
		addop();
		nextToken();
		MultipliExp();
		return 0;
	}else{
		printf("Error: * or + expected\n");
		return 1;
	}
}
int assignmentExp(){
	printf("assignmentExp %s\n", token);
	unaryExp();
	nextToken();
	assignmentOp();
	nextToken();
	primaryExp();
	return 0;
}
int assignmentOp(){
	printf("assignmentOp %s\n", token);
	if (strcmp("=", token) == 0){
		return 0; 
	}
	else{
		printf("Error: = expected\n");
		return 1;
	}
}

int cpdStatement(){
	printf("cpdStatement %s\n", token);
	if (strcmp(token, "{") == 0){
		/* brackets mean optional == FUTURE SELF WRITE SOMETHING HERE TO HANDLE OPTIONALITY*/
		nextToken();
		decList();
		nextToken();
		statementList();
		nextToken();
		if (strcmp(token, "}") == 0){
			return 0;
		}
		else{
			printf("Error: } expected \n");
			return 1;
		}
	}
	else{
		printf("Error: { expected \n");
		return 1;
	}
}
int condStatement (){
	printf("condStatement %s\n", token);
	ifOrElseStatement();
	return 0;
}

int constant(){
	printf("constant %s\n", token);
	char numba[64];
	strcpy(numba, token);
	printf("%s\n", numba);
	int isDot = 0;
	int pos = 0;
	for (pos; pos < 64; pos++){
		if (numba[pos] == '.'){
		isDot = 1;
		}
		if (isDot == 1){
		pos = 65;
		}
	}
if (isDot == 1){
	printf("Is dot\n");
	floatingConst();
}else{
	printf("No dot\n");
	integerConst();
	}
}

/*CONDITIONAL EXPRESSION HAS BEEN SIMPLIFIED AND REMOVED - SEE LOGICAL-OR-EXPRESSION */
int declaration(){
	printf("declaration %s\n", token);
	typeSpec();
	initializedDeclaratorList();
}
int decList(){
	printf("decList %s\n", token);
	declaration();
	printf("about to do dec list again token: %s lookahead: %s\n", token, lookahead);
	if (strcmp(token, ";") != 0){
		decList();
	}else{
		return 0;
	}
}
/*DECLARATION SPECIFIER REPLACED WITH TYPE SPECIFIER FOR SIMPLIFICATION*/
int digit(char integer){
	printf("digit \n");
	switch (integer){
		case 0: return 0;
		case 1: return 0;
		case 2: return 0;
		case 3: return 0;
		case 4: return 0;
		case 5: return 0;
		case 6: return 0;
		case 7: return 0;
		case 8: return 0;
		case 9: return 0;
		default: return 1;
	}
}
int digitSeq(){
	printf("digitSeq %s\n", token);
	int i = 0;
	for (i; i < strlen(token); i++){ /* this doesnt work. redo this POSSIBLITITY: have this and letter funtion be the only ones that take arguements. feed them one char at a time.*/
		if (digit(token[i]) != 0){
			printf("Error: expected digit\n");
			return 1;
		}
	}
}
int equalityOp(){
	printf("equalityOp %s\n", token);
	if (token == "=="){
		return 0;
	}else if(token == "!="){
		return 0;
	}else{
		printf("Error: Equality Operator expected\n");
		return 1;
	}
}
int equalityOpLookahead(){
	printf("equalityOpLookahead %s\n", token);
	if (lookahead == "=="){
		return 0;
	}else if(lookahead == "!="){
		return 0;
	}else{
		printf("Error: Equality Operator expected\n");
		return 1;
	}
}
int equalityExpression(){
	printf("equalityExpression %s\n", token);
	if (equalityOpLookahead() == 0){
		equalityExpression();
		nextToken();
	}
	relationalExp();
}
int expression(){ /*MIGHT BE REDUNDANT! CHECK EXPRESSION STATEMENT*/
	printf("expression %s\n", token);
	assignmentExp();
}
int expressionStatement(){ 
	printf("expressionStatement %s\n", token);
	expression();
	nextToken();
	if (token != ";"){
		printf("Error: ; expected\n");
		return 1;
	}else{
		return 0;
	}
}
int floatingConst(int dot){
	/*someone either make this check digits within this funtion or make it work with digits funtion*/
}
int floatTypeSpec(){
	printf("floatTypeSpec %s\n", token);
	if (strcmp(token, "float") != 0){
		return 1;
	}
	else{
		return 0;
	}
}
int letter(char c){
	printf("letter \n");
	if(isalpha(c) == 0){
		printf("Error: character expected\n");
		return 1;
	}else{
		return 0;
	}
}
int followingChar(char unknown){
	printf("followingChar %s\n", token);
	if(digit(unknown) == 0){
		return 0;
	}else if(letter(unknown) == 0){
		return 0;
	}else{
		return 1;
	}
}
int identifier(){
	printf("identifier \n");
	printf("ID token: %s lookahead: %s\n", token, lookahead);
	if(strlen(token) == 1 && isalpha(token[0]) != 0){
		letter(token[0]);
	}else{
		int i, var;
		for(i=0;i < strlen(token);i++){
		var = followingChar(token[i]);
			if (var == 1){
				printf("Error: integer or character expected\n");
				return 0;
			}
		}
	}
}
int ifOrElseStatement(){
	if (strcmp(token, "if") == 0){
		nextToken();
		if (strcmp(token, "(") == 0){
			nextToken();
			logicalOrExp();
		}
		else{
			printf("error: expected (\n");
		}
	}
	else{
		printf("error: expected if\n");
	}
}
int initializedDeclaratorList(){
	printf("initializedDeclaratorList %s\n", token);
	if (strcmp(lookahead, ",") == 0){
		identifier();
		nextToken();
		nextToken();
		initializedDeclaratorList();
	}
	else{
		identifier();
		printf("got the variable as: %s, with the lookahead: %s\n",token,lookahead );
		nextToken();
		if(strcmp(token, ";") == 0 && (strcmp(lookahead, "int") ==0 || strcmp(lookahead, "float") == 0)){
		nextToken();
		}
		printf("got the variable as: %s, with the lookahead: %s\n",token,lookahead );
	}
}
int integerConst(){

}
int intTypeSpec(){
	printf("intTypeSpec %s\n", token);
	if (strcmp(token, "int") != 0){
		return 1;
	}else{
		return 0;
	}
}

int logicalAndExp(){

}
int logicalOrExp(){
	printf("logicalOrExp\n");
}
int MultipliExp(){

}
int MultOp(){

}
int nullStatement(){

}
int parenExpression(){

}
int primaryExp(){

}
int program(){
	printf("Program \n");
	if(strcmp(token, "void") == 0){
		nextToken();
		if(strcmp(token, "main") == 0){
			nextToken();
			if(strcmp(token, "(") == 0){
				nextToken();
				if(strcmp(token, ")") == 0){
					nextToken();
					cpdStatement();
				}
				else{
					printf("error: expected )\n");
				}
			}
			else{
					printf("error: expected (\n");
				}
		}
		else{
				printf("error: expected main\n");
			}
	}
	else{
			printf("error: expected void\n");
		}
}
int relationalExp(){

}
int relationalOp(){

}
int statement(){

}
int statementList(){
	return 0;
}
int typeSpec(){
	printf("typeSpec\n");
	if (floatTypeSpec() == 1 && intTypeSpec() == 1){
		printf("Error: type specifier not recognized: %s\n", token);
		nextToken();
	}
	else{
		printf("type spec is valid\n");
		nextToken();
	}
}
int unaryExp(){
	return 0;
}
int whileStatement(){

}