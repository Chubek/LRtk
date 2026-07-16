#if !defined(_Lexis_Lexis_h)
#define _Lexis_Lexis_h

#include <iostream>
#include <string>
#include <stdint.h>

 namespace Lexis
 {
    typedef uint16_t StateNumber;
    typedef uint8_t TableEntry;
    StateNumber const errorState = 255;
    TableEntry const maximumCharacter = 128;

       enum Anchor
       {
            none = 0,
            head = 1,
            tail = 2,
            both = 3
       };
       inline ostream& operator<<(ostream& s, Anchor a)
       {
           switch (a)
           {
               case none: s << "none"; break;
               case head: s << "head"; break;
               case tail: s << "tail"; break;
               case both: s << "both"; break;
           }
           return s;
       }

       enum Action
       {
            advance = 0,
            accept = 1,
            discard = 3 // We want (discard & accept) != 0.
       };
       inline ostream& operator<<(ostream& s, Action a)
       {
           switch (a)
           {
               case advance: s << "advance"; break;
               case accept: s << "accept"; break;
               case discard: s << "discard"; break;
           }
           return s;
       }

       template<typename T>
       class Input
       {
            public: typedef T Token;
            private: enum Constants
            {
                 maximumLexemeLength = 1024,
                 bufferSize = 2 * maximumLexemeLength
            };
            private: istream& inputStream;
            private: char buffer[bufferSize];
            private: char* nextInput;
            private: char* endOfInput;
            private: char* const endOfBuffer;
            private: char* startOfLexeme;
            private: char* endOfLexeme;
            private: bool endOfFileRead;
            private: uint16_t currentLineNumber;
            private: uint16_t startMarkLineNumber;
            private: uint16_t endMarkLineNumber;
            private: void checkAssertions() const;
            private: int16_t advance();
            public: Input(istream&);
            public: operator bool();
            public: char operator*();
            public: Input& operator++();
            public: Input& operator--();
            public: void markStart();
            public: void markEnd();
            public: void returnToStartMark();
            public: void returnToEndMark();
            public: void advanceStartMark();
            public: uint16_t getLineNumber() const;
            public: string getLexeme() const;
       };
       template <typename T>
       inline uint16_t Input<T>::getLineNumber() const
            { return startMarkLineNumber; }

       template <typename T>
       class TokenStream;

       template <typename LT>
       class Token
       {
            public: typedef LT Tables;
            public: typedef TokenStream<Token> Stream;
            public: typedef typename LT::TokenType Type;
            private: Type type;
            private: string lexeme;
            private: uint16_t lineNumber;
            public: Token();
            public: Token(Type, string const&, uint16_t = 0);
            public: Token(Token const&);
            public: Token& operator=(Token const&);
            public: Type getType() const;
            public: string const& getLexeme() const;
            public: uint16_t getLineNumber() const;
            public: string getName() const;
            public: ostream& put(ostream& s) const;
       };
       template <typename LT>
       inline typename Token<LT>::Type Token<LT>::getType() const
            { return type; }
       template <typename LT>
       inline string const& Token<LT>::getLexeme() const
            { return lexeme; }
       template <typename LT>
       inline uint16_t Token<LT>::getLineNumber() const
            { return lineNumber; }
       template <typename LT>
       inline ostream& operator<<(ostream& stream, Token<LT> const& token)
            { return token.put(stream); }

       template <typename T>
       class TokenStream
       {
           public: typedef T Token;
           public: typedef typename T::Tables Tables;
           private: Input<Token> inputStream;
           private: TableEntry getTransition(TableEntry, char) const;
           private: bool isAcceptState(TableEntry) const;
           private: bool isAcceptOrDiscardState(TableEntry) const;
           private: bool isTailAnchored(TableEntry) const;
           private: bool isHeadAnchored(TableEntry) const;
           private: typename Token::Type getType(TableEntry) const;
           public: TokenStream(istream&);
           public: TokenStream& operator>>(Token&);
       };
       template <typename T>
       inline TokenStream<T>::TokenStream(istream& s) :
           inputStream(s)
           {}
  }

  #include "Lexis/Lexis.cc"

  #endif
