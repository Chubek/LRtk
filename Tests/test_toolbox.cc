#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <catch2/catch_test_macros.hpp>
#include "Toolbox/Character.h"
#include "Toolbox/EscapeSequence.h"
#include "Toolbox/HashTable.h"
#include "Toolbox/List.h"
#include "Toolbox/PathName.h"
#include "Toolbox/Set.h"
#include "Toolbox/Stack.h"
#include "Toolbox/String.h"

TEST_CASE("octal and hexadecimal character conversion")
{
    REQUIRE(Toolbox::Character::isOctalDigit('7'));
    REQUIRE_FALSE(Toolbox::Character::isOctalDigit('8'));
    REQUIRE(Toolbox::Character::octalToBinary('7') == 7);
    REQUIRE(Toolbox::Character::hexToBinary('f') == 15);
}

TEST_CASE("escape sequences encode and decode")
{
    REQUIRE(Toolbox::EscapeSequence::encode('\n') == "\\n");
    REQUIRE(Toolbox::EscapeSequence::decode("\\n\\x41") == "\nA");
}

TEST_CASE("set supports membership and cardinality")
{
    Toolbox::Set set;
    set += 2;
    set += 10;
    REQUIRE(set.contains(2));
    REQUIRE_FALSE(set.contains(3));
    REQUIRE(set.getSize() == 2);
}

TEST_CASE("set supports union intersection and difference")
{
    Toolbox::Set left;
    Toolbox::Set right;
    left += 1;
    left += 2;
    right += 2;
    right += 3;
    REQUIRE((left | right).getSize() == 3);
    REQUIRE((left & right).getSize() == 1);
    left -= 2;
    REQUIRE(left.getSize() == 1);
}

TEST_CASE("stack is last in first out")
{
    Toolbox::Stack<int> stack;
    stack.push(1);
    stack.push(2);
    REQUIRE(stack.getTop() == 2);
    REQUIRE(stack.pop() == 2);
    REQUIRE(stack.pop() == 1);
    REQUIRE(stack.isEmpty());
}

TEST_CASE("hash table finds and removes values")
{
    Toolbox::HashTable<std::string, int> table;
    table.add("one", 1);
    REQUIRE(*table.find("one") == 1);
    table.remove("one");
    REQUIRE(table.find("one") == Toolbox::HashTable<std::string, int>::const_iterator());
}

TEST_CASE("path names split components")
{
    Toolbox::PathName path("dir/file.txt");
    REQUIRE(path.getHead() == "dir/");
    REQUIRE(path.getTail() == "file.txt");
    REQUIRE(path.getRoot() == "file");
    REQUIRE(path.getExtension() == ".txt");
}
