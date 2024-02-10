#include "lexer.h"
#include "parser.h"
#include <stdio.h>

int main() {
    const char* source = "int product = foo() * bar() // example source code";
    
    int tokenCount;
    Token* tokens = NULL;
    tokenize(source, &tokens, &tokenCount);
    
    ASTNode* root = parse(tokens, tokenCount);
    
    // Here, you might evaluate the AST or print it for debugging
    
    freeTokens(tokens, tokenCount);
    freeAST(root);
    
    return 0;
}