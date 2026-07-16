#if !defined(_Gramatika_Gramatika_h)
#define _Gramatika_Gramatika_h

  #include <stdint.h>
  #include "Toolbox/Stack.h"

  using namespace Toolbox;

namespace Gramatika
{
    typedef uint16_t SymbolNumber;
    typedef uint16_t StateNumber;
    typedef uint16_t ProductionNumber;
    typedef uint8_t ProductionIndex;
    enum Constants
    {
        epsilon = 0,
        end_of_file = 1
    };

      struct TableEntry
      {
          public: uint8_t symbol;
          public: uint8_t action;
          public: uint16_t number;
      };
      inline ostream& operator<<(ostream& s, TableEntry entry)
      {
          s << "{" << static_cast<uint16_t>(entry.symbol);
          s << "," << static_cast<uint16_t>(entry.action);
          s << "," << entry.number << "}";
          return s;
      }

      struct MapEntry
      {
          public: uint16_t start;
          public: uint8_t count;
      };
      inline ostream& operator<<(ostream& s, MapEntry entry)
      {
          s << "{" << entry.start;
          s << "," << static_cast<uint16_t>(entry.count) << "}";
          return s;
      }

      enum SymbolType
      {
          terminal,
          nonterminal
      };
      inline ostream& operator<<(ostream& s, SymbolType sym)
      {
          switch (sym)
          {
               case terminal: s << "terminal"; break;
               case nonterminal: s << "nonterminal"; break;
          }
          return s;
      }

      enum Action
      {
           shiftAction,
           reduceAction,
           error
      };
      inline ostream& operator<<(ostream& s, Action act)
      {
          switch (act)
          {
              case shiftAction: s << "shift"; break;
              case reduceAction: s << "reduce"; break;
              case error: s << "error"; break;
          }
          return s;
      }

      template <typename T, typename A>
      class Value : public A
      {
           public: typedef T Token;
           public: typedef A Attributes;
           public: Token terminal;
           public: int _default;
           public: Value();
           public: Value(Token const&);
           public: ostream& put(ostream&) const;
      };
      template <typename T, typename A>
      inline Value<T,A>::Value() :
           A(),
           terminal(),
           _default(0)
           {}
      template <typename T, typename A>
      inline Value<T,A>::Value(T const& t) :
           A(),
           terminal(t),
           _default(0)
           {}
      template <typename T, typename A>
      inline ostream& operator<<(ostream& stream, Value<T,A> const& value)
           { return value.put(stream); }

      template <typename T, typename A>
      class StackItem : public Value<T,A>
      {
      public:
          typedef T Token;
          typedef A Attributes;
          public: StateNumber state;
          public: StackItem();
          public: StackItem(StateNumber, Value<T,A>);
          public: ostream& put(ostream&) const;
      };
      template <typename T, typename A>
      inline StackItem<T,A>::StackItem() :
          Value<T,A>(),
          state(0)
          {}
      template <typename T, typename A>
      inline StackItem<T,A>::StackItem(StateNumber s, Value<T,A> v) :
          Value<T,A>(v),
          state(s)
          {}
      template <typename A,typename T>
      inline ostream& operator<<(
               ostream& stream, StackItem<T,A> const& item)
          { return item.put(stream); }

      template <typename T, typename A, typename GT>
      class Parser
      {
           public: typedef T Token;
           public: typedef A Attributes;
           public: typedef GT Tables;
           public: typedef typename T::Stream TokenStream;
           public: typedef typename T::Tables TokenTables;
           protected: Stack<StackItem<T,A> > stack;
           protected: Value<T,A> resultValue;
           protected: TableEntry getEntry(StateNumber, SymbolNumber,
                     MapEntry const*, TableEntry const*) const;
           protected: TableEntry getAction(StateNumber, SymbolNumber) const;
           protected: TableEntry getGoto(StateNumber, SymbolNumber) const;
           protected: void shift(StateNumber, Token const&);
           protected: void reduce(ProductionNumber);
           protected: bool recover(TokenStream&, Token&);
           protected: virtual bool performAction(ProductionNumber) = 0;
           public: Parser();
           public: virtual ~Parser();
           public: Value<T,A> parse(TokenStream&);
      };
  }

  #include "Gramatika/Gramatika.cc"

  #endif
