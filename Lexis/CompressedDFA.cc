#include <iostream>
#include "Lexis/CompressedDFA.h"

namespace Lexis
{
    CompressedDFA::CompressedDFA(DFA const& dfa) :
        numberOfStates(dfa.getNumberOfStates()),
        numberOfRows(0),
        numberOfColumns(0),
        numberOfTokens(0),
        rowMap(dfa.getNumberOfStates()),
        columnMap(maximumCharacter),
        anchorTable(dfa.getNumberOfStates()),
        actionTable(dfa.getNumberOfStates()),
        transitionTable(0),
        tokenTable(dfa.getNumberOfStates()),
        tokenList(dfa.getNumberOfStates()),
        language(dfa.getLanguage())
    {
        for (uint8_t c = 0; c < maximumCharacter; ++c)
            columnMap[c] = maximumCharacter;

           vector<TableEntry> columnTable(maximumCharacter);
           for (uint8_t c = 0; c < maximumCharacter; ++c)
           {
               if (columnMap[c] == maximumCharacter)
               {
                    columnTable[numberOfColumns] = c;
                    columnMap[c] = numberOfColumns;
                    for (uint8_t i = c + 1; i < maximumCharacter; ++i)
                    {
                        if (columnMap[i] == maximumCharacter &&
                                dfa.isColumnEquivalent(c, i))
                            columnMap[i] = numberOfColumns;
                    }
                    numberOfColumns += 1;
               }
           }
           vector<TableEntry> rowTable(numberOfStates);
           for (StateNumber s = 0; s < numberOfStates; ++s)
               rowMap[s] = numberOfStates;
           for (StateNumber s = 0; s < numberOfStates; ++s)
           {
               if (rowMap[s] == numberOfStates)
               {
                    rowTable[numberOfRows] = s;
                    rowMap[s] = numberOfRows;
                    for (StateNumber i = s + 1;
                        i < numberOfStates; ++i)
                    {
                        if (rowMap[i] == numberOfStates &&
                                dfa.isRowEquivalent(s, i))
                            rowMap[i] = numberOfRows;
                    }
                    numberOfRows += 1;
               }
           }
           for (StateNumber s = 0; s < numberOfStates; ++s)
           {
               anchorTable[s] = dfa[s].getAnchor();
               actionTable[s] = dfa[s].getAction();
               if (actionTable[s] == accept)
                    tokenTable[s] = dfa[s].getToken();
               else
                    tokenTable[s] = "end_of_file";
           }
           tokenList[numberOfTokens++] = "_epsilon";
           tokenList[numberOfTokens++] = "end_of_file";
           for (StateNumber s = 0; s < numberOfStates; ++s)
           {
               TableEntry i;
               for (i = 0; i < numberOfTokens; ++i)
                    if (tokenList[i] == tokenTable[s])
                        break;
               if (i == numberOfTokens)
               {
                    tokenList[numberOfTokens] = tokenTable[s];
                    numberOfTokens += 1;
               }
           }
           transitionTable.resize(numberOfRows * numberOfColumns);
           for (TableEntry row = 0; row < numberOfRows; ++row)
               for (TableEntry col = 0;
                        col < numberOfColumns; ++col)
                    transitionTable[row * numberOfColumns + col] =
                        dfa[rowTable[row]].getNextState(columnTable[col]);
      }
    CompressedDFA::~CompressedDFA()
        {}
    ostream& CompressedDFA::putMap(ostream& stream,
        char const* label, TableEntry size,
        vector<TableEntry> const& map) const
    {
        stream << "TableEntry const LexisTables::"
            << label << "[" << static_cast<uint16_t>(size) << "] =\n";
        stream << "{\n";
        stream << " ";
        for (uint16_t i = 0; i < size; ++i)
        {
            stream << static_cast<uint16_t>(map[i]);
            if (i < size - 1U)
                stream << ", ";
            if (i % 10 == 9)
            {
                stream << "\n";
                stream << " ";
            }
        }
        stream << "\n";
        stream << "};\n";
        return stream;
    }
    ostream& CompressedDFA::putActionTable(ostream& stream) const
    {
        stream << "Action const LexisTables::actionTable["
            << static_cast<uint16_t>(numberOfStates) << "] =\n";
        stream << "{\n";
        stream << " ";
        for (uint16_t i = 0; i < numberOfStates; ++i)
        {
            stream << actionTable[i];
            if (i < numberOfStates - 1U)
                stream << ", ";
            if (i % 4 == 3)
            {
                stream << "\n";
                stream << " ";
            }
        }
        stream << "\n";
        stream << "};\n";
        return stream;
    }
    ostream& CompressedDFA::putAnchorTable(ostream& stream) const
    {
        stream << "Anchor const LexisTables::anchorTable["
            << static_cast<uint16_t>(numberOfStates) << "] =\n";
        stream << "{\n";
        stream << " ";
        for (uint16_t i = 0; i < numberOfStates; ++i)
        {
            stream << anchorTable[i];
            if (i < numberOfStates - 1U)
                stream << ", ";
            if (i % 4 == 3)
            {
                stream << "\n";
                stream << " ";
            }
        }
        stream << "\n";
        stream << "};\n";
        return stream;
    }
    ostream& CompressedDFA::putTokenList(ostream& stream) const
    {
        stream << "TableEntry const LexisTables::numberOfTokens = "
            << static_cast<uint16_t>(numberOfTokens) << ";\n";
        stream << "LexisTables::TokenName const LexisTables::nameTable["
            << static_cast<uint16_t>(numberOfTokens) << "] =\n";
        stream << "{\n";
        for (TableEntry i = 0; i < numberOfTokens; ++i)
        {
            stream << " { " << tokenList[i] << ","
                << " \"" << tokenList[i] << "\" }";
            if (i < numberOfTokens - 1U)
                stream << ",\n";
        }
        stream << "\n";
        stream << "};\n";
        return stream;
    }
    ostream& CompressedDFA::putTokenTable(ostream& stream) const
    {
        stream << "LexisTables::TokenType const LexisTables::tokenTable["
            << static_cast<uint16_t>(numberOfStates) << "] =\n";
        stream << "{\n";
        stream << " ";
        for (uint16_t i = 0; i < numberOfStates; ++i)
        {
            stream << tokenTable[i];
            if (i < numberOfStates - 1U)
                stream << ", ";
            if (i % 2 == 1)
            {
                stream << "\n";
                stream << " ";
            }
        }
        stream << "\n";
        stream << "};\n";
        return stream;
    }
    ostream& CompressedDFA::putTransitionTable(ostream& stream) const
    {
        stream << "TableEntry const LexisTables::transitionTable["
            << static_cast<uint16_t>(numberOfRows * numberOfColumns)
            << "] =\n";
        stream << "{\n";
        for (TableEntry row = 0; row < numberOfRows; ++row)
        {
            stream << " // row " << static_cast<uint16_t>(row) << "\n";
            stream << " ";
            for (TableEntry col = 0; col < numberOfColumns; ++col)
            {
                stream << static_cast<uint16_t>(transitionTable[
                    row * numberOfColumns + col]);
                if (col < numberOfColumns - 1U)
                    stream << ", ";
                if (col % 10 == 9)
                {
                    stream << "\n";
                    stream << " ";
                }
            }
            if (row < numberOfRows - 1U)
                stream << ",";
            stream << "\n";
        }
        stream << "\n";
        stream << "};\n";
        return stream;
    }
    ostream& CompressedDFA::putTokens(ostream& stream) const
    {
        stream <<
            "#if !defined(lexistab_h)\n"
            "#define lexistab_h\n"
            "\n"
            "#include \"Lexis/Lexis.h\"\n"
            "\n"
            "namespace " << language << "\n"
            "{\n"
            "using namespace Lexis;\n"
            "using Lexis::advance;\n"
            "class LexisTables\n"
            "{\n"
            "public:\n"
            " enum TokenType\n"
            " {\n";
        for (TableEntry i = 0; i < numberOfTokens; ++i)
        {
            stream << "\t" << tokenList[i]
                << " = " << static_cast<uint16_t>(i);
            if (i < numberOfTokens - 1U)
                stream << ",\n";
        }
        stream <<
            "\n"
            " };\n"
            " struct TokenName\n"
            " {\n"
            "\tTokenType type;\n"
            "\tchar const* name;\n"
            " };\n"
            " static uint8_t const numberOfTokens;\n"
            " static TokenName const nameTable[];\n"
            " static TableEntry const numberOfStates;\n"
            " static TableEntry const numberOfRows;\n"
            " static TableEntry const numberOfColumns;\n"
            " static TableEntry const rowMap[];\n"
            " static TableEntry const columnMap[];\n"
            " static TableEntry const transitionTable[];\n"
            " static Anchor const anchorTable[];\n"
            " static Action const actionTable[];\n"
            " static TokenType const tokenTable[];\n"
            "};\n"
            "}\n"
            "\n"
            "#endif\n";
        return stream;
    }
    ostream& CompressedDFA::putTables(ostream& stream) const
    {
        stream <<
            "#include \"lexistab.h\"\n"
            "\n"
            "namespace " << language << "\n"
            "{\n";
        putTokenList(stream);
        stream << "TableEntry const LexisTables::numberOfStates = "
            << static_cast<uint16_t>(numberOfStates) << ";\n";
        stream << "TableEntry const LexisTables::numberOfColumns = "
            << static_cast<uint16_t>(numberOfColumns) << ";\n";
        putMap(stream, "columnMap", maximumCharacter, columnMap);
        stream << "TableEntry const LexisTables::numberOfRows = "
            << static_cast<uint16_t>(numberOfRows) << ";\n";
        putMap(stream, "rowMap", numberOfStates, rowMap);
        putTransitionTable(stream);
        putAnchorTable(stream);
        putActionTable(stream);
        putTokenTable(stream);
        stream << "}\n";
        return stream;
    }
}
