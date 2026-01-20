#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
typedef enum{
    TK_INT, TK_RETURN, TK_SEMI, TK_FLOAT, TK_VARIABLE, TK_DIGIT
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
    if (token.type == TK_RETURN){
        printf("RETURN ");
    }else if (token.type == TK_VARIABLE){
        printf("VARIABLE(%s) ", token.value);
    }else if (token.type == TK_INT){
        printf("INT(%s) ", token.value);
    }else if(token.type == TK_DIGIT){
        printf("DIGIT(%s) ", token.value);
    }else if(token.type == TK_SEMI){
        printf("SEMI ");
    }
}
Token get_next_token(char **src){
    while(isspace(**src)){
            (*src)++;
    }


    char current = **src;
    Token t;
    t.type = -1;
    t.value = NULL;
    char buffer[100];
    int index = 0;
    bool hasEnded = false;
    bool isADigit = false;
        //checking if the next token is a variable or a reserved buffer
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
    }else{
        (*src)++;
    }
   
    buffer[index] = '\0';
    if (strcmp(buffer, "return") == 0){
        t.type = TK_RETURN; 
        t.value = strdup(buffer);
    }else if(strcmp(buffer, "int") == 0){
        t.type = TK_INT;
    }else if(strcmp(buffer, "float") == 0){
        t.type = TK_FLOAT;
    }else if(isADigit){
        t.type = TK_DIGIT;
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
