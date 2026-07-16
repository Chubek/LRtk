#if !defined(_Gramatika_Gramatika_cc)
#define _Gramatika_Gramatika_cc

  #include <iostream>
  #include "Gramatika/Gramatika.h"

namespace Gramatika
{
    template <typename T, typename A>
    ostream& Value<T,A>::put(ostream& s) const
         { return s << terminal; }
    template <typename T, typename A>
    ostream& StackItem<T,A>::put(ostream& s) const
    {
        s << "state = " << state << ", value = ";
        return Value<T,A>::put(s);
    }
    template <typename T, typename A, typename GT>
    TableEntry Parser<T,A,GT>::getEntry(
             StateNumber state, SymbolNumber symbol,
             MapEntry const* map, TableEntry const* table) const
    {
        uint16_t const start = map[state].start;
        uint8_t const count = map[state].count;
        for (uint8_t i = 0; i < count; ++i)
             if (table[start + i].symbol == symbol)
                 return table[start + i];
        TableEntry result;
        result.symbol = symbol;
        result.action = error;
        result.number = 0;
        return result;
    }
    template <typename T, typename A, typename GT>
    TableEntry Parser<T,A,GT>::getAction(
              StateNumber state, SymbolNumber symbol) const
    {
         return getEntry(state, symbol, GT::actionMap, GT::actionTable);
    }
    template <typename T, typename A, typename GT>
    TableEntry Parser<T,A,GT>::getGoto(
              StateNumber state, SymbolNumber symbol) const
    {
         return getEntry(state, symbol, GT::gotoMap, GT::gotoTable);
    }
    template <typename T, typename A, typename GT>
    Parser<T,A,GT>::Parser() :
         stack(),
         resultValue()
         {}
    template <typename T, typename A, typename GT>
    Parser<T,A,GT>::~Parser()
         {}
    template <typename T, typename A, typename GT>
    void Parser<T,A,GT>::shift(StateNumber state, T const& terminal)
    {
         stack.push(StackItem<T,A>(state, terminal));
    }
    template <typename T, typename A, typename GT>
    void Parser<T,A,GT>::reduce(ProductionNumber production)
    {
         ProductionIndex const length =
              GT::rightHandSideTable[production];

          stack.pop(length);

          SymbolNumber const symbol =
              GT::leftHandSideTable[production];
          TableEntry const entry =
              getGoto(stack.getTop().state, symbol);

          stack.push(StackItem<T,A>(entry.number, resultValue));
      }
    template <typename T, typename A, typename GT>
    bool Parser<T,A,GT>::recover(TokenStream& tokenStream, T& nextToken)
    {
        uint16_t const depth = stack.getSize();
        for (;;)
        {
             for (uint16_t i = 0; i < depth; ++i)
             {
                 TableEntry const entry = getAction(
                      stack[i].state, nextToken.getType());
                 if (entry.action != error)
                 {
                      stack.pop(i);
                      return true;
                 }
             }
             if (nextToken.getType() == TokenTables::end_of_file)
                 return false;
             cerr << "Gramatika: ignoring " << nextToken << "\n";
             tokenStream >> nextToken;
        }
    }
    template <typename T, typename A, typename GT>
    Value<T,A> Parser<T,A,GT>::parse(typename T::Stream& tokenStream)
    {
         stack.reset();

          stack.push(StackItem<T,A>(0, Value<T,A>()));

          T nextToken;
          tokenStream >> nextToken;
          for (;;)
          {
              TableEntry const entry = getAction(
                  stack.getTop().state, nextToken.getType());
              if (entry.action == shiftAction)
              {
                  shift(entry.number, nextToken);
                  tokenStream >> nextToken;
              }
              else if (entry.action == reduceAction)
              {
                  resultValue = stack.getTop();
                  if (!performAction(entry.number))
                      break;
                  if (entry.number == 0)
                      break;
                  reduce(entry.number);
              }
              else
              {
                  cerr << "Gramatika: Syntax error: unexpected " <<
                      nextToken << "\n";
                  if (!recover(tokenStream, nextToken))
                      break;
              }
          }
          return resultValue;
      }
}

  #endif
