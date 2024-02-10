#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    // Single-character tokens
    SEMICOLON, LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    PLUS, MINUS, STAR, SLASH, EQUAL, BANG,
    // One or two character tokens
    EQUAL_EQUAL, BANG_EQUAL,
    // Literals
    IDENTIFIER, STRING, NUMBER,
    // Keywords
    AND, CLASS, ELSE, FALSE, FOR, IF, NIL, OR, POWER,
    TOKEN_TYPE_COUNT, // Placeholder to count the enum members
    // Undefined token type for errors and end-of-file
    TOKEN_UNDEFINED,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char* lexeme;
    int line;
} Token;

Token* tokens[1024]; // Array to hold pointers to tokens
int tokensCount = 0;

// Function prototypes
void addToken(TokenType type, const char* lexeme, int line);
void tokenize(const char* source);
void printToken(const Token* token);
void freeTokens();

int main() {
    const char* input_code =
        "\"example\" // STRING\n"
        "{ // LEFT_BRACE\n"
        "} // RIGHT_BRACE\n"
        "( // LEFT_PAREN\n"
        ") // RIGHT_PAREN\n"
        "; // SEMICOLON\n"
        "+ // PLUS\n"
        "- // MINUS\n"
        "* // STAR\n"
        "/ // SLASH\n"
        "= // EQUAL\n"
        "== // EQUAL_EQUAL\n"
        "! // BANG\n"
        "!= // BANG_EQUAL\n"
        "Hello // IDENTIFIER\n"
        "12345 // NUMBER\n"
        "AND CLASS ELSE FALSE FOR IF NIL OR // Keywords\n";
    
    tokenize(input_code);

    for (int i = 0; i < tokensCount; ++i) {
        printToken(tokens[i]);
    }

    freeTokens();

    return 0;
}

void addToken(TokenType type, const char* lexeme, int line) {
    Token* token = (Token*)malloc(sizeof(Token));
    token->type = type;
    token->lexeme = strdup(lexeme); // Duplicate the lexeme string
    token->line = line;
    tokens[tokensCount++] = token; // Fix: Added missing semicolon
}

void tokenize(const char* source) {
    int line = 1;
    for (const char* p = source; *p != '\0'; ++p) {
        switch (*p) {
            case '(': addToken(LEFT_PAREN, "(", line); break;
            case ')': addToken(RIGHT_PAREN, ")", line); break;
            case '{': addToken(LEFT_BRACE, "{", line); break;
            case '}': addToken(RIGHT_BRACE, "}", line); break;
            case ';': addToken(SEMICOLON, ";", line); break;
            case '+': addToken(PLUS, "+", line); break;
            // More cases to be added for other tokens
            case '\n': line++; break;
            // Handle numbers, strings, two-character tokens, etc.
        }
    }
    addToken(TOKEN_EOF, "", line); // Mark the end of file with an EOF token
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
        free(tokens[i]);         // Free the token itself
    }
}
