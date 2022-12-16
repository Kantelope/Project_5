#include "Token.h"

Token::Token(TokenType type, std::string description, int line) {
    typeT = type;
    value = description;
    lineNum = line;
}
std::string Token::to_string() {
    std::ostringstream os;
    os << "(" << tokenArray[static_cast<int>(typeT)] << ",\"" << value << "\"," << std::to_string(lineNum) <<")";
    return os.str();
}
TokenType Token::getType(){
    return typeT;
}
std::string Token::getString() {
    return value;
}

