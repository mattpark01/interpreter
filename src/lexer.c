#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Token* tokens[1024];
int tokensCount = 0;

// Fucntion to dynamically add a token to the tokens array
void addToken(Token** tokens, int* count, int* capacity, TokenType type, const char* lexeme, int line) {
    if (*count >= *capacity) {
        *capacity *= 2;
        *tokens = realloc(*tokens, sizeof(Token) * (*capacity));
    }
    (*tokens)[*count].type = type;
    (*tokens)[*count].lexeme = strdup(lexeme); // copy lexeme
    (*tokens)[*count].line = line;
    (*count)++;
}

// Identifies if a lexeme matches a keyword and returns the corresponding token type.
TokenType checkKeyword(const char* lexeme) {
    // TODO: extend this keyword check.
    if (strcmp(lexeme, "and") == 0) return AND;
    if (strcmp(lexeme, "class") == 0) return CLASS;
    if (strcmp(lexeme, "else") == 0) return ELSE;
    return IDENTIFIER;
}
// The main tokenize function
void tokenize(const char* source, Token** outTokens, int* tokenCount) {
    int capacity = 1024; // initial capacity for tokens array.
    *outTokens = malloc(sizeof(Token) * capacity);
    int count = 0; // token count;
    int line = 1; // line num for tokens

    for (const char* p = source; *p != '\0'; p++) {
        // allocate more space if capacity is reached.
        if (count >= capacity) {
            capacity *= 2;
            *outTokens = realloc(*outTokens, sizeof(Token) * capacity);
            if (*outTokens == NULL) {
                // we handle reallocation failure
                // for simplicity, exiting, but we should ideally clean up and return an error.
                fprintf(stderr, "Failed to realllocate memory\n");
                exit(EXIT_FAILURE);
            }
        }

        // handle eachj character
        switch (*p) {
            case '(':
                addToken(outTokens, &count, &capacity, LEFT_PAREN, "(", line);
                break;
            case ')':
                addToken(outTokens, &count, &capacity, RIGHT_PAREN, ")", line);
                break;
            case '/':
                if (*(p + 1) == '/') { // Skip comments
                    while (*p != '\n' && *p != '\0') p++;
                    if (*p == '\n') line++;
                } else {
                    addToken(outTokens, &count, &capacity, SLASH, "/", line);
                }
                break;
            case ' ': case '\r': case '\t': case '\n':
                if (*p == '\n') line++;
                break; // ignore whitespace
            case '=':
                if (*(p + 1) == '=') {
                    addToken(outTokens, &count, &capacity, EQUAL_EQUAL, "==", line);
                    p++; // skip to next character
                } else {
                    addToken(outTokens, &count, &capacity, EQUAL, "=", line);
                }
                break;
            // TODO: handle other cases, such as numbers and identifiers
            
            default:
                if (isalpha(*p) || *p == '_') { // identifier or keyword
                    const char* start = p;
                    while (isalnum(*p) || *p == '_') p++;
                    char* lexeme = strndup(start, p - start);
                    TokenType type = checkKeyword(lexeme);
                    addToken(outTokens, &count, &capacity, type, lexeme, line);
                    free(lexeme);
                    p--; // adjust pointer since it will increment in for loop
                } else if (isdigit(*p)) { // number
                    const char* start = p;
                    while (isdigit(*p) || *p == '.') p++;
                    addToken(outTokens, &count, &capacity, NUMBER, strndup(start, p - start), line);
                    p--; // adjust pointer
                }
                break;
        }
    }
    // append EOF token
    addToken(outTokens, &count, &capacity, TOKEN_EOF, "", line);
    // update the count of tokens found
    *tokenCount = count;
}

void printToken(const Token* token) {
    const char* tokenNames[TOKEN_TYPE_COUNT] = {
        "SEMICOLON", "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE",
        "PLUS", "MINUS", "STAR", "SLASH", "EQUAL", "BANG",
        "EQUAL_EQUAL", "BANG_EQUAL",
        "IDENTIFIER", "STRING", "NUMBER",
        "AND", "CLASS", "ELSE", "FALSE", "FOR", "IF", "NIL", "OR", "POWER"
    };
    printf("Line %d: Type %s, Lexeme '%s'\n", token->line, tokenNames[token->type], token->lexeme);
}

void freeTokens() {
    for (int i = 0; i < tokensCount; ++i) {
        free(tokens[i]->lexeme); // Free the lexeme
        free(tokens[i]); // Free the token itself
    }
}