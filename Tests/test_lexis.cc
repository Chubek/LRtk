#include <sstream>
#include <catch2/catch_test_macros.hpp>
#include "Lexis/DFA.h"
#include "Lexis/NFA.h"
#include "Lexis/State.h"

TEST_CASE("lexis state stores metadata")
{
    Lexis::State state(3, Lexis::both, Lexis::accept, "identifier");
    REQUIRE(state.getNumber() == 3);
    REQUIRE(state.getAnchor() == Lexis::both);
    REQUIRE(state.getAction() == Lexis::accept);
    REQUIRE(state.getToken() == "identifier");
}

TEST_CASE("nfa from literal has one state per character plus start")
{
    Lexis::NFA nfa("abc");
    REQUIRE(nfa.getNumberOfStates() == 4);
    REQUIRE(nfa[0].isTransitionLabelled('a'));
    REQUIRE_FALSE(nfa[0].isTransitionLabelled('b'));
}

TEST_CASE("nfa metadata applies to final state")
{
    Lexis::NFA nfa("x");
    nfa.setAnchor(Lexis::tail);
    nfa.setAction(Lexis::discard);
    nfa.setToken("x_token");
    REQUIRE(nfa[1].getAnchor() == Lexis::tail);
    REQUIRE(nfa[1].getAction() == Lexis::discard);
    REQUIRE(nfa[1].getToken() == "x_token");
}

TEST_CASE("dfa construction preserves language")
{
    Lexis::NFA nfa("hello");
    nfa.setLanguage("English");
    Lexis::DFA dfa(nfa);
    REQUIRE(dfa.getLanguage() == "English");
    REQUIRE(dfa.getNumberOfStates() >= 1);
}

TEST_CASE("nfa epsilon closure includes reachable states")
{
    Lexis::NFA nfa(3);
    nfa[0].connect(static_cast<Lexis::StateNumber>(1),
        static_cast<Lexis::StateNumber>(2));
    Toolbox::Set input;
    input += 0;
    Toolbox::Set closure = nfa.getEpsilonClosure(input);
    REQUIRE(closure.contains(0));
    REQUIRE(closure.contains(1));
    REQUIRE(closure.contains(2));
}
