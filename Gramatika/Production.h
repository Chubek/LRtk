#if !defined(_Gramatika_Production_h)
#define _Gramatika_Production_h

#include <iostream>
#include <vector>
#include <string>
#include "Gramatika/Gramatika.h"
#include "Toolbox/Set.h"

  using namespace Toolbox;

namespace Gramatika
{
    class Symbol;
    class Production
    {
        private: ProductionNumber number;
        private: Symbol* leftHandSide;
        private: vector<Symbol*> rightHandSide;
        private: string action;
        private: ProductionIndex getPosition(
            string const&, ProductionIndex) const;
        public: Production();
        public: ~Production();
        public: void setNumber(ProductionNumber);
        public: void setLeftHandSide(Symbol*);
        public: void setAction(string const&);
        public: void add(Symbol*);
        public: ProductionNumber getNumber() const;
        public: Symbol* getLeftHandSide() const;
        public: Symbol* getRightHandSide(ProductionIndex) const;
        public: ProductionIndex getLength() const;
        public: Set getFirstClosure() const;
        public: ostream& put(ostream&) const;
        public: ostream& putAction(ostream&) const;
    };
    inline void Production::setNumber(ProductionNumber n)
        { number = n; }
    inline void Production::setLeftHandSide(Symbol* symbol)
        { leftHandSide = symbol; }
    inline void Production::setAction(string const& s)
        { action = s; }
    inline ProductionNumber Production::getNumber() const
        { return number; }
    inline Symbol* Production::getLeftHandSide() const
        { return leftHandSide; }
    inline ProductionIndex Production::getLength() const
        { return rightHandSide.size(); }
    inline ostream& operator<<(ostream& stream, Production const& production)
        { return production.put(stream); }
}

  #endif
