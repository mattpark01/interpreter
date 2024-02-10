#ifndef LEXER_H
#define LEXER_H

typedef enum {
    SEMICOLON, LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    PLUS, MINUS, STAR, SLASH, EQUAL, BANG,
    EQUAL_EQUAL, BANG_EQUAL,
    IDENTIFIER, STRING, NUMBER,
    AND, CLASS, ELSE, FALSE, FOR, IF, NIL, OR, POWER,
    TOKEN_EOF,
    TOKEN_TYPE_COUNT, // we keep as the last element for counting purposes.
    TOKEN_UNDEFINED
} TokenType;

typedef struct {
    TokenType type;
    char* lexeme;
    int line;
} Token;

void addToken(Token** tokens, int* count, int* capcaity, TokenType type, const char* lexeme, int line);
void tokenize(const char* source, Token** outTokens, int* tokenCount);
void printToken(const Token* token);
void freeToken();

#endif LEXER_H