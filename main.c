#include "lexer.h"

int main(){
    char* buffer = read_file("text.txt");
    while (*buffer != '\0'){
        printToken(get_next_token(&buffer));
    }
    return 0;
}
