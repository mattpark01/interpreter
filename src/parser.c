#include "parser.h"
#include <stdlib.h>

ASTNode* parseExpression(Token** tokens, int* currentIndex) {
    // TODO: Implement parsing logic
    // This is where we hadnle different precedence levels and parse binary expressions, literals, etc.
}

// Main parse function
ASTNode* parse(Token* tokens, int tokensCount) {
    int currentIndex = 0;
    ASTNode* root = parseExpression(&tokens, &currentIndex);
    return root;
}

void freeAST(ASTNode* node) {
    // Recursively free the AST
    if (!node) return;
    switch (node->type) {
        case AST_BINARY_EXPR:
            freeAST(node->data.binaryExpr.left);
            freeAST(node->data.binaryExpr.right);
            break;
        // TODO: handle other AST node types
    }
    free(node);
}