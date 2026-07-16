#if !defined(_Lexis_State_h)
#define _Lexis_State_h

#include <iostream>
#include <string>
#include <stdint.h>
#include "Lexis/Lexis.h"

namespace Lexis
{
    class State
    {
         protected: StateNumber number;
         protected: Anchor anchor;
         protected: Action action;
         protected: string token;
         public: State();
         public: State(StateNumber, Anchor, Action, string const&);
         public: State& operator=(State const&);
         public: void setNumber(StateNumber);
         public: void setAnchor(Anchor);
         public: void setAction(Action);
         public: void setToken(string const&);
         public: StateNumber getNumber() const;
         public: Anchor getAnchor() const;
         public: Action getAction() const;
         public: string const& getToken() const;
         public: ostream& put(ostream&) const;
    };
    inline State::State() :
         number(0),
         anchor(none),
         action(advance),
         token()
         {}
    inline State::State(StateNumber n, Anchor ancr,
               Action actn, string const& s) :
         number(n),
         anchor(ancr),
         action(actn),
         token(s)
         {}
    inline StateNumber State::getNumber() const
         { return number; }
    inline Anchor State::getAnchor() const
         { return anchor; }
    inline Action State::getAction() const
         { return action; }
    inline string const& State::getToken() const
         { return token; }
    inline ostream& operator<<(ostream& stream, State const& state)
         { return state.put(stream); }
}

  #endif
