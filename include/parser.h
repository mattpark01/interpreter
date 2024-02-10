#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef enum {
    AST_BINARY_EXPR,
    AST_LITERAL,
    AST_VARIABLE,
    // TODO: add other AST node types
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    union {
        struct {
            Token operator;
            struct ASTNode* left;
            struct ASTNode* right;
        } binaryExpr;
        Token literal;
        Token variable;
        // TODO: add other node type representations
    } data;
} ASTNode;

ASTNode* parse(Token* tokens, int tokenCount);

void freeAST(ASTNode* node);

#endif PARSER_H