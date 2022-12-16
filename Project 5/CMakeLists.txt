cmake_minimum_required(VERSION 3.23)
project(Project_5)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project_5 main.cpp Automaton.h ColonAutomaton.h ColonAutomaton.cpp ColonDashAutomaton.h ColonDashAutomaton.cpp Lexer.h Lexer.cpp  Token.h Token.cpp CommaAutomaton.cpp CommaAutomaton.h PeriodAutomaton.cpp PeriodAutomaton.h Q_markAutomaton.cpp Q_markAutomaton.h Left_parenAutomaton.cpp Left_parenAutomaton.h Right_parenAutomaton.cpp Right_parenAutomaton.h MultiplyAutomaton.cpp MultiplyAutomaton.h AddAutomaton.cpp AddAutomaton.h SchemesAutomaton.cpp SchemesAutomaton.h FactsAutomaton.cpp FactsAutomaton.h RulesAutomaton.cpp RulesAutomaton.h QueriesAutomaton.cpp QueriesAutomaton.h IDAutomaton.cpp IDAutomaton.h StringAutomaton.cpp StringAutomaton.h CommentAutomaton.cpp CommentAutomaton.h UndefinedAutomaton.cpp UndefinedAutomaton.h DatalogProgram.cpp DatalogProgram.h Rule.cpp Rule.h Predicate.cpp Predicate.h Parameter.cpp Parameter.h Header.cpp Header.h Tuple.cpp Tuple.h Relation.cpp Relation.h Database.cpp Database.h Graph.cpp Graph.h)

