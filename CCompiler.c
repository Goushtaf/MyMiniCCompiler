#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
typedef enum{
    TK_INT, TK_RETURN, TK_SEMI, TK_FLOAT,
    TK_IDENTIFIER, TK_DIGIT, TK_KEYWORDS, TK_LPAREN,
    TK_RPAREN, TK_LCURLYB, TK_RCURLYB, TK_RSQUAREB,
    TK_LSQUAREB, TK_FOR, TK_WHILE, TK_EQUAL, TK_EOF
} TokenType;
typedef struct {
    TokenType type;
    char* value;
} Token;
char *read_file(const char* path){
    FILE *file = fopen(path, "rb");
    if (!file){
        perror("Unable to open the file");
        exit(1);
    }
    
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(length + 1);
    if (!buffer){
        perror("Unable to initiate the buffer");
        exit(1);
    }


    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    fclose(file);
    return buffer;
}
void printToken(Token token){
    switch (token.type){
        case (TK_RETURN):
            printf("RETURN ");
            break;
        case (TK_IDENTIFIER):
            printf("IDENTIFIER(%s) ", token.value);
            break;
        case (TK_INT):
            printf("INT ");
            break;
        case (TK_DIGIT):
            printf("DIGIT(%s) ", token.value);
            break;
        case (TK_SEMI):
            printf("SEMI ");
            break;
        case (TK_LPAREN):
            printf("LPAREN ");
            break;
        case (TK_RPAREN):
            printf("RPAREN ");
            break;
        case (TK_LCURLYB):
            printf("LCURLYB ");
            break;
        case (TK_RCURLYB):
            printf("RCURLYB " );
            break;
        case (TK_LSQUAREB):
            printf("LSQUAREB ");
            break;
        case (TK_RSQUAREB):
            printf("RSQUAREB ");
            break;
        case (TK_FOR):
            printf("FOR ");
            break;
        case (TK_WHILE):
            printf("WHILE ");
            break;
        case (TK_FLOAT):
            printf("FLOAT ");
            break;
        case (TK_EQUAL):
            printf("EQUAL ");
            break;
        case (TK_EOF):
            printf("EOF ");
            break;
        default:
            printf("NOT_IMPLEMENTED ");
    }
}
Token get_next_token(char **src){
    //Skipping spaces
    while(isspace(**src)){
            (*src)++;
    }
    //ckecking if end of FILE
    if (**src == '\0'){
        Token t;
        t.type = TK_EOF;
        t.value = NULL;
        return t;
    }


    char current = **src;
    Token t;
    t.type = -1;
    t.value = NULL;
    char buffer[100];
    int index = 0;
    bool hasEnded = false;
    bool isADigit = false;
    //checking the type of the next token; 
    if (isalpha(current) || current == '_'){
        while (isalnum(**src) || **src == '_'){
            buffer[index++] = **src;
            (*src)++;
        }
    }else if (isdigit(current)){
        isADigit = true;
        while(isdigit(**src)){
            buffer[index++] = **src;
            (*src)++;
        }
    }else if (current == ';'){
        t.type = TK_SEMI;
        (*src)++;
    }else if (current == '('){
        t.type = TK_LPAREN;
        (*src)++;
    }else if (current == ')'){
        t.type = TK_RPAREN;
        (*src)++;
    }else if (current == '{'){
        t.type = TK_LCURLYB;
        (*src)++;
    }else if (current == '}'){
        t.type = TK_RCURLYB;
        (*src)++;
    }else if (current == '['){
        t.type = TK_LSQUAREB;
        (*src)++;
    }else if (current == ']'){
        t.type = TK_RSQUAREB;
        (*src)++;
    }else if (current == '='){
        t.type = TK_EQUAL;
        (*src)++;
    }else{
        (*src)++;
    }
   
    buffer[index] = '\0';

    //Checking for key words
    if (strcmp(buffer, "return") == 0){
        t.type = TK_RETURN; 
    }else if(strcmp(buffer, "int") == 0){
        t.type = TK_INT;
    }else if(strcmp(buffer, "float") == 0){
        t.type = TK_FLOAT;
    }else if (strcmp(buffer, "for") == 0){
        t.type = TK_FOR;
    }else if (strcmp(buffer, "while") == 0){
        t.type = TK_WHILE;
    }else if(isADigit){
        t.type = TK_DIGIT;
        t.value = strdup(buffer);
    }else if(isalpha(buffer[0])){
        t.type = TK_IDENTIFIER;
        t.value = strdup(buffer);
    }
    return t;
}
int main(){
    char* buffer = read_file("text.txt");
    while(*buffer != '\0'){
        Token token = get_next_token(&buffer);
        printToken(token);;
    }
    return 0;
}
