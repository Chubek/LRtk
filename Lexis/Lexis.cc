#if !defined(_Lexis_Lexis_cc)
#define _Lexis_Lexis_cc

#include <iostream>
#include <string>
#include "Lexis/Lexis.h"
#include "Toolbox/EscapeSequence.h"

  using namespace Toolbox;

namespace Lexis
{
    template <typename T>
    Input<T>::Input(istream& s) :
        inputStream(s),
        nextInput(buffer),
        endOfInput(buffer),
        endOfBuffer(buffer + bufferSize),
        startOfLexeme(buffer),
        endOfLexeme(buffer),
        endOfFileRead(false),
        currentLineNumber(0),
        startMarkLineNumber(0),
        endMarkLineNumber(0)
    {
        assert(endOfInput < endOfBuffer);
        *endOfInput++ = '\n';
        checkAssertions();
    }
    template <typename T>
    void Input<T>::checkAssertions() const
    {
        assert(buffer <= startOfLexeme);
        assert(startOfLexeme <= endOfLexeme);
        assert(endOfLexeme <= nextInput);
        assert(nextInput <= endOfInput);
        assert(endOfInput <= endOfBuffer);
        assert(nextInput - startOfLexeme <= maximumLexemeLength);
    }
    template <typename T>
    int16_t Input<T>::advance()
    {
        if (nextInput == endOfInput && !endOfFileRead)
        {
             if (endOfInput == endOfBuffer)
             {
                     uint32_t const shift = startOfLexeme - buffer;
                     char* dst = buffer;
                     char* src = startOfLexeme;
                     while (src < endOfInput)
                          *dst++ = *src++;
                     startOfLexeme -= shift;
                     endOfLexeme -= shift;
                     endOfInput -= shift;
                     nextInput -= shift;
             }
             assert(endOfInput < endOfBuffer);
             int const c = inputStream.get();
             if (c == EOF)
                 endOfFileRead = true;
             else
             {
                 *endOfInput = c;
                 endOfInput += 1;
             }
        }
        int16_t result = EOF;
        if (nextInput < endOfInput)
             result = *nextInput;
        else
             assert(endOfFileRead);
        checkAssertions();
        return result;
    }
    template <typename T>
    Input<T>::operator bool()
         { return advance() != EOF; }
    template <typename T>
    char Input<T>::operator*()
    {
         int16_t const c = advance();
         if (c != EOF)
              return c;
         else
              return 0;
    }
    template <typename T>
    Input<T>& Input<T>::operator++()
    {
        if (nextInput == endOfInput && !endOfFileRead)
             advance();
        if (nextInput < endOfInput)
        {
             if (*nextInput == '\n')
                 currentLineNumber += 1;
             nextInput += 1;
             if (nextInput - startOfLexeme > maximumLexemeLength)
             {
             if (*startOfLexeme == '\n')
                     startMarkLineNumber += 1;
                 startOfLexeme += 1;
                 if (endOfLexeme < startOfLexeme)
                 {
             if (*endOfLexeme == '\n')
                          endMarkLineNumber += 1;
                     endOfLexeme += 1;
                 }
             }
        }
        else
             assert(endOfFileRead);
        checkAssertions();
        return *this;
    }
    template <typename T>
    Input<T>& Input<T>::operator--()
    {
        if (nextInput > startOfLexeme)
        {
             nextInput -= 1;
             if (*nextInput == '\n')
                 currentLineNumber -= 1;
             if (endOfLexeme > nextInput)
             {
                 endOfLexeme = nextInput;
                 endMarkLineNumber = currentLineNumber;
             }
        }
        checkAssertions();
        return *this;
    }
    template <typename T>
    void Input<T>::markStart()
    {
         startOfLexeme = nextInput;
         endOfLexeme = nextInput;
         startMarkLineNumber = currentLineNumber;
         endMarkLineNumber = currentLineNumber;
         checkAssertions();
    }
    template <typename T>
    void Input<T>::markEnd()
    {
         endOfLexeme = nextInput;
         endMarkLineNumber = currentLineNumber;
         checkAssertions();
    }
    template <typename T>
    void Input<T>::returnToStartMark()
    {
         nextInput = startOfLexeme;
         endOfLexeme = startOfLexeme;
         currentLineNumber = startMarkLineNumber;
         checkAssertions();
    }
    template <typename T>
    void Input<T>::returnToEndMark()
    {
         nextInput = endOfLexeme;
         currentLineNumber = endMarkLineNumber;
         checkAssertions();
    }
    template <typename T>
    void Input<T>::advanceStartMark()
    {
         if (startOfLexeme < endOfLexeme)
              if (*startOfLexeme == '\n')
                  startMarkLineNumber += 1;
              startOfLexeme += 1;
         checkAssertions();
    }
    template <typename T>
    string Input<T>::getLexeme() const
    {
         string result(startOfLexeme, endOfLexeme - startOfLexeme);
         checkAssertions();
         return result;
    }
    template <typename LT>
    Token<LT>::Token() :
         type(LT::end_of_file),
         lexeme(""),
         lineNumber(0)
         {}
    template <typename LT>
    Token<LT>::Token(Token<LT>::Type t, string const& s, uint16_t l) :
         type(t),
         lexeme(s),
         lineNumber(l)
         { assert(0 <= type && type < LT::numberOfTokens); }
    template <typename LT>
    Token<LT>::Token(Token<LT> const& t) :
         type(t.type),
         lexeme(t.lexeme),
         lineNumber(t.lineNumber)
         { assert(0 <= type && type < LT::numberOfTokens); }
    template <typename LT>
    Token<LT>& Token<LT>::operator=(Token<LT> const& t)
    {
         type = t.type;
         lexeme = t.lexeme;
         lineNumber = t.lineNumber;
         return *this;
    }
    template <typename LT>
    string Token<LT>::getName() const
    {
        uint8_t i;
        for (i = 0; i < LT::numberOfTokens; ++i)
             if (LT::nameTable[i].type == type)
                 break;
        assert(i < LT::numberOfTokens);
        return LT::nameTable[i].name;
    }
    template <typename LT>
    ostream& Token<LT>::put(ostream& s) const
    {
         s << "Token {" << getName();
         s << ", \"" << EscapeSequence::encode(lexeme, '"') << "\"";
         return s << ", " << lineNumber << "}";
    }
    template <typename T>
    TableEntry TokenStream<T>::getTransition(TableEntry state, char c) const
    {
        assert(state < Tables::numberOfStates);
        if (static_cast<uint8_t>(c) < maximumCharacter)
             return Tables::transitionTable[
                 Tables::rowMap[state] * Tables::numberOfColumns
                 + Tables::columnMap[c]];
        else
            return errorState;
    }
    template <typename T>
    bool TokenStream<T>::isAcceptState(TableEntry state) const
    {
        assert(state < Tables::numberOfStates);
        return Tables::actionTable[state] == accept;
    }
    template <typename T>
    bool TokenStream<T>::isAcceptOrDiscardState(TableEntry state) const
    {
        assert(state < Tables::numberOfStates);
        return (Tables::actionTable[state] & accept) != 0;
    }
    template <typename T>
    bool TokenStream<T>::isTailAnchored(TableEntry state) const
    {
        assert(state < Tables::numberOfStates);
        return (Tables::anchorTable[state] & tail) != 0;
    }
    template <typename T>
    bool TokenStream<T>::isHeadAnchored(TableEntry state) const
    {
        assert(state < Tables::numberOfStates);
        return (Tables::anchorTable[state] & head) != 0;
    }
    template <typename T>
    typename T::Type TokenStream<T>::getType(TableEntry state) const
    {
        assert(state < Tables::numberOfStates);
        return Tables::tokenTable[state];
    }
    template <typename T>
    TokenStream<T>& TokenStream<T>::operator>>(T& result)
    {
        TableEntry currentState = 0;
        TableEntry nextState = 0;
        TableEntry acceptState = 0;
        inputStream.markStart();
        for (;;)
        {
            if (inputStream)
            {
                 char const nextChar = *inputStream;
                 ++inputStream;
                 nextState = getTransition(currentState, nextChar);
            }
            else if (acceptState != 0)
                 nextState = errorState;
            else
            {
                 result = T(Tables::end_of_file, "",
                     inputStream.getLineNumber());
                 return *this;
            }
            currentState = nextState;
            if (currentState != errorState)
            {
                 if(isAcceptOrDiscardState(currentState))
                 {
                     acceptState = currentState;
                     inputStream.markEnd();
                 }
            }
            else
            {
                 if (acceptState != 0)
                 {
                      inputStream.returnToEndMark();
                      if (isTailAnchored(acceptState))
                          --inputStream;
                      if (isHeadAnchored(acceptState))
                          inputStream.advanceStartMark();
                      if (isAcceptState(acceptState))
                      {
                          result = T(getType(acceptState),
                                inputStream.getLexeme(),
                                inputStream.getLineNumber());
                          return *this;
                      }
                 }
                 else
                 {
                      inputStream.returnToStartMark();
                      char const nextChar = *inputStream;
                      cerr << "Lexis: Input error on line " <<
                            inputStream.getLineNumber() << ".";
                      cerr << " Input character '" <<
                            EscapeSequence::encode(nextChar, '\'')
                            << "' ignored.\n";
                      ++inputStream;
                 }
                 currentState = 0;
                 acceptState = 0;
                 inputStream.markStart();
            }
        }
    }
}

  #endif
