#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
typedef enum{
    TK_INT, TK_RETURN, TK_SEMI, TK_FLOAT,
    TK_IDENTIFIER, TK_DIGIT, TK_KEYWORDS, TK_LPAREN,
    TK_RPAREN, TK_LCURLYB, TK_RCURLYB, TK_RSQUAREB,
    TK_LSQUAREB, TK_FOR, TK_WHILE, TK_EQUAL, TK_EOF,
    TK_IF, TK_ELSE, TK_NOT
} TokenType;
typedef struct {
    TokenType type;
    char* value;
} Token;
char *read_file(const char* path);

void printToken(Token token);

Token get_next_token(char **src);

#endif
