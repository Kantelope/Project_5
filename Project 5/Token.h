#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <sstream>

enum class TokenType {
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    EF //This is EF instead of EOF because that was throwing an error
};

class Token
{
private:
    TokenType typeT;
    std::string value;
    int lineNum;
    std::string tokenArray[18]{
            "COMMA",
            "PERIOD",
            "Q_MARK",
            "LEFT_PAREN",
            "RIGHT_PAREN",
            "COLON",
            "COLON_DASH",
            "MULTIPLY",
            "ADD",
            "SCHEMES",
            "FACTS",
            "RULES",
            "QUERIES",
            "ID",
            "STRING",
            "COMMENT",
            "UNDEFINED",
            "EOF"
    };

public:
    Token(TokenType type, std::string description, int line);
    std::string to_string();
    TokenType getType();
    std::string getString();
};

#endif // TOKEN_H

